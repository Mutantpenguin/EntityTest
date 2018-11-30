#include "Transform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Types.hpp"

#include "World.hpp"

namespace cmpt
{
	void Transform::Rotate( const f16 pitchAngle, const f16 yawAngle, const f16 rollAngle )
	{
		Orientation = glm::angleAxis( glm::radians( pitchAngle ), World::X ) * Orientation;
		Orientation = glm::angleAxis( glm::radians( yawAngle ), World::Y ) * Orientation;
		Orientation = glm::angleAxis( glm::radians( rollAngle ), World::Z ) * Orientation;
	}

	const glm::mat4 Transform::ViewMatrix( void ) const
	{
		return( glm::translate( glm::toMat4( Orientation ), -Position ) );
	}
}