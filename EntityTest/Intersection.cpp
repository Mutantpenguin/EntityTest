#include "Intersection.hpp"

#include <glm/gtx/norm.hpp>

#include "Contains.hpp"
#include "ClosestPoint.hpp"
#include "Distance.hpp"

#include "ext/minitrace/minitrace.h"

eIntersectionType Intersection( const glm::vec3 &boxAPosition, const CBoundingBox &boxA, const glm::vec3 &boxBPosition, const CBoundingBox &boxB )
{
	const glm::vec3 maxA = boxA.Max( boxAPosition );
	const glm::vec3 minA = boxA.Min( boxAPosition );

	const glm::vec3 maxB = boxB.Max( boxBPosition );
	const glm::vec3 minB = boxB.Min( boxBPosition );

	if( ( maxA.x < minB.x )
		||
		( minA.x > maxB.x )
		||
		( maxA.y < minB.y )
		||
		( minA.y > maxB.y )
		||
		( maxA.z < minB.z )
		||
		( minA.z > maxB.z ) )
	{
		return( eIntersectionType::OUTSIDE );
	}

	if( ( minA.x <= minB.x )
		&&
		( maxA.x >= maxB.x )
		&&
		( minA.y <= minB.y )
		&&
		( maxA.y >= maxB.y )
		&&
		( minA.z <= minB.z )
		&&
		( maxA.z >= maxB.z ) )
	{
		return( eIntersectionType::INSIDE );
	}

	return( eIntersectionType::INTERSECT );
}

eIntersectionType Intersection( const glm::vec3 &boxPosition, const CBoundingBox &box, const glm::vec3 &spherePosition, const CSphere &sphere )
{
	if( sphere.Radius2() >= glm::length2( spherePosition - ClosestPoint( boxPosition, box, spherePosition ) ) )
	{
		if( Contains( spherePosition, sphere, box.Min( boxPosition ) )
			&&
			Contains( spherePosition, sphere, box.Max( boxPosition ) ) )
		{
			return( eIntersectionType::INSIDE );
		}

		return( eIntersectionType::INTERSECT );
	}

	return( eIntersectionType::OUTSIDE );
}

eIntersectionType Intersection( const glm::vec3 &sphereAPosition, const CSphere &sphereA, const glm::vec3 &sphereBPosition, const CSphere &sphereB )
{
    const glm::vec3 distance = sphereAPosition - sphereBPosition;
	
	if( sphereA.Radius() >= ( glm::length( distance ) + sphereB.Radius() ) )
	{
		return( eIntersectionType::INSIDE );
	}
	else
	{
		const f16 squaredDistance = glm::dot( distance, distance ); // same as squared length of distance
		
		// Spheres intersect if squared distance is less than squared sum of radii
		if( squaredDistance <= std::pow( sphereA.Radius() + sphereB.Radius(), 2 ) )
		{
			return( eIntersectionType::INTERSECT );
		}
	}
	
	return( eIntersectionType::OUTSIDE );
}

eIntersectionType Intersection( const glm::vec3 &spherePosition, const CSphere &sphere, const glm::vec3 &boxPosition, const CBoundingBox &box )
{
	const auto &radiusSquared = sphere.Radius2();
	
	if( radiusSquared >= glm::length2( spherePosition - ClosestPoint( boxPosition, box, spherePosition ) ) )
	{
		if( ( radiusSquared >= glm::length2( spherePosition - box.Min( boxPosition ) ) )
			&&
			( radiusSquared >= glm::length2( spherePosition - box.Max( boxPosition ) ) ) )
		{
			return( eIntersectionType::INSIDE );
		}
		
		return( eIntersectionType::INTERSECT );
	}
	
	return( eIntersectionType::OUTSIDE );
}

eIntersectionType Intersection( const CFrustum &frustum, const glm::vec3 &boxPosition, const CBoundingBox &box )
{
	const glm::vec3 max = box.Max( boxPosition );
	const glm::vec3 min = box.Min( boxPosition );

	auto		ret = eIntersectionType::INSIDE;
	glm::vec3	vmin, vmax;

	for( const auto &plane : frustum.Planes() )
	{
		const auto &normal		= plane.Normal();
		const auto &distance	= plane.Distance();

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
			return( eIntersectionType::OUTSIDE );
		}
		
		if( ( glm::dot( normal, vmax ) + distance ) >= 0 )
		{
			ret = eIntersectionType::INTERSECT;
		}
	}

	return( ret );
}

eIntersectionType Intersection( const CFrustum &frustum, const glm::vec3 &spherePosition, const CSphere &sphere )
{
	const auto &radius = sphere.Radius();

	auto ret = eIntersectionType::INSIDE;

	for( const auto &plane : frustum.Planes() )
	{
		const auto distance = Distance( plane, spherePosition );

		if( distance < -radius )
		{
			return( eIntersectionType::OUTSIDE );
		}
		
		if( std::abs( distance ) <= radius )
		{
			ret = eIntersectionType::INTERSECT;
		}
	}

	return( ret );
}