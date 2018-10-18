#include <chrono>

#include "CLogger.hpp"

#include "MyECS.hpp"

#include "COcTree.hpp"

#include "CBombSystem.hpp"
#include "CHealthSystem.hpp"
#include "CMovementSystem.hpp"
#include "CBVHSystem.hpp"

#include "minitrace.h"

int main()
{
	mtr_init( "trace.json" );

	MTR_META_PROCESS_NAME( "EntityTest" );
	MTR_META_THREAD_NAME( "main thread" );


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

				if( rand() % 10 > 4 )
				{
					ecs.AddComponent( entity, CBoundingBoxComponent( { 2.0f, 2.0f, 2.0f } ) );
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
		auto spatial = std::make_shared< COcTree >( glm::vec3( 0.0f, 0.0f, 0.0f ), CBoundingBox( { 110.0f, 110.0f, 110.0f } ) );

		ecs.CreateSystem< CBombSystem >( spatial );
		ecs.CreateSystem< CHealthSystem >();
		ecs.CreateSystem< CMovementSystem >();
		ecs.CreateSystem< CBVHSystem >( spatial );

		CLogger::Log( "" );

		// test of a real mainloop
		CLogger::Log( "START main loop" );

		for( std::uint16_t i = 0; i < 500; i++ )
		{
			MTR_SCOPE( "main", "Frame" );

			const auto start = std::chrono::system_clock::now();

			ecs.ProcessSystems();

			const auto end = std::chrono::system_clock::now();
			const std::chrono::duration<double> diff = end - start;
			CLogger::Log( "delta: " + std::to_string( diff.count() * 1000.0f ) + " ms" );
			CLogger::Log( "" );
		}
		CLogger::Log( "END main loop" );

		ecs.DestroySystem< CBombSystem >();
		ecs.DestroySystem< CHealthSystem >();
		ecs.DestroySystem< CMovementSystem >();
		ecs.DestroySystem< CBVHSystem >();
	}

	mtr_flush();
	mtr_shutdown();

	return( 0 );
}