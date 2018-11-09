#pragma once

#include "CComponentSystem.hpp"

#include "CBVHBase.hpp"

template< typename T_ecs >
class CBombSystem final : public CComponentSystem< T_ecs >
{
public:
	CBombSystem( T_ecs &ecs, const std::shared_ptr< CBVHBase > &bvh ) :
		CComponentSystem( ecs ),
		m_bvh { bvh }
	{}

	~CBombSystem()
	{};

	virtual void Process() override
	{
		MTR_BEGIN( "CBombSystem", "CBombSystem::Process" );

		CLogger::Debug( "\tprocessing: CBombSystem" );

		std::vector<CEntity> bombEntitiesForDeletion;

		MTR_BEGIN( "CBombSystem", "ForEach<CBombComponent>" );
		m_ecs.ForEach<CBombComponent>( [ this ] ( const auto &bombEntity, auto bombComponent )
		{
			if( !m_ecs.HasComponents<CExplosionComponent>( bombEntity ) )
			{
				if( const auto bombTransform = m_ecs.GetComponent<CTransformComponent>( bombEntity ) )
				{
					if( m_bvh->ExistsIn( bombTransform->Position, CSphere( bombComponent->activationRadius ), [ this ] ( const CEntity &entity )
					{
						return( m_ecs.HasComponents< CHealthComponent >( entity ) );
					} ) )
					{
						m_ecs.AddComponent( bombEntity, CExplosionComponent( 20.0f, 15.0f ) );
					}
				}
			}
		} );
		MTR_END( "CBombSystem", "ForEach<CBombComponent>" );

		MTR_BEGIN( "CBombSystem", "ForEach<CExplosionComponent>" );
		m_ecs.ForEach<CExplosionComponent>( [ this, &bombEntitiesForDeletion ] ( const auto &explosionEntity, auto explosionComponent )
		{
			const auto explosionTransform = m_ecs.GetComponent<CTransformComponent>( explosionEntity );

			m_bvh->ForEachIn( explosionTransform->Position, CSphere( explosionComponent->explosionRadius ), [ this, &damage = explosionComponent->damage ]( const CEntity &entity )
			{
				if( auto healthComponent = m_ecs.GetComponent< CHealthComponent >( entity ) )
				{
					healthComponent->health -= damage;
				}
			} );

			bombEntitiesForDeletion.push_back( explosionEntity );
		} );
		MTR_END( "CBombSystem", "ForEach<CExplosionComponent>" );


		for( const auto &entity : bombEntitiesForDeletion )
		{
			m_ecs.Destroy( entity );
		}

		CLogger::Debug( "\t\t" + std::to_string( m_ecs.Count<CBombComponent>() ) + " CBombComponent remaining" );

		MTR_END( "CBombSystem", "CBombSystem::Process" );
	}

private:
	const std::shared_ptr< CBVHBase > m_bvh;
};

