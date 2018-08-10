#include "CTransform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "CWorld.hpp"

void CTransform::Rotate( const float pitchAngle, const float yawAngle, const float rollAngle )
{
	Orientation = glm::angleAxis( glm::radians( pitchAngle ), CWorld::X ) * Orientation;
	Orientation = glm::angleAxis( glm::radians( yawAngle ), CWorld::Y ) * Orientation;
	Orientation = glm::angleAxis( glm::radians( rollAngle ), CWorld::Z ) * Orientation;
}

const glm::mat4 CTransform::ViewMatrix( void ) const
{
	return( glm::translate( glm::toMat4( Orientation ), -Position ) );
}