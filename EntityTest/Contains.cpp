#include "Contains.hpp"

#include <glm/gtx/norm.hpp>

bool Contains( const CBoundingBox &box, const glm::vec3 &position )
{
	if( ( box.Max().x < position.x )
		||
		( box.Min().x > position.x )
		||
		( box.Max().y < position.y )
		||
		( box.Min().y > position.y )
		||
		( box.Max().z < position.z )
		||
		( box.Min().z > position.z ) )
	{
		return( false );
	}

	return( true );
}

bool Contains( const CSphere &sphere, const glm::vec3 &position )
{
	if( glm::length2( sphere.Position() - position ) <= std::pow( sphere.Radius(), 2 ) )
	{
		return( true );
	}

	return( false );
}