#include "CCameraFreeComponent.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "CWorld.hpp"

CCameraFreeComponent::CCameraFreeComponent(const std::shared_ptr< CEntity > &parent, float aspectRatio, float fov, float zNear, float zFar) :
	CCameraComponent(parent,zNear, zFar),
	m_aspectRatio{ aspectRatio },
	m_fov{ fov }
{
}

CCameraFreeComponent::~CCameraFreeComponent()
{
}

void CCameraFreeComponent::FOV(float fov)
{
	if (fov > 155)
	{
		m_fov = 155;
	}
	else if (fov < 25)
	{
		m_fov = 25;
	}
	else
	{
		m_fov = fov;
	}
}

float CCameraFreeComponent::FOV(void) const
{
	return(m_fov);
}

void CCameraFreeComponent::MoveForward(const float distance)
{
	m_parent->Transform.Position(m_parent->Transform.Position() - (Direction() * distance));
}

void CCameraFreeComponent::MoveBackward(const float distance)
{
	m_parent->Transform.Position(m_parent->Transform.Position() + (Direction() * distance));
}

void CCameraFreeComponent::MoveUp(const float distance)
{
	m_parent->Transform.Position(m_parent->Transform.Position() + (CWorld::Y * distance));
}

void CCameraFreeComponent::MoveDown(const float distance)
{
	m_parent->Transform.Position(m_parent->Transform.Position() - (CWorld::Y * distance));
}

void CCameraFreeComponent::MoveLeft(const float distance)
{
	m_parent->Transform.Position(m_parent->Transform.Position() - (glm::cross(Up(), Direction()) * distance));
}

void CCameraFreeComponent::MoveRight(const float distance)
{
	m_parent->Transform.Position(m_parent->Transform.Position() + (glm::cross(Up(), Direction()) * distance));
}

void CCameraFreeComponent::Rotate(const float pitchAngle, const float yawAngle)
{
	m_parent->Transform.Orientation(glm::angleAxis(glm::radians(pitchAngle), CWorld::X) * m_parent->Transform.Orientation() * glm::angleAxis(glm::radians(yawAngle), CWorld::Y));
}

const glm::mat4 CCameraFreeComponent::ProjectionMatrix(void) const
{
	return(glm::perspective(glm::radians(m_fov), m_aspectRatio, m_zNear, m_zFar));
}