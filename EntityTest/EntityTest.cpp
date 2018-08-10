#include <chrono>

#include "CLogger.hpp"

#include "MyECS.hpp"

#include "CBombSystem.hpp"
#include "CHealthSystem.hpp"
#include "CMovementSystem.hpp"
#include "CBVHSystem.hpp"

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

				CTransform transform;
				transform.Position = { rand() % 100, rand() % 100, rand() % 100 };
				ecs.AddComponent( entity, transform );

				if( rand() % 10 > 4 )
				{
					CBoundingBox boundingBox( { -5.0f, -5.0f, -5.0f }, { 5.0f, 5.0f, 5.0f } );
					boundingBox.MoveTo( transform.Position );
					ecs.AddComponent( entity, boundingBox );
				}
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
		ecs.CreateSystem< CBombSystem >();
		ecs.CreateSystem< CHealthSystem >();
		ecs.CreateSystem< CMovementSystem >();
		ecs.CreateSystem< CBVHSystem >( CBoundingBox( { -110.0f, -110.0f, -110.0f }, { 110.0f, 110.0f, 110.0f } ) );

		// test of a real mainloop
		while( true )
		{
			const auto start = std::chrono::system_clock::now();

			ecs.ProcessSystems();

			const auto end = std::chrono::system_clock::now();
			const std::chrono::duration<double> diff = end - start;
			CLogger::Log( "delta: " + std::to_string( diff.count() * 1000.0f ) + " ms" );
			CLogger::Log( "\t" + std::to_string( ecs.Count<CBombComponent>() ) + " remaining" );
			CLogger::Log( "" );
		}

		ecs.DestroySystem< CBombSystem >();
		ecs.DestroySystem< CHealthSystem >();
		ecs.DestroySystem< CMovementSystem >();
		ecs.DestroySystem< CBVHSystem >();
	}

	return( 0 );
}