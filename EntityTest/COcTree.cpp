#include "COcTree.hpp"

const float COcTree::sMinSize = 10.0f;

COcTree::COcTree( const CBoundingBox &region ) :
	m_region { region }
{
	// TODO create all the needed nodes here, not dynamically during runtime

	const auto dimensions = m_region.Dimensions();

	// don't create child nodes if we are already at the minimal size
	if( !( ( dimensions.x <= sMinSize ) && ( dimensions.y <= sMinSize ) && ( dimensions.z <= sMinSize ) ) )
	{
		const auto min = m_region.Min();
		const auto max = m_region.Max();
		const auto center = m_region.Center();

		// TODO
		m_childNodes = std::make_unique< std::array< COcTree, 8 > >( std::array< COcTree, 8 >{
			CBoundingBox( {                    min.x,                    min.y,                    min.z }, { center.x,                 center.y,                 center.z } ),
			CBoundingBox( { ( min.x + max.x ) / 2.0f,                    min.y,                    min.z }, {    max.x, ( min.y + max.y ) / 2.0f, ( min.z + max.z ) / 2.0f } ),
			CBoundingBox( {                    min.x, ( min.y + max.y ) / 2.0f, ( min.z + max.z ) / 2.0f }, { center.x,                    max.y, ( min.z + max.z ) / 2.0f } ),
			CBoundingBox( {                 center.x,                 center.y,                    min.z }, {    max.x,                    max.y, ( min.z + max.z ) / 2.0f } ),
			CBoundingBox( { -5.0f, -5.0f, -5.0f }, { 5.0f, 5.0f, 5.0f } ), // TODO
			CBoundingBox( { -5.0f, -5.0f, -5.0f }, { 5.0f, 5.0f, 5.0f } ), // TODO
			CBoundingBox( { -5.0f, -5.0f, -5.0f }, { 5.0f, 5.0f, 5.0f } ), // TODO
			CBoundingBox( {                 center.x,                 center.y,                 center.z }, {    max.x,                     max.y,                   max.z } ) } );
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
