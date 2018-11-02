#include "CTransformComponent.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "World.hpp"

void CTransformComponent::Rotate( const float pitchAngle, const float yawAngle, const float rollAngle )
{
	Orientation = glm::angleAxis( glm::radians( pitchAngle ), World::X ) * Orientation;
	Orientation = glm::angleAxis( glm::radians( yawAngle ), World::Y ) * Orientation;
	Orientation = glm::angleAxis( glm::radians( rollAngle ), World::Z ) * Orientation;
}

const glm::mat4 CTransformComponent::ViewMatrix( void ) const
{
	return( glm::translate( glm::toMat4( Orientation ), -Position ) );
}