#include "Distance.hpp"

f16 Distance( const CPlane &plane, const glm::vec3 &point )
{
	return( glm::dot( plane.Normal(), point ) + plane.Distance() );
}