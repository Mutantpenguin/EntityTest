#include "CSphere.hpp"
#include "CBoundingBox.hpp"

#include "Types.hpp"

enum class eIntersectionType : u8
{
	INSIDE,
	INTERSECT,
	OUTSIDE
};

eIntersectionType Intersection( const glm::vec3 &boxAPosition, const CBoundingBox &boxA, const glm::vec3 &boxBPosition, const CBoundingBox &boxB );

eIntersectionType Intersection( const glm::vec3 &boxPosition, const CBoundingBox &box, const glm::vec3 &spherePosition, const CSphere &sphere );

eIntersectionType Intersection( const glm::vec3 &sphereAPosition, const CSphere &sphereA, const glm::vec3 &sphereBPosition, const CSphere &sphereB );

eIntersectionType Intersection( const glm::vec3 &spherePosition, const CSphere &sphere, const glm::vec3 &boxPosition, const CBoundingBox &box );