#include "Intersection.hpp"

#include <glm/gtx/norm.hpp>

#include "Contains.hpp"
#include "ClosestPoint.hpp"

#include "minitrace.h"

eIntersectionType Intersection( const CBoundingBox &a, const CBoundingBox &b )
{
	MTR_SCOPE( "Intersection", "Intersection box <-> box" );


	if( ( a.Max().x < b.Min().x )
		||
		( a.Min().x > b.Max().x )
		||
		( a.Max().y < b.Min().y )
		||
		( a.Min().y > b.Max().y )
		||
		( a.Max().z < b.Min().z )
		||
		( a.Min().z > b.Max().z ) )
	{
		return( eIntersectionType::OUTSIDE );
	}

	if( ( a.Min().x <= b.Min().x )
		&&
		( a.Max().x >= b.Max().x )
		&&
		( a.Min().y <= b.Min().y )
		&&
		( a.Max().y >= b.Max().y )
		&&
		( a.Min().z <= b.Min().z )
		&&
		( a.Max().z >= b.Max().z ) )
	{
		return( eIntersectionType::INSIDE );
	}

	return( eIntersectionType::INTERSECT );
}

eIntersectionType Intersection( const CBoundingBox &box, const CSphere &sphere )
{
	MTR_SCOPE( "Intersection", "Intersection box <-> sphere" );

	if( std::pow( sphere.Radius(), 2 ) >= glm::length2( sphere.Position() - ClosestPoint( box, sphere.Position() ) ) )
	{
		if( Contains( sphere, box.Min() )
			&&
			Contains( sphere, box.Max() ) )
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

eIntersectionType Intersection( const CSphere &sphere, const CBoundingBox &box )
{
	MTR_SCOPE( "Intersection", "Intersection sphere <-> box" );

	const auto radiusSquared = std::pow( sphere.Radius(), 2 );
	
	if( radiusSquared >= glm::length2( sphere.Position() - ClosestPoint( box, sphere.Position() ) ) )
	{
		if( ( radiusSquared >= glm::length2( sphere.Position() - box.Min() ) )
			&&
			( radiusSquared >= glm::length2( sphere.Position() - box.Max() ) ) )
		{
			return( eIntersectionType::INSIDE );
		}
		
		return( eIntersectionType::INTERSECT );
	}
	
	return( eIntersectionType::OUTSIDE );
}