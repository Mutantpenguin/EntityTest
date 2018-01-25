#include "COcTree.hpp"

const float COcTree::sMinSize = 1.0f;

COcTree::COcTree( const CBoundingBox &region ) :
	m_region { region }
{}


COcTree::~COcTree()
{}

void COcTree::AddEntity( const std::shared_ptr<CEntity>& entity )
{
	const auto dimensions = m_region.Max() - m_region.Min();

	if( ( dimensions.x <= sMinSize ) && ( dimensions.y <= sMinSize ) && ( dimensions.z <= sMinSize ) )
	{
		m_entities.insert( entity );
	}
	else
	{
		const auto center = dimensions / 2.0f;

		std::array<std::unique_ptr<COcTree>, 8> nodes;

		for( std::uint8_t i = 0; i < 8; i++ )
		{
			if( m_childNodes[ i ] == nullptr )
			{
				// TODO how to correctly calculate each node?
				nodes[ i ] = std::make_unique<COcTree>( CBoundingBox( glm::vec3 { 0.0f, 0.0f, 0.0f }, glm::vec3 { 0.0f, 0.0f, 0.0f } ) );
			}
			else
			{
				nodes[ i ] = std::move( m_childNodes[ i ] );
			}
		}

		for( auto &node : nodes )
		{
			if( node->m_region.Intersect( entity->BoundingBox ) == CBoundingBox::eIntersectionType::INSIDE )
			{
				node->AddEntity( entity );
				break;
			}
		}

		for( std::uint8_t i = 0; i < 8; i++ )
		{
			if( nodes[ i ]->m_entities.size() > 0 )
			{
				m_childNodes[ i ] = std::move( nodes[ i ] );
			}
			else
			{
				m_childNodes[ i ] = nullptr;
			}
		}

		if( 1 == 1 )
		{

		}
		else
		{
			m_entities.insert( entity );
		}
	}
}
