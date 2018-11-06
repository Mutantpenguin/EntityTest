#include "CBVHSystem.hpp"

#include <chrono>

#include <glm/gtx/string_cast.hpp>

#include "minitrace.h"

CBVHSystem::CBVHSystem( MyECS &ecs, const std::shared_ptr< CBVHBase > &bvh ) :
	m_ecs { ecs },
	m_bvh { bvh }
{
	Process();
}

void CBVHSystem::Process()
{
	MTR_BEGIN( "CBVHSystem", "CBVHSystem::Process" );

	CLogger::Debug( "\tprocessing: CBVHSystem" );
	
	const auto start = std::chrono::high_resolution_clock::now();

	m_bvh->Clear();
	
	std::vector< CEntity > entitiesForDeletion;

	m_ecs.ForEach<CTransformComponent>( [ this, &entitiesForDeletion ] ( const auto &transformEntity, const auto spatialComponent )
	{
		auto const boundingBox = m_ecs.GetComponent<CBoundingBoxComponent>( transformEntity );

		if( !m_bvh->Add( transformEntity, spatialComponent->Position, boundingBox ) )
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
		CLogger::Debug( "\t\tdestroyed " + std::to_string( entitiesForDeletion.size() ) + " entities which dropped out of the world" );
	}

	const auto end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> diff = end - start;
	CLogger::Debug( "\t\trebuilding bvh system: " + std::to_string( diff.count() * 1000.0f ) + " ms" );
	
	MTR_END( "CBVHSystem", "CBVHSystem::Process" );
}
