#include "Contains.hpp"

#include <glm/gtx/norm.hpp>

#include "minitrace.h"

bool Contains( const glm::vec3 &position, const CBoundingBox &box, const glm::vec3 &point )
{
	MTR_SCOPE( "Contains", "Contains box <-> point" );

	const glm::vec3 max = box.Max( position );
	const glm::vec3 min = box.Min( position );

	if( ( max.x < point.x )
		||
		( min.x > point.x )
		||
		( max.y < point.y )
		||
		( min.y > point.y )
		||
		( max.z < point.z )
		||
		( min.z > point.z ) )
	{
		return( false );
	}

	return( true );
}

bool Contains( const CSphere &sphere, const glm::vec3 &point )
{
	MTR_SCOPE( "Contains", "Contains sphere <-> point" );

	if( glm::length2( sphere.Position() - point ) <= std::pow( sphere.Radius(), 2 ) )
	{
		return( true );
	}

	return( false );
}