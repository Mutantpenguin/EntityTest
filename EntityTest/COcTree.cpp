#include "COcTree.hpp"

#include "CLogger.hpp"

const float COcTree::sMinSize = 10.0f;

COcTree::COcTree( const CBoundingBox &region ) :
	m_region { region }
{
	// create all the needed nodes here, not dynamically during runtime
	
	m_entities.reserve( 1000 );

	const auto dimensions = m_region.Dimensions();

	// don't create child nodes if we are already at the minimal size
	if( !( ( dimensions.x <= sMinSize ) && ( dimensions.y <= sMinSize ) && ( dimensions.z <= sMinSize ) ) )
	{
		const auto min = m_region.Min();
		const auto max = m_region.Max();
		const auto center = m_region.Center();

		m_childNodes = std::make_unique< std::array< COcTree, 8 > >( std::array< COcTree, 8 >{
			CBoundingBox( {    min.x,    min.y,    min.z }, { center.x, center.y, center.z } ), //  left, lower, front
			CBoundingBox( { center.x,    min.y,    min.z }, {    max.x, center.y, center.z } ), // right, lower, front
			CBoundingBox( {    min.x,    min.y, center.z }, { center.x, center.y,    max.z } ), //  left, lower, back
			CBoundingBox( { center.x,    min.y, center.z }, {    max.x, center.y,    max.z } ), // right, lower, back
			CBoundingBox( {    min.x, center.y,    min.z }, { center.x,    max.y, center.z } ), //  left, upper, front
			CBoundingBox( { center.x, center.y,    min.z }, {    max.x,    max.y, center.z } ), // right, upper, front
			CBoundingBox( {    min.x, center.y, center.z }, { center.x,    max.y,    max.z } ), //  left, upper, back
			CBoundingBox( { center.x, center.y, center.z }, {    max.x,    max.y,    max.z } )  // right, upper, back
			} );
	}
}

void COcTree::Clear()
{
	m_containsEntities = false;

	m_entities.clear();

	if( m_childNodes )
	{
		for( auto &node : *m_childNodes )
		{
			if( node.m_containsEntities )
			{
				node.Clear();
			}
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
	
	m_containsEntities = true;

	if( m_childNodes )
	{
		// try to insert it into any child node
		for( auto &node : *m_childNodes )
		{
			if( node.Add( entity, transform, boundingBox ) )
			{
				return( true );
			}
		}
	}

	// didn't fit into any child node, so put it inside current one
	m_entities.push_back( entity );
	
	return( true );
}

void COcTree::ForEachIn( const CSphere &sphere, const std::function< void( const CEntity &entity ) > lambda )
{
	// TODO implement
}

bool COcTree::ExistsIn( const CSphere &sphere, const std::function< bool( const CEntity &entity ) > lambda ) const
{
	// TODO implement
	/*
	if( lambda( m_entities[ i ], &m_objects[ i ] ) )
	{
		return( true );
	}*/
	return( false );
}