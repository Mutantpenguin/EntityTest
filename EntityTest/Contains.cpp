#include "Contains.hpp"

#include <glm/gtx/norm.hpp>

#include "minitrace.h"

bool Contains( const CBoundingBox &box, const glm::vec3 &position )
{
	MTR_SCOPE( "Contains", "Contains box <-> position" );

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
	MTR_SCOPE( "Contains", "Contains sphere <-> position" );

	if( glm::length2( sphere.Position() - position ) <= std::pow( sphere.Radius(), 2 ) )
	{
		return( true );
	}

	return( false );
}