#include "CHealthSystem.hpp"

#include "CLogger.hpp"

void CHealthSystem::Run()
{
	std::vector< CEntity > entitiesForDeletion;

	m_ecs.ForEach< CHealthComponent >( [ &entitiesForDeletion ] ( const auto &healthEntity, auto healthComponent )
	{ 
		if( healthComponent->health <= 0.0f )
		{
			entitiesForDeletion.push_back( healthEntity );
		}
	} );

	for( const auto &entity : entitiesForDeletion )
	{
		m_ecs.Destroy( entity );
	}

	if( entitiesForDeletion.size() > 0 )
	{
		CLogger::Log( "deleted " + std::to_string( entitiesForDeletion.size() ) + " entities" );
	}
}