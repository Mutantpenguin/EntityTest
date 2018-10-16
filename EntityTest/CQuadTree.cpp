/* TODO
#include "CQuadTree.hpp"

#include "CLogger.hpp"

#include "Intersection.hpp"
#include "Contains.hpp"

#include "minitrace.h"

const float CQuadTree::sMinSize = 50.0f;

CQuadTree::CQuadTree( const CBoundingBox &region ) :
	m_region { region }
{
	m_children.reserve( 1000 );

	// create all the needed nodes here, not dynamically during runtime
	const auto dimensions = m_region.Dimensions();

	// don't create octants if we are already at the minimal size
	if( !( ( dimensions.x <= sMinSize ) && ( dimensions.y <= sMinSize ) ) )
	{
		const auto &min = m_region.Min();
		const auto &max = m_region.Max();
		const auto center = m_region.Center();

		m_octants = std::make_unique< std::array< CQuadTree, 4 > >( std::array< CQuadTree, 4 >{
				CQuadTree( CBoundingBox( { min.x,       min.y, min.z }, { center.x, center.y, max.z } ) ), //  left, front
				CQuadTree( CBoundingBox( { center.x,    min.y, min.z }, {    max.x, center.y, max.z } ) ), // right, front
				CQuadTree( CBoundingBox( { min.x,    center.y, min.z }, { center.x,    max.y, max.z } ) ), //  left, back
				CQuadTree( CBoundingBox( { center.x, center.y, min.z }, {    max.x,    max.y, max.z } ) ), // right, back
		} );
	}
}

void CQuadTree::Clear()
{
	if( m_containsEntities )
	{
		m_containsEntities = false;

		m_children.clear();

		if( m_octants )
		{
			for( auto &octant : *m_octants )
			{
				octant.Clear();
			}
		}
	}
}

bool CQuadTree::Add( const CEntity &entity, const CTransform &transform, const CBoundingBox * const boundingBox )
{
	if( boundingBox )
	{
		if( Intersection( m_region, *boundingBox ) != eIntersectionType::INSIDE )
		{
			return( false );
		}
	}
	else
	{
		if( !Contains( m_region, transform.Position ) )
		{
			return( false );
		}
	}

	m_containsEntities = true;

	if( m_octants )
	{
		// try to insert it into the first fitting octant
		for( auto &octant : *m_octants )
		{
			if( octant.Add( entity, transform, boundingBox ) )
			{
				return( true );
			}
		}
	}

	// didn't fit into any octant, so put it inside current one
	m_children.push_back( std::make_tuple( entity, transform, ( nullptr == boundingBox ? nullptr : std::make_unique< CBoundingBox >( *boundingBox ) ) ) );

	return( true );
}

void CQuadTree::ForEach( const std::function< void( const CEntity &entity ) > lambda )
{
	MTR_SCOPE( "CQuadTree", "CQuadTree::ForEach" );

	if( m_containsEntities )
	{
		for( const auto &child : m_children )
		{
			lambda( std::get<0>( child ) );
		}

		if( m_octants )
		{
			for( auto &octant : *m_octants )
			{
				octant.ForEach( lambda );
			}
		}
	}
}

void CQuadTree::ForEachIn( const CSphere &sphere, const std::function< void( const CEntity &entity ) > lambda )
{
	MTR_SCOPE( "CQuadTree", "CQuadTree::ForEachIn" );

	if( m_containsEntities )
	{
		switch( Intersection( sphere, m_region ) )
		{
		case eIntersectionType::INSIDE:
			ForEach( lambda );
			break;

		case eIntersectionType::INTERSECT:
			for( const auto &child : m_children )
			{
				const auto &boundingBox = std::get<2>( child );

				if( boundingBox )
				{
					if( Intersection( sphere, *boundingBox ) != eIntersectionType::OUTSIDE )
					{
						lambda( std::get<0>( child ) );
					}
				}
				else
				{
					if( Contains( sphere, std::get<1>( child ).Position ) )
					{
						lambda( std::get<0>( child ) );
					}
				}
			}

			if( m_octants )
			{
				for( auto &octant : *m_octants )
				{
					octant.ForEachIn( sphere, lambda );
				}
			}

			break;
		
		case eIntersectionType::OUTSIDE:
			break;
		}
	}
}

bool CQuadTree::Exists( const std::function< bool( const CEntity &entity ) > lambda ) const
{
	MTR_SCOPE( "CQuadTree", "CQuadTree::Exists" );

	if( m_containsEntities )
	{
		for( const auto &child : m_children )
		{
			if( lambda( std::get<0>( child ) ) )
			{
				return( true );
			}
		}

		if( m_octants )
		{
			for( auto &octant : *m_octants )
			{
				if( octant.Exists( lambda ) )
				{
					return( true );
				}
			}
		}
	}

	return( false );
}

bool CQuadTree::ExistsIn( const CSphere &sphere, const std::function< bool( const CEntity &entity ) > lambda ) const
{
	MTR_SCOPE( "CQuadTree", "CQuadTree::ExistsIn" );

	if( m_containsEntities )
	{
		switch( Intersection( sphere, m_region ) )
		{
		case eIntersectionType::INSIDE:
			return( Exists( lambda ) );
			break;

		case eIntersectionType::INTERSECT:
			for( const auto &child : m_children )
			{
				const auto &boundingBox = std::get<2>( child );

				if( boundingBox )
				{
					if( Intersection( sphere, *boundingBox ) != eIntersectionType::OUTSIDE )
					{
						if( lambda( std::get<0>( child ) ) )
						{
							return( true );
						}
					}
				}
				else
				{
					if( Contains( sphere, std::get<1>( child ).Position ) )
					{
						if( lambda( std::get<0>( child ) ) )
						{
							return( true );
						}
					}
				}
			}

			if( m_octants )
			{
				for( auto &octant : *m_octants )
				{
					if( octant.ExistsIn( sphere, lambda ) )
					{
						return( true );
					}
				}
			}

			break;
		
		case eIntersectionType::OUTSIDE:
			break;
		}
	}

	return( false );
}
*/