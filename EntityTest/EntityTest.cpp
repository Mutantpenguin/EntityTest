// EntityTest.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <chrono>

#include "CScene.hpp"

#include "CCameraFreeComponent.hpp"
#include "CPhysicsComponent.hpp"
#include "CPlayerComponent.hpp"


int main()
{
	const std::uint32_t numberOfEntities = 10000;

	auto scene = std::make_shared<CScene>();

	CLogger::Log( "----------------------------------------------------------------------------------------" );
	CLogger::Log( "entity count: " + std::to_string( numberOfEntities ) );
	CLogger::Log( "----------------------------------------------------------------------------------------" );

	CLogger::Log( "" );

	{
		const auto start = std::chrono::system_clock::now();
		for( int i = 10; i < numberOfEntities; i++ )
		{
			auto ent = scene->CreateEntity( "entity_" + std::to_string( i ) );

			if( rand() % 10 == 2 )
			{
				ent->Add<CPhysicsComponent>();
				ent->Transform.Position( { rand() % 100, rand() % 100, rand() % 100 } );
			}

			if( rand() % 10 > 4 )
			{
				auto comp = ent->Add<CPlayerComponent>();

				if( rand() % 10 > 4 )
				{
					comp->Team = 1;
				}
				else
				{
					comp->Team = 2;
				}

			}
		}
		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> diff = end - start;
		CLogger::Log( "creating entities : " + std::to_string( diff.count() * 1000.0f ) + " ms\n" );
	}

	{
		CLogger::Log( "entities with physics:" );
		const auto start = std::chrono::system_clock::now();
		const auto componentsWithPhysics = scene->GetEntitiesWithComponents<CPhysicsComponent>();

		if( componentsWithPhysics.size() > 0 )
		{
			for( const auto entity : componentsWithPhysics )
			{
				//CLogger::Log("\t - " + entity->Name());
			}
		}

		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> diff = end - start;
		CLogger::Log( "Time to fill and iterate a vector of " + std::to_string( componentsWithPhysics.size() ) + " : " + std::to_string( diff.count() * 1000.0f ) + " ms\n" );
	}

	{
		CLogger::Log( "entities with physics and player:" );
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

	{
		CLogger::Log( "entities with physics and player:" );
		const auto start = std::chrono::system_clock::now();
		//scene->Each<CCameraFreeComponent>([](const std::shared_ptr<const CEntity> &entity)
		std::uint16_t counter = 0;
		scene->Each<CPhysicsComponent, CPlayerComponent>( [&counter] ( const std::shared_ptr<const CEntity> &entity )
		{
			counter++;
			//CLogger::Log("\t - " + entity->Name() + " / " + entity->Get<CPlayerComponent>()->Team);
			const auto blah1 = entity->Get<CPlayerComponent>();
			const auto mult = blah1->Team * blah1->Team;
			//const auto blah1 = entity->Get<CPlayerComponent>();

			//const auto blah3 = entity->Get<CCameraFreeComponent>();
		} );
		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> diff = end - start;
		CLogger::Log( "Time iterate " + std::to_string( counter ) + " entities: " + std::to_string( diff.count() * 1000.0f ) + " ms\n" );
	}

	{
		CLogger::Log( "entities with physics in radius:" );
		const glm::vec3 position { 0.0f, 0.0f, 0.0f };
		const float radius { 30.0f };
		const auto start = std::chrono::system_clock::now();
		std::uint16_t counter = 0;
		scene->EachInRadius<CPhysicsComponent>( position, radius, [&counter] ( const std::shared_ptr<const CEntity> &entity )
		{
			counter++;
		} );
		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> diff = end - start;
		CLogger::Log( "Time iterate " + std::to_string( counter ) + " entities: " + std::to_string( diff.count() * 1000.0f ) + " ms\n" );
	}

	return( 0 );
}

