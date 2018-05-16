// EntityTest.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <chrono>

#include <memory>

#include "CLogger.hpp"

#include "CScene.hpp"

#include "CPhysicsComponent.hpp"
#include "CPlayerComponent.hpp"
#include "CDebugNameComponent.hpp"
#include "CTransformComponent.hpp"

int main()
{
	constexpr size_t numberOfEntities = 100000;

	CScene< numberOfEntities,
		    CPhysicsComponent,
		    CPlayerComponent,
		    CDebugNameComponent,
		    CTransformComponent > scene;

	CLogger::Log( "----------------------------------------------------------------------------------------" );
	CLogger::Log( "entity count: " + std::to_string( numberOfEntities ) );
	CLogger::Log( "----------------------------------------------------------------------------------------" );

	CLogger::Log( "" );


	{
		const auto start = std::chrono::system_clock::now();
		for( size_t i = 0; i < numberOfEntities; i++ )
		{
			auto entity = scene.CreateEntity();

			scene.AddComponent( entity, CDebugNameComponent { "entity_" + std::to_string( i ) } );

			if( rand() % 10 == 2 )
			{
				CPhysicsComponent physics;
				physics.mass = 10.0f;

				scene.AddComponent( entity, physics );

				CTransformComponent transform;
				transform.Position( { rand() % 100, rand() % 100, rand() % 100 } );
				scene.AddComponent( entity, transform );
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

				scene.AddComponent( entity, playerComponent );
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
		scene.EachComponent<CPhysicsComponent>( [ &counter, &scene ]( const Entity &entity, const auto &component )
		{
			auto debugName = scene.GetComponent<CDebugNameComponent>( entity );

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
		const auto componentsWithPhysicsAndPlayer = scene->GetEntitiesWithComponents<CPhysicsComponent, CPlayerComponent>();

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
		scene.EachComponent< CPhysicsComponent >( [ &counter, &scene ] ( const Entity &entity, const auto &component )
		{
			if( scene.HasComponents< CPlayerComponent >( entity ) )
			{
				//CLogger::Log( "gnah" );
			}

			if( scene.HasComponents< CPlayerComponent, CDebugNameComponent >( entity ) )
			{
				//CLogger::Log( "gnah" );
			}

			if( scene.HasAnyComponents< CPlayerComponent, CDebugNameComponent >( entity ) )
			{
				//CLogger::Log( "gnah" );
			}

			const auto blah1 = scene.GetComponent<CPlayerComponent>( entity );

			if( blah1 )
			{
				counter++;
			}
		} );
		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> diff = end - start;
		CLogger::Log( "Time iterate " + std::to_string( counter ) + " entities: " + std::to_string( diff.count() * 1000.0f ) + " ms\n" );
	}
	
	/*
	{
		CLogger::Log( "entities with physics in radius:" );
		const glm::vec3 position { 0.0f, 0.0f, 0.0f };
		const float radius { 30.0f };
		const auto start = std::chrono::system_clock::now();
		std::uint32_t counter = 0;
		scene->EachWithComponentsInRadius<CPhysicsComponent>( position, radius, [ &counter ] ( const std::shared_ptr<const CEntity> &entity )
		{
			counter++;
		} );
		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> diff = end - start;
		CLogger::Log( "Time iterate " + std::to_string( counter ) + " entities: " + std::to_string( diff.count() * 1000.0f ) + " ms\n" );
	}
	*/
	/* TODO
	{
		CLogger::Log( "entities with physics and/or player in radius:" );
		const auto start = std::chrono::system_clock::now();
		std::uint32_t counter = 0;
		scene.EachWithAnyComponents<CPhysicsComponent, CPlayerComponent>( [ &counter, &scene ] ( const std::uint32_t id, const auto &component )
		{
			counter++;
		} );
		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> diff = end - start;
		CLogger::Log( "Time iterate " + std::to_string( counter ) + " entities: " + std::to_string( diff.count() * 1000.0f ) + " ms\n" );
	}
	*/
	/* TODO
	{
		std::uint32_t numIterations { 100 };

		CLogger::Log( "test for a whole frame with '" + std::to_string( numIterations ) + "' iterations:" );
		const glm::vec3 position { 0.0f, 0.0f, 0.0f };
		const auto start = std::chrono::system_clock::now();
		std::uint32_t counter = 0;
		for( std::uint16_t j = 0; j < numIterations; j++ )
		{
			scene.EachComponent<CPhysicsComponent>( [ &counter, &scene ] ( const std::uint32_t id, const auto &component )
			{
				const auto player = scene.GetComponent<CPlayerComponent>( id );

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
	*/

	return( 0 );
}