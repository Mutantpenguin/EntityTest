#include "Contains.hpp"

#include <glm/gtx/norm.hpp>

#include "Distance.hpp"

#include "ext/minitrace/minitrace.h"

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
	if( glm::length2( spherePosition - point ) <= sphere.Radius2() )
	{
		return( true );
	}

	return( false );
}

bool Contains( const CFrustum &frustum, const glm::vec3 &point )
{
	// TODO multithreaded?
	for( const CPlane &plane : frustum.Planes() )
	{
		if( Distance( plane, point ) < 0 )
		{
			return( false );
		}
	}

	return( true );
}

bool Contains( const CFrustum &frustum, const glm::vec3 &spherePosition, const CSphere &sphere )
{
	// TODO multithreaded?
	for( const CPlane &plane : frustum.Planes() )
	{
		if( Distance( plane, spherePosition ) < -sphere.Radius() )
		{
			return( false );
		}
	}

	return( true );
}

bool Contains( const CFrustum &frustum, const glm::vec3 &boxPosition, const CBoundingBox &box )
{
	const glm::vec3 max = box.Max( boxPosition );
	const glm::vec3 min = box.Min( boxPosition );

	auto		ret = true;
	glm::vec3	vmin, vmax;

	for( const auto &plane : frustum.Planes() )
	{
		const auto &normal = plane.Normal();
		const auto &distance = plane.Distance();

		// X axis 
		if( normal.x > 0 )
		{
			vmin.x = min.x;
			vmax.x = max.x;
		}
		else
		{
			vmin.x = max.x;
			vmax.x = min.x;
		}

		// Y axis 
		if( normal.y > 0 )
		{
			vmin.y = min.y;
			vmax.y = max.y;
		}
		else
		{
			vmin.y = max.y;
			vmax.y = min.y;
		}

		// Z axis 
		if( normal.z > 0 )
		{
			vmin.z = min.z;
			vmax.z = max.z;
		}
		else
		{
			vmin.z = max.z;
			vmax.z = min.z;
		}

		if( ( glm::dot( normal, vmin ) + distance ) > 0 )
		{
			return( false );
		}
	}

	return( ret );
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