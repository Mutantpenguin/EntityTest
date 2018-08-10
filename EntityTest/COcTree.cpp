#include "COcTree.hpp"

const float COcTree::sMinSize = 5.0f;

COcTree::COcTree( const CBoundingBox &region ) :
	m_region { region }
{
	// TODO create all the needed nodes here, not dynamically during runtime

	const auto dimensions = m_region.Dimensions();

	if( !( ( dimensions.x <= sMinSize ) && ( dimensions.y <= sMinSize ) && ( dimensions.z <= sMinSize ) ) )
	{
		// TODO
		m_childNodes = std::make_unique< std::array< COcTree, 8 > >();
	}

	/* TODO
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
	}
	*/
}

void COcTree::Clear()
{
	m_containsEntities = false;

	m_entities.clear();

	if( m_childNodes )
	{
		for( auto &node : *m_childNodes )
		{
			node.Clear();
		}
	}
}

bool COcTree::Add( const CEntity &entity, const CTransform &transform, const CBoundingBox * const boundingBox )
{
	if( boundingBox )
	{
		if( m_region.Intersect( *boundingBox ) != CBoundingBox::eIntersectionType::INSIDE )
		{
			return( false );
		}
	}
	else
	{
		if( m_region.Intersect( transform.Position ) != CBoundingBox::eIntersectionType::INSIDE )
		{
			return( false );
		}
	}

	if( m_childNodes )
	{
		// try to insert it into any child node
		for( auto &node : *m_childNodes )
		{
			if( node.Add( entity, transform, boundingBox ) )
			{
				m_containsEntities = true;
				return( true );
			}
		}
	}

	// didn't fit into any child node, so put it inside current one
	m_entities.push_back( entity );
	
	m_containsEntities = true;
	
	return( true );
}
