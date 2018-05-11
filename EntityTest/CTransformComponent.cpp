#include "CTransformComponent.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "CWorld.hpp"

void CTransformComponent::Position( const glm::vec3 &position )
{
	m_position = position;
}

const glm::vec3 &CTransformComponent::Position( void ) const
{
	return( m_position );
}

void CTransformComponent::Orientation( const glm::quat &orientation )
{
	m_orientation = orientation;
}

void CTransformComponent::Scale( const glm::vec3 &scale )
{
	m_scale = scale;
}

const glm::vec3 &CTransformComponent::Scale( void ) const
{
	return( m_scale );
}

const glm::quat &CTransformComponent::Orientation( void ) const
{
	return( m_orientation );
}

void CTransformComponent::Rotate( const float pitchAngle, const float yawAngle, const float rollAngle )
{
	m_orientation = glm::angleAxis( glm::radians( pitchAngle ), CWorld::X ) * m_orientation;
	m_orientation = glm::angleAxis( glm::radians( yawAngle ), CWorld::Y ) * m_orientation;
	m_orientation = glm::angleAxis( glm::radians( rollAngle ), CWorld::Z ) * m_orientation;
}

const glm::mat4 CTransformComponent::ViewMatrix( void ) const
{
	return( glm::translate( glm::toMat4( m_orientation ), -m_position ) );
}