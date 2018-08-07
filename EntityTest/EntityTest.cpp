#include <chrono>

#include "CLogger.hpp"

#include "MyECS.hpp"

#include "CBombSystem.hpp"
#include "CHealthSystem.hpp"
#include "CMovementSystem.hpp"

int main()
{
	MyECS ecs;

	CLogger::Log( "" );


	{
		const auto start = std::chrono::system_clock::now();
		for( size_t i = 0; i < ecs.MaxSize; i++ )
		{
			auto entity = ecs.Create();

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
			else
			{
				CMovementComponent movement;
				movement.Direction = {	static_cast< float >( rand() ) / static_cast< float >( RAND_MAX ),
										static_cast< float >( rand() ) / static_cast< float >( RAND_MAX ),
										static_cast< float >( rand() ) / static_cast< float >( RAND_MAX ) };
				ecs.AddComponent( entity, movement );
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
		ecs.ForEach<CPhysicsComponent>( [ &counter, &ecs ]( const CEntity &entity, auto component )
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
		ecs.ForEach< CPhysicsComponent >( [ &counter, &ecs ] ( const CEntity &entity, auto component )
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
		const std::uint32_t numIterations { 100 };

		CLogger::Log( "test for a whole frame with '" + std::to_string( numIterations ) + "' iterations:" );
		const auto start = std::chrono::system_clock::now();
		std::uint32_t counter = 0;
		for( std::uint16_t j = 0; j < numIterations; j++ )
		{
			ecs.ForEach<CPhysicsComponent>( [ &counter, &ecs ] ( const CEntity &entity, auto component )
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
		std::vector< std::unique_ptr< CBaseSystem > > systems;

		systems.emplace_back( std::make_unique< CBombSystem >( ecs ) );
		systems.emplace_back( std::make_unique< CHealthSystem >( ecs ) );
		systems.emplace_back( std::make_unique< CMovementSystem >( ecs ) );

		// test of a real mainloop
		while( true )
		{
			const auto start = std::chrono::system_clock::now();

			for( auto &system : systems )
			{
				system->Run();
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