#include "Intersection.hpp"

#include <glm/gtx/norm.hpp>

#include "Contains.hpp"
#include "ClosestPoint.hpp"

#include "minitrace.h"

eIntersectionType Intersection( const glm::vec3 &boxAPosition, const CBoundingBox &boxA, const glm::vec3 &boxBPosition, const CBoundingBox &boxB )
{
	MTR_SCOPE( "Intersection", "Intersection box <-> box" );

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

eIntersectionType Intersection( const glm::vec3 &boxPosition, const CBoundingBox &box, const CSphere &sphere )
{
	MTR_SCOPE( "Intersection", "Intersection box <-> sphere" );

	if( std::pow( sphere.Radius(), 2 ) >= glm::length2( sphere.Position() - ClosestPoint( boxPosition, box, sphere.Position() ) ) )
	{
		if( Contains( sphere, box.Min( boxPosition ) )
			&&
			Contains( sphere, box.Max( boxPosition ) ) )
		{
			return( eIntersectionType::INSIDE );
		}

		return( eIntersectionType::INTERSECT );
	}

	return( eIntersectionType::OUTSIDE );
}

eIntersectionType Intersection( const CSphere &a, const CSphere &b )
{
	MTR_SCOPE( "Intersection", "Intersection sphere <-> sphere" );

    const glm::vec3 distance = a.Position() - b.Position();
	
	if( a.Radius() >= ( glm::length( distance ) + b.Radius() ) )
	{
		return( eIntersectionType::INSIDE );
	}
	else
	{
		const float squaredDistance = glm::dot( distance, distance ); // same as squared length of distance
		
		// Spheres intersect if squared distance is less than squared sum of radii
		if( squaredDistance <= std::pow( a.Radius() + b.Radius(), 2 ) )
		{
			return( eIntersectionType::INTERSECT );
		}
	}
	
	return( eIntersectionType::OUTSIDE );
}

eIntersectionType Intersection( const CSphere &sphere, const glm::vec3 &boxPosition, const CBoundingBox &box )
{
	MTR_SCOPE( "Intersection", "Intersection sphere <-> box" );

	const auto radiusSquared = std::pow( sphere.Radius(), 2 );
	
	if( radiusSquared >= glm::length2( sphere.Position() - ClosestPoint( boxPosition, box, sphere.Position() ) ) )
	{
		if( ( radiusSquared >= glm::length2( sphere.Position() - box.Min( boxPosition ) ) )
			&&
			( radiusSquared >= glm::length2( sphere.Position() - box.Max( boxPosition ) ) ) )
		{
			return( eIntersectionType::INSIDE );
		}
		
		return( eIntersectionType::INTERSECT );
	}
	
	return( eIntersectionType::OUTSIDE );
}