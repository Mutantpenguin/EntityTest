#include "CSphere.hpp"
#include "CBoundingBox.hpp"

enum class eIntersectionType : std::uint8_t
{
	INSIDE,
	INTERSECT,
	OUTSIDE
};

eIntersectionType Intersection( const CBoundingBox &a, const CBoundingBox &b );

eIntersectionType Intersection( const CSphere &a, const CSphere &b );

eIntersectionType Intersection( const CSphere &sphere, const CBoundingBox &box );