#include "CSphere.hpp"
#include "CBoundingBox.hpp"

enum class eIntersectionType : std::uint8_t
{
	INSIDE,
	INTERSECT,
	OUTSIDE
};

eIntersectionType Intersection( const glm::vec3 &positionA, const CBoundingBox &boxA, const glm::vec3 &positionB, const CBoundingBox &boxB );

eIntersectionType Intersection( const glm::vec3 &positionBox, const CBoundingBox &box, const CSphere &sphere );

eIntersectionType Intersection( const CSphere &a, const CSphere &b );

eIntersectionType Intersection( const CSphere &sphere, const glm::vec3 &positionBox, const CBoundingBox &box );