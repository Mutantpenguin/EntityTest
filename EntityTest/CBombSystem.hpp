#pragma once

#include "ecs/CComponentSystem.hpp"

#include "CBVHBase.hpp"

template< typename T_ecs >
class CBombSystem final : public ecs::CComponentSystem< T_ecs >
{
public:
	CBombSystem( T_ecs &ecs, const std::shared_ptr< CBVHBase > &bvh ) :
		CComponentSystem( ecs ),
		m_bvh { bvh }
	{}

	virtual ~CBombSystem()
	{};

	virtual void Process() override
	{
		MTR_BEGIN( "CBombSystem", "CBombSystem::Process" );

		CLogger::Debug( "\tprocessing: CBombSystem" );

		std::vector< ecs::CEntity > bombEntitiesForDeletion;

		MTR_BEGIN( "CBombSystem", "ForEach<Bomb>" );
		m_ecs.ForEach<cmpt::Bomb>( [ this ] ( const auto &bombEntity, auto bombComponent )
		{
			if( !m_ecs.HasComponents<cmpt::Explosion>( bombEntity ) )
			{
				if( const auto bombTransform = m_ecs.GetComponent<cmpt::Transform>( bombEntity ) )
				{
					if( m_bvh->ExistsIn( bombTransform->Position, CSphere( bombComponent->activationRadius ), [ this ] ( const ecs::CEntity &entity )
					{
						return( m_ecs.HasComponents< cmpt::Health >( entity ) );
					} ) )
					{
						m_ecs.AddComponent( bombEntity, cmpt::Explosion( 20.0f, 15.0f ) );
					}
				}
			}
		} );
		MTR_END( "CBombSystem", "ForEach<Bomb>" );

		MTR_BEGIN( "CBombSystem", "ForEach<Explosion>" );
		m_ecs.ForEach<cmpt::Explosion>( [ this, &bombEntitiesForDeletion ] ( const auto &explosionEntity, auto explosionComponent )
		{
			const auto explosionTransform = m_ecs.GetComponent<cmpt::Transform>( explosionEntity );

			m_bvh->ForEachIn( explosionTransform->Position, CSphere( explosionComponent->explosionRadius ), [ this, &damage = explosionComponent->damage ]( const ecs::CEntity &entity )
			{
				if( auto healthComponent = m_ecs.GetComponent< cmpt::Health >( entity ) )
				{
					healthComponent->health -= damage;
				}
			} );

			bombEntitiesForDeletion.push_back( explosionEntity );
		} );
		MTR_END( "CBombSystem", "ForEach<Explosion>" );


		for( const auto &entity : bombEntitiesForDeletion )
		{
			m_ecs.Destroy( entity );
		}

		CLogger::Debug( "\t\t" + std::to_string( m_ecs.Count<cmpt::Bomb>() ) + " Bomb remaining" );

		MTR_END( "CBombSystem", "CBombSystem::Process" );
	}

private:
	const std::shared_ptr< CBVHBase > m_bvh;
};

