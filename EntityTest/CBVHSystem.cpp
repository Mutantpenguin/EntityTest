#include "CBVHSystem.hpp"

#include <chrono>

#include <glm/gtx/string_cast.hpp>

CBVHSystem::CBVHSystem( MyECS &ecs, const std::shared_ptr< CBVHBase > &bvh ) :
	m_ecs { ecs },
	m_bvh( bvh)
{
	Process();
}

void CBVHSystem::Process()
{
	CLogger::Log( "\tprocessing: CBVHSystem" );
	
	const auto start = std::chrono::system_clock::now();

	m_bvh->Clear();
	
	std::vector< CEntity > entitiesForDeletion;

	m_ecs.ForEach<CTransform>( [ this, &entitiesForDeletion ] ( const auto &transformEntity, const auto transformComponent )
	{
		auto const boundingBox = m_ecs.GetComponent< CBoundingBox >( transformEntity );

		if( !m_bvh->Add( transformEntity, *transformComponent, boundingBox ) )
		{
			entitiesForDeletion.push_back( transformEntity );
			CLogger::Log( "entity '" + std::to_string( transformEntity.Id() ) + "' lies outside of the OCTree: " + glm::to_string( transformComponent->Position ) );
		}
	} );
	
	for( const auto &entity : entitiesForDeletion )
	{
		m_ecs.Destroy( entity );
	}

	if( entitiesForDeletion.size() > 0 )
	{
		CLogger::Log( "destroyed " + std::to_string( entitiesForDeletion.size() ) + " entities which dropped out of the world" );
	}

	const auto end = std::chrono::system_clock::now();
	const std::chrono::duration<double> diff = end - start;
	CLogger::Log( "rebuilding BVH: " + std::to_string( diff.count() * 1000.0f ) + " ms" );
}
