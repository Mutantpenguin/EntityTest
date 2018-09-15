#include "ClosestPoint.hpp"

glm::vec3 ClosestPoint( const CBoundingBox &box, const glm::vec3 &position )
{
	glm::vec3 result;

	if( position.x > box.Max().x )
	{
		result.x = box.Max().x;
	}
	else if( position.x < box.Min().x )
	{
		result.x = box.Min().x;
	}
	else
	{
		result.x = position.x;
	}

	if( position.y > box.Max().y )
	{
		result.y = box.Max().y;
	}
	else if( position.y < box.Min().y )
	{
		result.y = box.Min().y;
	}
	else
	{
		result.y = position.y;
	}

	if( position.z > box.Max().z )
	{
		result.z = box.Max().z;
	}
	else if( position.z < box.Min().z )
	{
		result.z = box.Min().z;
	}
	else
	{
		result.z = position.z;
	}

	return( result );
}

glm::vec3 ClosestPoint( const CSphere &sphere, const glm::vec3 &position )
{
	return( sphere.Position() + ( glm::normalize( position - sphere.Position() ) * sphere.Radius() ) );
}