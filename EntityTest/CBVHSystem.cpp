#include "CBVHSystem.hpp"

void CBVHSystem::Process()
{
	m_octree.Clear();

	m_ecs.ForEach<CTransform>( [ this ] ( const auto &transformEntity, const auto transformComponent )
	{
		auto const boundingBox = m_ecs.GetComponent< CBoundingBox >( transformEntity );

		m_octree.Add( transformEntity, *transformComponent, boundingBox );
	} );
}
