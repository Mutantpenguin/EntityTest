#include "Contains.hpp"

#include <glm/gtx/norm.hpp>

#include "minitrace.h"

bool Contains( const glm::vec3 &boxPosition, const CBoundingBox &box, const glm::vec3 &point )
{
	const glm::vec3 max = box.Max( boxPosition );
	const glm::vec3 min = box.Min( boxPosition );

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

bool Contains( const glm::vec3 &spherePosition, const CSphere &sphere, const glm::vec3 &point )
{
	if( glm::length2( spherePosition - point ) <= std::pow( sphere.Radius(), 2 ) )
	{
		return( true );
	}

	return( false );
}