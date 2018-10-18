#include "CSphere.hpp"
#include "CBoundingBox.hpp"

enum class eIntersectionType : std::uint8_t
{
	INSIDE,
	INTERSECT,
	OUTSIDE
};

eIntersectionType Intersection( const glm::vec3 &boxAPosition, const CBoundingBox &boxA, const glm::vec3 &boxBPosition, const CBoundingBox &boxB );

eIntersectionType Intersection( const glm::vec3 &boxPosition, const CBoundingBox &box, const CSphere &sphere );

eIntersectionType Intersection( const CSphere &a, const CSphere &b );

eIntersectionType Intersection( const CSphere &sphere, const glm::vec3 &boxPosition, const CBoundingBox &box );