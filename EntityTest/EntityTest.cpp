#include <chrono>

#include "minitrace.h"

#include "Types.hpp"

#include "CLogger.hpp"

#include "TestECS.hpp"

#include "COcTree.hpp"


int main()
{
	mtr_init( "trace.json" );

	MTR_META_PROCESS_NAME( "EntityTest" );
	MTR_META_THREAD_NAME( "main thread" );


	TestECS ecs;

	CLogger::Info( "" );


	{
		MTR_SCOPE( __FILE__, "Creating entities" );

		const auto start = std::chrono::high_resolution_clock::now();

		for( u32 i = 0; i < ecs.MaxSize; i++ )
		{
			auto entity = ecs.Create();
			
			ecs.AddComponent( entity, cmpt::DebugName( "entity_" + std::to_string( i ) ) );

			if( rand() % 10 == 2 )
			{
				ecs.AddComponent( entity, cmpt::Physics( 10.0f ) );

				cmpt::Transform transform;
				transform.Position = { rand() % 100, rand() % 100, rand() % 100 };
				ecs.AddComponent( entity, transform );

				if( rand() % 10 > 4 )
				{
					ecs.AddComponent( entity, cmpt::BoundingBox( { 2.0f, 2.0f, 2.0f } ) );
				}
			}

			if( rand() % 10 > 4 )
			{
				cmpt::Player playerComponent;

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
				ecs.AddComponent( entity, cmpt::Health( 100.0f ) );
			}

			if( rand() % 10 > 7 )
			{
				ecs.AddComponent( entity, cmpt::Bomb( 10.0f ) );
			}
			else
			{
				cmpt::Movement movement;
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

			ecs.CreateSystem< TestBombSystem >( spatial );
			ecs.CreateSystem< TestHealthSystem >();
			ecs.CreateSystem< TestMovementSystem >();
			ecs.CreateSystem< TestBVHSystem >( spatial );
		}

		const auto firstIterationStart = std::chrono::high_resolution_clock::now();
		ecs.ProcessSystems();
		const std::chrono::duration<f32> firstIterationDiff = std::chrono::high_resolution_clock::now() - firstIterationStart;
		CLogger::Info( "first iteration diff: " + std::to_string( firstIterationDiff.count() * 1000.0f ) + " ms" );
		CLogger::Info( "" );
		
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

		ecs.DestroySystemAll();
	}

	mtr_flush();
	mtr_shutdown();

	return( 0 );
}