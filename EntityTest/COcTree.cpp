#include "COcTree.hpp"

#include "CLogger.hpp"

#include "Intersection.hpp"
#include "Contains.hpp"

#include "minitrace.h"

const float COcTree::sMinSize = 50.0f;

COcTree::COcTree( const glm::vec3 &position, const CBoundingBox &region ) :
	m_position { position },
	m_region { region }
{
	m_children.reserve( 1000 );

	// create all the needed nodes here, not dynamically during runtime
	const auto dimensions = m_region.Dimensions();

	// don't create octants if we are already at the minimal size
	if( !( ( dimensions.x <= sMinSize ) && ( dimensions.y <= sMinSize ) && ( dimensions.z <= sMinSize ) ) )
	{
		const auto childsize = m_region.Size() / 2.0f;

		m_octants = std::make_unique< std::array< COcTree, 8 > >( std::array< COcTree, 8 >{
				COcTree( position + glm::vec3( -childsize.x, -childsize.y, -childsize.z ), CBoundingBox( childsize ) ), //  left, lower, front
				COcTree( position + glm::vec3(  childsize.x, -childsize.y, -childsize.z ), CBoundingBox( childsize ) ), // right, lower, front
				COcTree( position + glm::vec3( -childsize.x, -childsize.y,  childsize.z ), CBoundingBox( childsize ) ), //  left, lower, back
				COcTree( position + glm::vec3(  childsize.x, -childsize.y,  childsize.z ), CBoundingBox( childsize ) ), // right, lower, back
				COcTree( position + glm::vec3( -childsize.x,  childsize.y, -childsize.z ), CBoundingBox( childsize ) ), //  left, upper, front
				COcTree( position + glm::vec3(  childsize.x,  childsize.y, -childsize.z ), CBoundingBox( childsize ) ), // right, upper, front
				COcTree( position + glm::vec3( -childsize.x,  childsize.y,  childsize.z ), CBoundingBox( childsize ) ), //  left, upper, back
				COcTree( position + glm::vec3(  childsize.x,  childsize.y,  childsize.z ), CBoundingBox( childsize ) )  // right, upper, back
			} );
	}
}

void COcTree::Clear()
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

bool COcTree::Add( const CEntity &entity, const glm::vec3 &position, const CBoundingBox * const boundingBox )
{
	if( boundingBox )
	{
		if( Intersection( m_position, m_region, position, *boundingBox ) != eIntersectionType::INSIDE )
		{
			return( false );
		}
	}
	else
	{
		if( !Contains( m_position, m_region, position ) )
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
			if( octant.Add( entity, position, boundingBox ) )
			{
				return( true );
			}
		}
	}

	// didn't fit into any octant, so put it inside current one
	m_children.push_back( std::make_tuple( entity, position, ( boundingBox ? std::make_optional< CBoundingBox >( *boundingBox ) : std::nullopt ) ) );
	
	return( true );
}

void COcTree::ForEach( const std::function< void( const CEntity &entity ) > lambda )
{
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

void COcTree::ForEachIn( const glm::vec3 &spherePosition, const CSphere &sphere, const std::function< void( const CEntity &entity ) > lambda )
{
	if( m_containsEntities )
	{
		switch( Intersection( spherePosition, sphere, m_position, m_region ) )
		{
		case eIntersectionType::INSIDE:
			ForEach( lambda );
			break;

		case eIntersectionType::INTERSECT:
			for( const auto &[ entity, position, boundingBox ] : m_children )
			{
				if( boundingBox.has_value() )
				{
					if( Intersection( spherePosition, sphere, position, boundingBox.value() ) != eIntersectionType::OUTSIDE )
					{
						lambda( entity );
					}
				}
				else
				{
					if( Contains( spherePosition, sphere, position ) )
					{
						lambda( entity );
					}
				}
			}

			if( m_octants )
			{
				for( auto &octant : *m_octants )
				{
					octant.ForEachIn( spherePosition, sphere, lambda );
				}
			}

			break;
		
		case eIntersectionType::OUTSIDE:
			break;
		}
	}
}

bool COcTree::Exists( const std::function< bool( const CEntity &entity ) > lambda ) const
{
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

bool COcTree::ExistsIn( const glm::vec3 &spherePosition, const CSphere &sphere, const std::function< bool( const CEntity &entity ) > lambda ) const
{
	if( m_containsEntities )
	{
		switch( Intersection( spherePosition, sphere, m_position, m_region ) )
		{
		case eIntersectionType::INSIDE:
			return( Exists( lambda ) );
			break;

		case eIntersectionType::INTERSECT:
			for( const auto &[ entity, position, boundingBox ] : m_children )
			{
				if( boundingBox.has_value() )
				{
					if( Intersection( spherePosition, sphere, position, boundingBox.value() ) != eIntersectionType::OUTSIDE )
					{
						if( lambda( entity ) )
						{
							return( true );
						}
					}
				}
				else
				{
					if( Contains( spherePosition, sphere, position ) )
					{
						if( lambda( entity ) )
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
					if( octant.ExistsIn( spherePosition, sphere, lambda ) )
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