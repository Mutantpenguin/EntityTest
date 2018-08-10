#include "CBVHSystem.hpp"

#include <chrono>

void CBVHSystem::Process()
{
	const auto start = std::chrono::system_clock::now();

	m_octree.Clear();

	m_ecs.ForEach<CTransform>( [ this ] ( const auto &transformEntity, const auto transformComponent )
	{
		auto const boundingBox = m_ecs.GetComponent< CBoundingBox >( transformEntity );

		m_octree.Add( transformEntity, *transformComponent, boundingBox );
	} );

	const auto end = std::chrono::system_clock::now();
	const std::chrono::duration<double> diff = end - start;
	CLogger::Log( "rebuilding BVH: " + std::to_string( diff.count() * 1000.0f ) + " ms" );
}
