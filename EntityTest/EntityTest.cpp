#include "stdafx.h"

#include <chrono>

#include <memory>

#include "CLogger.hpp"

#include "CEntityComponentSystem.hpp"

#include "CPhysicsComponent.hpp"
#include "CPlayerComponent.hpp"
#include "CDebugNameComponent.hpp"
#include "CTransformComponent.hpp"

#include "CBombComponent.hpp"
#include "CExplosionComponent.hpp"
#include "CHealthComponent.hpp"

int main()
{
	constexpr size_t numberOfEntities = 10000;

	CEntityComponentSystem< numberOfEntities,
							CPhysicsComponent,
							CPlayerComponent,
							CDebugNameComponent,
							CTransformComponent,
							CBombComponent,
							CExplosionComponent,
							CHealthComponent > ecs;

	CLogger::Log( "" );


	{
		const auto start = std::chrono::system_clock::now();
		for( size_t i = 0; i < numberOfEntities; i++ )
		{
			auto entity = ecs.CreateEntity();

			ecs.AddComponent( entity, CDebugNameComponent( "entity_" + std::to_string( i ) ) );

			if( rand() % 10 == 2 )
			{
				ecs.AddComponent( entity, CPhysicsComponent( 10.0f ) );

				CTransformComponent transform;
				transform.Position = { rand() % 100, rand() % 100, rand() % 100 };
				ecs.AddComponent( entity, transform );
			}

			if( rand() % 10 > 4 )
			{
				CPlayerComponent playerComponent;

				if( rand() % 10 > 4 )
				{
					playerComponent.Team = 1;
				}
				else
				{
					playerComponent.Team = 2;
				}

				ecs.AddComponent( entity, playerComponent );
			}

			if( rand() % 10 > 7 )
			{
				ecs.AddComponent( entity, CHealthComponent( 100.0f ) );
			}

			if( rand() % 10 > 7 )
			{
				ecs.AddComponent( entity, CBombComponent( 10.0f ) );
			}
		}
		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> diff = end - start;
		CLogger::Log( "creating entities : " + std::to_string( diff.count() * 1000.0f ) + " ms\n" );
	}


	{
		CLogger::Log( "entities with physics and name:" );
		const auto start = std::chrono::system_clock::now();
		std::uint32_t counter = 0;
		ecs.ForEach<CPhysicsComponent>( [ &counter, &ecs ]( const Entity &entity, auto component )
		{
			auto debugName = ecs.GetComponent<CDebugNameComponent>( entity );

			if( debugName )
			{
				//CLogger::Log( "\t - " + debugName->name );
			}

			counter++;
		} );

		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> diff = end - start;
		CLogger::Log( "Time iterate " + std::to_string( counter ) + " entities: " + std::to_string( diff.count() * 1000.0f ) + " ms\n" );
	}
	/* TODO
	{
		CLogger::Log( "entities with physics and player 1:" );
		const auto start = std::chrono::system_clock::now();
		const auto componentsWithPhysicsAndPlayer = ecs->GetEntitiesWithComponents<CPhysicsComponent, CPlayerComponent>();

		if( componentsWithPhysicsAndPlayer.size() > 0 )
		{
			for( const auto entity : componentsWithPhysicsAndPlayer )
			{
				//CLogger::Log("\t - " + entity->Name());
			}
		}

		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> diff = end - start;
		CLogger::Log( "Time to fill and iterate a vector of " + std::to_string( componentsWithPhysicsAndPlayer.size() ) + " : " + std::to_string( diff.count() * 1000.0f ) + " ms\n" );
	}
	*/

	{
		CLogger::Log( "entities with physics and player 2:" );
		const auto start = std::chrono::system_clock::now();
		std::uint32_t counter = 0;
		ecs.ForEach< CPhysicsComponent >( [ &counter, &ecs ] ( const Entity &entity, auto component )
		{
			if( ecs.HasComponents< CPlayerComponent >( entity ) )
			{
				//CLogger::Log( "gnah" );
			}

			if( ecs.HasComponents< CPlayerComponent, CDebugNameComponent >( entity ) )
			{
				//CLogger::Log( "gnah" );
			}

			if( ecs.HasAnyComponents< CPlayerComponent, CDebugNameComponent >( entity ) )
			{
				//CLogger::Log( "gnah" );
			}

			const auto playerComponent = ecs.GetComponent< CPlayerComponent >( entity );

			if( playerComponent )
			{
				counter++;
			}
		} );
		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> diff = end - start;
		CLogger::Log( "Time iterate " + std::to_string( counter ) + " entities: " + std::to_string( diff.count() * 1000.0f ) + " ms\n" );
	}


	{
		std::uint32_t numIterations { 100 };

		CLogger::Log( "test for a whole frame with '" + std::to_string( numIterations ) + "' iterations:" );
		const glm::vec3 position { 0.0f, 0.0f, 0.0f };
		const auto start = std::chrono::system_clock::now();
		std::uint32_t counter = 0;
		for( std::uint16_t j = 0; j < numIterations; j++ )
		{
			ecs.ForEach<CPhysicsComponent>( [ &counter, &ecs ] ( const Entity &entity, auto component )
			{
				const auto player = ecs.GetComponent<CPlayerComponent>( entity );

				if( player )
				{
					counter++;
				}
			} );
		}
		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> diff = end - start;
		CLogger::Log( "Time: " + std::to_string( diff.count() * 1000.0f ) + " ms\n" );
	}

	{
		// test of a real mainloop
		while( true )
		{
			const auto start = std::chrono::system_clock::now();

			ecs.ForEach<CBombComponent>( [ &ecs ] ( const auto &bombEntity, auto bombComponent )
			{
				if( !ecs.HasComponents<CExplosionComponent>( bombEntity ) )
				{
					const auto bombTransform = ecs.GetComponent<CTransformComponent>( bombEntity );

					if( bombTransform )
					{
						if( ecs.Exists<CHealthComponent>(	[ &ecs, &bombPosition = bombTransform->Position, &activationRadius = bombComponent->activationRadius ] ( const auto &healthEntity, const auto healthComponent )
															{
																const auto healthTransform = ecs.GetComponent<CTransformComponent>( healthEntity );

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
							ecs.AddComponent( bombEntity, CExplosionComponent( 20.0f, 15.0f ) );
						}
					}
				}
			} );

			ecs.ForEach<CExplosionComponent>( [ &ecs ]( const auto &explosionEntity, auto explosionComponent )
											  {
												  const auto explosionTransform = ecs.GetComponent<CTransformComponent>( explosionEntity );

												  ecs.ForEach<CHealthComponent>( [ &ecs, &explosionPosition = explosionTransform->Position, &explosionRadius = explosionComponent->explosionRadius, &damage = explosionComponent->damage ]( const auto &healthEntity, auto healthComponent )
																				 {
																					 const auto healthTransform = ecs.GetComponent<CTransformComponent>( healthEntity );

																					 if( healthTransform )
																					 {
																						 if( glm::length( explosionPosition - healthTransform->Position ) < explosionRadius )
																						 {
																							 healthComponent->health -= damage;
																						 }
																					 }
																				 } );
											  } );

			std::vector<Entity> entitiesForDeletion;

			ecs.ForEach<CHealthComponent>( [ &entitiesForDeletion ]( const auto &healthEntity, auto healthComponent )
										   {
											   if( healthComponent->health < 0.0f )
											   {
												   entitiesForDeletion.push_back( healthEntity );
											   }
										   } );

			for( const auto &entity : entitiesForDeletion )
			{
				ecs.DestroyEntity( entity );
			}

			if( entitiesForDeletion.size() > 0 )
			{
				CLogger::Log( "deleted " + std::to_string( entitiesForDeletion.size() ) + " entities" );
			}

			const auto end = std::chrono::system_clock::now();
			const std::chrono::duration<double> diff = end - start;
			CLogger::Log( "delta: " + std::to_string( diff.count() * 1000.0f ) + " ms" );
			CLogger::Log( "\t" + std::to_string( ecs.Count<CBombComponent>() ) + " remaining" );
			CLogger::Log( "" );
		}
	}

	return( 0 );
}