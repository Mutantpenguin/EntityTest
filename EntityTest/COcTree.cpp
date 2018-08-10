#include "COcTree.hpp"

const float COcTree::sMinSize = 5.0f;

COcTree::COcTree( const CBoundingBox &region ) :
	m_region { region }
{}

void COcTree::Clear()
{
	for( auto &note : m_childNodes )
	{
		note.reset();
	}
}

void COcTree::Add( const CEntity &entity, const CTransform &transform, const CBoundingBox * const boundingBox )
{
	const auto dimensions = m_region.Dimensions();

	if( ( dimensions.x <= sMinSize ) && ( dimensions.y <= sMinSize ) && ( dimensions.z <= sMinSize ) )
	{
		m_entities.push_back( entity );
	}
	else
	{
		const auto center = m_region.Center();

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
			if( boundingBox )
			{
				if( node->m_region.Intersect( *boundingBox ) == CBoundingBox::eIntersectionType::INSIDE )
				{
					node->Add( entity, transform, boundingBox );
					break;
				}
			}
			else
			{
				if( node->m_region.Intersect( transform.Position ) == CBoundingBox::eIntersectionType::INSIDE )
				{
					node->Add( entity, transform, boundingBox );
					break;
				}
			}
		}

		// TODO wtf??
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

		if( 1 == 2 )
		{

		}
		else
		{
			m_entities.push_back( entity );
		}
	}
}
