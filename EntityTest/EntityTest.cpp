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
	auto scene = std::make_shared<CScene>();

	{
		auto gnahEntity = scene->CreateEntity( "gnah" );

		auto cam = gnahEntity->Add<CCameraFreeComponent>( 800.0f / 600.0f, 90.0f, 0.0f, 100.f );
		auto phy = gnahEntity->Add<CPhysicsComponent>();

		// TODO gnahEntity->Remove<CCameraFreeComponent>();

		if( gnahEntity->HasComponents<CPhysicsComponent>() )
		{
			CLogger::Log( "has physics" );
		}

		if( gnahEntity->HasComponents<CCameraFreeComponent>() )
		{
			CLogger::Log( "has camera" );
		}

		if( gnahEntity->HasComponents<CPlayerComponent>() )
		{
			CLogger::Log( "is a player" );
		}
		else
		{
			CLogger::Log( "is a NOT player" );
		}

		if( gnahEntity->HasComponents<CPhysicsComponent, CCameraFreeComponent>() )
		{
			CLogger::Log( "has physics AND camera" );
		}

		if( gnahEntity->HasComponents<CPhysicsComponent, CPlayerComponent>() )
		{
			CLogger::Log( "has physics AND player" );
		}
	}

	{
		const auto start = std::chrono::system_clock::now();
		for( int i = 10; i < 10000; i++ )
		{
			auto ent = scene->CreateEntity( "entity_" + std::to_string( i ) );

			if( rand() % 10 == 2 )
			{
				ent->Add<CPhysicsComponent>();
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
		CLogger::Log( "creating entities : " + std::to_string( diff.count() ) + " s\n" );
	}

	{
		const auto start = std::chrono::system_clock::now();
		const auto componentsWithPhysics = scene->GetEntitiesWithComponents<CPhysicsComponent>();
		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> diff = end - start;
		CLogger::Log( "Time to fill and iterate a vector of " + std::to_string( componentsWithPhysics.size() ) + " : " + std::to_string( diff.count() ) + " s\n" );

		if( componentsWithPhysics.size() > 0 )
		{
			CLogger::Log( "entities with physics:" );
			for( const auto entity : componentsWithPhysics )
			{
				//CLogger::Log("\t - " + entity->Name());
			}
		}
	}

	{
		const auto start = std::chrono::system_clock::now();
		const auto componentsWithPhysicsAndPlayer = scene->GetEntitiesWithComponents<CPhysicsComponent, CPlayerComponent>();
		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> diff = end - start;
		CLogger::Log( "Time to fill and iterate a vector of " + std::to_string( componentsWithPhysicsAndPlayer.size() ) + " : " + std::to_string( diff.count() ) + " s\n" );

		if( componentsWithPhysicsAndPlayer.size() > 0 )
		{
			CLogger::Log( "entities with physics and player:" );
			for( const auto entity : componentsWithPhysicsAndPlayer )
			{
				//CLogger::Log("\t - " + entity->Name());
			}
		}
	}

	{
		const auto start = std::chrono::system_clock::now();
		//scene->Each<CCameraFreeComponent>([](const std::shared_ptr<const CEntity> &entity)
		scene->Each<CPhysicsComponent, CPlayerComponent>( [] ( const std::shared_ptr<const CEntity> &entity )
		{
			//CLogger::Log("\t - " + entity->Name() + " / " + entity->Get<CPlayerComponent>()->Team);
			const auto blah1 = entity->Get<CPlayerComponent>();
			const auto mult = blah1->Team * blah1->Team;
			//const auto blah1 = entity->Get<CPlayerComponent>();

			const auto blah3 = entity->Get<CCameraFreeComponent>();
		} );
		const auto end = std::chrono::system_clock::now();
		const std::chrono::duration<double> diff = end - start;
		CLogger::Log( "Time iterate: " + std::to_string( diff.count() ) + " s\n" );
	}

	return( 0 );
}

