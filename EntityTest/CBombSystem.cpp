#include "CBombSystem.hpp"

#include <vector>
#include <chrono>

#include <glm/gtx/norm.hpp>

#include "minitrace.h"

void CBombSystem::Process()
{
	MTR_SCOPE( "CBombSystem", "CBombSystem::Process" );

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
	MTR_END( "CBombSystem", "each CExplosionComponent" );

	
	for( const auto &entity : bombEntitiesForDeletion )
	{
		m_ecs.Destroy( entity );
	}
	
	CLogger::Debug( "\t\t" + std::to_string( m_ecs.Count<CBombComponent>() ) + " CBombComponent remaining" );
}
