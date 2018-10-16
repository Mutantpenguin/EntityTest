#include "CSpatialSystem.hpp"

#include <chrono>

#include <glm/gtx/string_cast.hpp>

#include "minitrace.h"

CSpatialSystem::CSpatialSystem( MyECS &ecs, const std::shared_ptr< CSpatialBase > &spatial ) :
	m_ecs { ecs },
	m_spatial { spatial }
{
	Process();
}

void CSpatialSystem::Process()
{
	MTR_SCOPE( "CSpatialSystem", "CSpatialSystem::Process" );

	CLogger::Log( "\tprocessing: CSpatialSystem" );
	
	const auto start = std::chrono::system_clock::now();

	m_spatial->Clear();
	
	std::vector< CEntity > entitiesForDeletion;

	m_ecs.ForEach<CSpatial>( [ this, &entitiesForDeletion ] ( const auto &transformEntity, const auto spatialComponent )
	{
		auto const boundingBox = m_ecs.GetComponent< CBoundingBox >( transformEntity );

		if( !m_spatial->Add( transformEntity, (*transformComponent).Position, boundingBox ) )
		{
			entitiesForDeletion.push_back( transformEntity );
		}
	} );
	
	for( const auto &entity : entitiesForDeletion )
	{
		m_ecs.Destroy( entity );
	}

	if( entitiesForDeletion.size() > 0 )
	{
		CLogger::Log( "\t\tdestroyed " + std::to_string( entitiesForDeletion.size() ) + " entities which dropped out of the world" );
	}

	const auto end = std::chrono::system_clock::now();
	const std::chrono::duration<double> diff = end - start;
	CLogger::Log( "\t\trebuilding spatial system: " + std::to_string( diff.count() * 1000.0f ) + " ms" );
}
