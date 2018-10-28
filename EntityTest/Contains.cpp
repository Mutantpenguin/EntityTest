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

bool Contains( const CFrustum &frustum, const glm::vec3 &point )
{
	// TODO multithreaded?
	for( const CPlane &plane : frustum.m_planes )
	{
		if( plane.DistanceToPlane( point ) < 0 )
		{
			return( false );
		}
	}

	return( true );
}

bool Contains( const glm::vec3 &boxAPosition, const CBoundingBox &boxA, const glm::vec3 &boxBPosition, const CBoundingBox &boxB )
{
	const glm::vec3 maxA = boxA.Max( boxAPosition );
	const glm::vec3 minA = boxA.Min( boxAPosition );

	const glm::vec3 maxB = boxB.Max( boxBPosition );
	const glm::vec3 minB = boxB.Min( boxBPosition );

	if( ( minA.x > minB.x )
		||
		( maxA.x < maxB.x )
		||
		( minA.y > minB.y )
		||
		( maxA.y < maxB.y )
		||
		( minA.z > minB.z )
		||
		( maxA.z < maxB.z ) )
	{
		return( false );
	}
	
	return( true );
}