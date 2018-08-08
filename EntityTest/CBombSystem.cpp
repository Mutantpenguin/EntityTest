#include "CBombSystem.hpp"

void CBombSystem::Process()
{
	m_ecs.ForEach<CBombComponent>( [ this ] ( const auto &bombEntity, auto bombComponent )
	{
		if( !m_ecs.HasComponents<CExplosionComponent>( bombEntity ) )
		{
			const auto bombTransform = m_ecs.GetComponent<CTransformComponent>( bombEntity );

			if( bombTransform )
			{
				if( m_ecs.Exists<CHealthComponent>( [ this, &bombPosition = bombTransform->Position, &activationRadius = bombComponent->activationRadius ]( const auto &healthEntity, const auto healthComponent )
				{
					const auto healthTransform = m_ecs.GetComponent<CTransformComponent>( healthEntity );

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
			}
		}
	} );

	m_ecs.ForEach<CExplosionComponent>( [ this ] ( const auto &explosionEntity, auto explosionComponent )
	{
		const auto explosionTransform = m_ecs.GetComponent<CTransformComponent>( explosionEntity );

		m_ecs.ForEach<CHealthComponent>( [ this, &explosionPosition = explosionTransform->Position, &explosionRadius = explosionComponent->explosionRadius, &damage = explosionComponent->damage ]( const auto &healthEntity, auto healthComponent )
		{
			const auto healthTransform = m_ecs.GetComponent<CTransformComponent>( healthEntity );

			if( healthTransform )
			{
				if( glm::length( explosionPosition - healthTransform->Position ) < explosionRadius )
				{
					healthComponent->health -= damage;
				}
			}
		} );
	} );
}
