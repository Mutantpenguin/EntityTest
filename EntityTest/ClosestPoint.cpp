#include "ClosestPoint.hpp"

glm::vec3 ClosestPoint( const glm::vec3 &boxPosition, const CBoundingBox &box, const glm::vec3 &point )
{
	const glm::vec3 max = box.Max( boxPosition );
	const glm::vec3 min = box.Min( boxPosition );

	glm::vec3 result;

	if( point.x > max.x )
	{
		result.x = max.x;
	}
	else if( point.x < min.x )
	{
		result.x = min.x;
	}
	else
	{
		result.x = point.x;
	}

	if( point.y > max.y )
	{
		result.y = max.y;
	}
	else if( point.y < min.y )
	{
		result.y = min.y;
	}
	else
	{
		result.y = point.y;
	}

	if( point.z > max.z )
	{
		result.z = max.z;
	}
	else if( point.z < min.z )
	{
		result.z = min.z;
	}
	else
	{
		result.z = point.z;
	}

	return( result );
}

glm::vec3 ClosestPoint( const CSphere &sphere, const glm::vec3 &position )
{
	return( sphere.Position() + ( glm::normalize( position - sphere.Position() ) * sphere.Radius() ) );
}