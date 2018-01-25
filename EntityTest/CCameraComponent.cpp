#include "CCameraComponent.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "CLogger.hpp"

#include "CWorld.hpp"

CCameraComponent::CCameraComponent( const std::shared_ptr< CEntity > &parent, float zNear, float zFar ) :
	CBaseComponent( parent ),
	m_zNear { zNear },
	m_zFar { zFar }
{}

CCameraComponent::~CCameraComponent()
{}

void CCameraComponent::ZNear( float zNear )
{
	m_zNear = zNear;
}

float CCameraComponent::ZNear( void ) const
{
	return( m_zNear );
}

void CCameraComponent::ZFar( float zFar )
{
	m_zFar = zFar;
}

float CCameraComponent::ZFar( void ) const
{
	return( m_zFar );
}

glm::vec3 const CCameraComponent::Up( void ) const
{
	return( CWorld::Y * m_parent->Transform.Orientation() );
}

void CCameraComponent::Direction( const glm::vec3 &direction )
{
	const glm::mat4 RotationMatrix = glm::lookAt( m_parent->Transform.Position(), m_parent->Transform.Position() + direction, CWorld::Y );

	m_parent->Transform.Orientation( glm::toQuat( RotationMatrix ) );
}

const glm::vec3 CCameraComponent::Direction( void ) const
{
	return( CWorld::Z * m_parent->Transform.Orientation() );
}

const CFrustum CCameraComponent::Frustum( void ) const
{
	return( CFrustum( ViewProjectionMatrix() ) );
}

const glm::mat4 CCameraComponent::ViewProjectionMatrix( void ) const
{
	return( ProjectionMatrix() * m_parent->Transform.ViewMatrix() );
}