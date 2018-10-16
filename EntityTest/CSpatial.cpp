#include "CSpatial.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "CWorld.hpp"

void CSpatial::Rotate( const float pitchAngle, const float yawAngle, const float rollAngle )
{
	Orientation = glm::angleAxis( glm::radians( pitchAngle ), CWorld::X ) * Orientation;
	Orientation = glm::angleAxis( glm::radians( yawAngle ), CWorld::Y ) * Orientation;
	Orientation = glm::angleAxis( glm::radians( rollAngle ), CWorld::Z ) * Orientation;
}

CBoundingBox CSpatial::BoundingBox() const
{
	return( CBoundingBox( Position - Blah.value(), Position + Blah.value() ) );
}

const glm::mat4 CSpatial::ViewMatrix( void ) const
{
	return( glm::translate( glm::toMat4( Orientation ), -Position ) );
}