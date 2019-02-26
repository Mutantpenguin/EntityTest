#include <chrono>

#include "ext/minitrace/minitrace.h"

#include "ext/fmt/format.h"

#include "ext/effolkronium/random.hpp"

#include "Types.hpp"

#include "CLogger.hpp"

#include "TestECS.hpp"
#include "TestSystems.hpp"

#include "COcTree.hpp"

int main()
{
	mtr_init( "trace.json" );

	MTR_META_PROCESS_NAME( "EntityTest" );
	MTR_META_THREAD_NAME( "main thread" );


	TestECS ecs;

	CLogger::Info( "Created ECS for:" );
	CLogger::Info( fmt::format( "\tup to {0:n} entities", ecs.MaxSize ) );
	CLogger::Info( "\twith these components:" );

	f16 totalComponentStorageInBytes;
	ecs.ForEachComponentStorage(	[ &totalComponentStorageInBytes ]( const auto &componentStorage )
									{
										CLogger::Info( fmt::format( "\t\t- {0:<15}{1:<4.2f} MiBi", componentStorage.ComponentName, componentStorage.SizeInBytes / 1024.0f / 1024.0f ) );
										totalComponentStorageInBytes += componentStorage.SizeInBytes;
									} );
	CLogger::Info( fmt::format( "\ttotal storage space: {0:.2f} MiBi", totalComponentStorageInBytes / 1024.0f / 1024.0f ) );
	CLogger::Info( "" );


	{
		using Random = effolkronium::random_static;

		MTR_SCOPE( __FILE__, "Creating entities" );

		const auto start = std::chrono::high_resolution_clock::now();

		for( u32 i = 0; i < ecs.MaxSize; i++ )
		{
			auto entity = ecs.Create();
			
			ecs.AddComponent( entity, DebugName( "entity_" + std::to_string( i ) ) );

			if( Random::get<u8>( 0, 9 ) == 2 )
			{
				ecs.AddComponent( entity, Physics( 10.0f ) );

				Transform transform;
				transform.Position = { Random::get<u8>( 0, 99 ), Random::get<u8>( 0, 99 ), Random::get<u8>( 0, 99 ) };
				ecs.AddComponent( entity, transform );

				if( Random::get<u8>( 0, 9 ) > 4 )
				{
					ecs.AddComponent( entity, BoundingBox( { 2.0f, 2.0f, 2.0f } ) );
				}
			}

			if( Random::get<u8>( 0, 9 ) > 4 )
			{
				Player playerComponent;

				if( Random::get<u8>( 0, 9 ) > 4 )
				{
					playerComponent.Team = 1;
				}
				else
				{
					playerComponent.Team = 2;
				}

				ecs.AddComponent( entity, playerComponent );
			}

			if( Random::get<u8>( 0, 9 ) > 7 )
			{
				ecs.AddComponent( entity, Health( 100.0f ) );
			}

			if( Random::get<u8>( 0, 9 ) > 7 )
			{
				ecs.AddComponent( entity, Bomb( 10.0f ) );
			}
			else
			{
				Movement movement;
				movement.Direction = {	Random::get<f16>( -1.0f, 1.0f ),
										Random::get<f16>( -1.0f, 1.0f ),
										Random::get<f16>( -1.0f, 1.0f ) };
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

			ecs.CreateSystem< TestBVHSystem >( spatial );
			ecs.CreateSystem< TestBombSystem >( spatial );
			ecs.CreateSystem< TestHealthSystem >();
			ecs.CreateSystem< TestMovementSystem >();
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

		auto avgFrametimeMs = diffMainLoop.count() / simulateFrameCount * 1000.0f;

		CLogger::Info( fmt::format( "average frametime: {0:.2f} ms", avgFrametimeMs ) );

		auto fps = 1.0f / avgFrametimeMs * 1000.0f;

		CLogger::Info( fmt::format( "average fps:     : {0:.2f}", fps ) );

		CLogger::Info( "" );

		ecs.DestroySystemAll();
	}

	mtr_flush();
	mtr_shutdown();

	return( 0 );
}