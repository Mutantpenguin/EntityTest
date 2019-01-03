#pragma once

#include "ecs/ComponentSystemBase.hpp"

#include "CBVHBase.hpp"

template< typename T_ecs >
class CBombSystem final : public ecs::ComponentSystemBase< T_ecs >
{
public:
	CBombSystem( T_ecs &ecs, const std::shared_ptr< CBVHBase > &bvh ) :
		ComponentSystemBase( ecs ),
		m_bvh { bvh }
	{}

	virtual ~CBombSystem()
	{};

	virtual void Process() override
	{
		MTR_BEGIN( "CBombSystem", "CBombSystem::Process" );

		CLogger::Debug( "\tprocessing: CBombSystem" );

		std::vector< ecs::Id > bombEntitiesForDeletion;

		MTR_BEGIN( "CBombSystem", "ForEachComponent<Bomb>" );
		m_ecs.ForEachComponent<Bomb>( [ this ] ( const auto &bombEntity, auto bombComponent )
		{
			if( !m_ecs.HasComponents<Explosion>( bombEntity ) )
			{
				if( const auto bombTransform = m_ecs.GetComponent<Transform>( bombEntity ) )
				{
					if( m_bvh->ExistsIn( bombTransform->Position, CSphere( bombComponent->activationRadius ), [ this ] ( const ecs::Id &entity )
					{
						return( m_ecs.HasComponents< Health >( entity ) );
					} ) )
					{
						m_ecs.AddComponent( bombEntity, Explosion( 20.0f, 15.0f ) );
					}
				}
			}
		} );
		MTR_END( "CBombSystem", "ForEachComponent<Bomb>" );

		MTR_BEGIN( "CBombSystem", "ForEachComponent<Explosion>" );
		m_ecs.ForEachComponent<Explosion>( [ this, &bombEntitiesForDeletion ] ( const auto &explosionEntity, auto explosionComponent )
		{
			const auto explosionTransform = m_ecs.GetComponent<Transform>( explosionEntity );

			m_bvh->ForEachIn( explosionTransform->Position, CSphere( explosionComponent->explosionRadius ), [ this, &damage = explosionComponent->damage ]( const ecs::Id &entity )
			{
				if( auto healthComponent = m_ecs.GetComponent< Health >( entity ) )
				{
					healthComponent->health -= damage;
				}
			} );

			bombEntitiesForDeletion.push_back( explosionEntity );
		} );
		MTR_END( "CBombSystem", "ForEachComponent<Explosion>" );


		for( auto &entity : bombEntitiesForDeletion )
		{
			m_ecs.Destroy( entity );
		}

		CLogger::Debug( "\t\t" + std::to_string( m_ecs.Count<Bomb>() ) + " Bomb remaining" );

		MTR_END( "CBombSystem", "CBombSystem::Process" );
	}

private:
	const std::shared_ptr< CBVHBase > m_bvh;
};

