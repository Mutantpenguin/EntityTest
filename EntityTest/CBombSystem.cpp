#include "CBombSystem.hpp"

#include <vector>

void CBombSystem::Process()
{
	CLogger::Log( "\tprocessing: CBombSystem" );	
	
	std::vector<CEntity> bombEntitiesForDeletion;

	m_ecs.ForEach<CBombComponent>( [ this ] ( const auto &bombEntity, auto bombComponent )
	{
		if( !m_ecs.HasComponents<CExplosionComponent>( bombEntity ) )
		{
			const auto bombTransform = m_ecs.GetComponent<CTransform>( bombEntity );

			if( bombTransform )
			{
				// TODO use the spatial partitioning to find out if such an entity exists
				if( m_spatial->ExistsIn( CSphere( bombTransform->Position, bombComponent->activationRadius ), [ this ] ( const CEntity &entity )
				{
					if( m_ecs.HasComponents< CHealthComponent >( entity ) )
					{
						return( true );
					}
					
					return( false );
				} ) )
				{
					// TODO set proper radius and damage
					m_ecs.AddComponent( bombEntity, CExplosionComponent( 20.0f, 15.0f ) );
				}

				/* TODO old, needed for timing the execution time after conversion
				if( m_ecs.Exists<CHealthComponent>( [ this, &bombPosition = bombTransform->Position, &activationRadius = bombComponent->activationRadius ]( const auto &healthEntity, const auto healthComponent )
				{
					const auto healthTransform = m_ecs.GetComponent<CTransform>( healthEntity );

					if( healthTransform )
					{
						if( glm::length( bombPosition - healthTransform->Position ) < activationRadius )
						{
							return( true );
						}
					}

					return( false );
				} ) )
				{
					// TODO set proper radius and damage
					m_ecs.AddComponent( bombEntity, CExplosionComponent( 20.0f, 15.0f ) );
				}
				*/
			}
		}
	} );

	m_ecs.ForEach<CExplosionComponent>( [ this, &bombEntitiesForDeletion ] ( const auto &explosionEntity, auto explosionComponent )
	{
		const auto explosionTransform = m_ecs.GetComponent<CTransform>( explosionEntity );

		// TODO use the spatial partitioning to find out if such an entity exists
		m_spatial->ForEachIn( CSphere( explosionTransform->Position, explosionComponent->explosionRadius ), [ this, &damage = explosionComponent->damage ] ( const CEntity &entity )
		{
			auto healthComponent = m_ecs.GetComponent< CHealthComponent >( entity );

			if( healthComponent )
			{
				healthComponent->health -= damage;
			}
		} );


		/* TODO old, needed for timing the execution time after conversion
		m_ecs.ForEach<CHealthComponent>( [ this, &explosionPosition = explosionTransform->Position, &explosionRadius = explosionComponent->explosionRadius, &damage = explosionComponent->damage ]( const auto &healthEntity, auto healthComponent )
		{
			const auto healthTransform = m_ecs.GetComponent<CTransform>( healthEntity );

			if( healthTransform )
			{
				if( glm::length( explosionPosition - healthTransform->Position ) < explosionRadius )
				{
					healthComponent->health -= damage;
				}
			}
		} );
		*/
		
		bombEntitiesForDeletion.push_back( explosionEntity );
	} );
	
	for( const auto &entity : bombEntitiesForDeletion )
	{
		m_ecs.Destroy( entity );
	}
	
	CLogger::Log( std::to_string( m_ecs.Count<CBombComponent>() ) + " CBombComponent remaining" );
}
