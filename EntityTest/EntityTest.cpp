#include <chrono>

#include "Types.hpp"

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

	CLogger::Info( "" );


	{
		MTR_SCOPE( __FILE__, "Creating entities" );

		const auto start = std::chrono::high_resolution_clock::now();

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
				movement.Direction = {	static_cast< f16 >( rand() ) / static_cast< f16 >( RAND_MAX ),
										static_cast< f16 >( rand() ) / static_cast< f16 >( RAND_MAX ),
										static_cast< f16 >( rand() ) / static_cast< f16 >( RAND_MAX ) };
				ecs.AddComponent( entity, movement );
			}
		}

		const auto end = std::chrono::high_resolution_clock::now();
		const std::chrono::duration<f32> diff = end - start;
		CLogger::Info( "creating entities : " + std::to_string( diff.count() * 1000.0f ) + " ms\n" );
	}


	{
		{
			MTR_SCOPE( __FILE__, "Create systems" );

			auto spatial = std::make_shared< COcTree >( glm::vec3( 0.0f, 0.0f, 0.0f ), CBoundingBox( { 110.0f, 110.0f, 110.0f } ) );

			ecs.CreateSystem< CBombSystem >( spatial );
			ecs.CreateSystem< CHealthSystem >();
			ecs.CreateSystem< CMovementSystem >();
			ecs.CreateSystem< CBVHSystem >( spatial );
		}

		ecs.ProcessSystems();
		
		MTR_INSTANT( "main", "START" );

		// test of a real mainloop
		CLogger::Info( "START main loop" );

		const u16 simulateFrameCount { 500 };

		const auto startMainLoop = std::chrono::high_resolution_clock::now();

		for( u16 i = 0; i < simulateFrameCount; i++ )
		{
			MTR_SCOPE_I( __FILE__, "Frame", "no", i );
			MTR_INSTANT_I( __FILE__, "ECS", "count", ecs.Count() );

			const auto startFrame = std::chrono::high_resolution_clock::now();

			ecs.ProcessSystems();

			const std::chrono::duration<f32> diffFrame = std::chrono::high_resolution_clock::now() - startFrame;
			CLogger::Debug( "frame delta: " + std::to_string( diffFrame.count() * 1000.0f ) + " ms" );
			CLogger::Debug( "" );
		}

		const std::chrono::duration<f32> diffMainLoop = std::chrono::high_resolution_clock::now() - startMainLoop;

		CLogger::Info( "END main loop" );

		CLogger::Info( "" );

		CLogger::Info( "average framtime: " + std::to_string( diffMainLoop.count() / simulateFrameCount * 1000.0f ) + " ms" );

		CLogger::Info( "" );

		ecs.DestroySystem< CBombSystem >();
		ecs.DestroySystem< CHealthSystem >();
		ecs.DestroySystem< CMovementSystem >();
		ecs.DestroySystem< CBVHSystem >();
	}

	mtr_flush();
	mtr_shutdown();

	return( 0 );
}