#include "CFrustum.hpp"

CFrustum::CFrustum(const glm::mat4 &viewProjectionMatrix)
{
	// right
	CPlane &right = m_planes[0];
	right.SetNormal(glm::vec3(viewProjectionMatrix[0][3] - viewProjectionMatrix[0][0],
		viewProjectionMatrix[1][3] - viewProjectionMatrix[1][0],
		viewProjectionMatrix[2][3] - viewProjectionMatrix[2][0]));
	right.SetDistance(viewProjectionMatrix[3][3] - viewProjectionMatrix[3][0]);
	right.Normalize();

	// left
	CPlane &left = m_planes[1];
	left.SetNormal(glm::vec3(viewProjectionMatrix[0][3] + viewProjectionMatrix[0][0],
		viewProjectionMatrix[1][3] + viewProjectionMatrix[1][0],
		viewProjectionMatrix[2][3] + viewProjectionMatrix[2][0]));
	left.SetDistance(viewProjectionMatrix[3][3] + viewProjectionMatrix[3][0]);
	left.Normalize();

	// top
	CPlane &top = m_planes[2];
	top.SetNormal(glm::vec3(viewProjectionMatrix[0][3] - viewProjectionMatrix[0][1],
		viewProjectionMatrix[1][3] - viewProjectionMatrix[1][1],
		viewProjectionMatrix[2][3] - viewProjectionMatrix[2][1]));
	top.SetDistance(viewProjectionMatrix[3][3] - viewProjectionMatrix[3][1]);
	top.Normalize();

	// bottom
	CPlane &bottom = m_planes[3];
	bottom.SetNormal(glm::vec3(viewProjectionMatrix[0][3] + viewProjectionMatrix[0][1],
		viewProjectionMatrix[1][3] + viewProjectionMatrix[1][1],
		viewProjectionMatrix[2][3] + viewProjectionMatrix[2][1]));
	bottom.SetDistance(viewProjectionMatrix[3][3] + viewProjectionMatrix[3][1]);
	bottom.Normalize();

	// front
	CPlane &front = m_planes[4];
	front.SetNormal(glm::vec3(viewProjectionMatrix[0][3] + viewProjectionMatrix[0][2],
		viewProjectionMatrix[1][3] + viewProjectionMatrix[1][2],
		viewProjectionMatrix[2][3] + viewProjectionMatrix[2][2]));
	front.SetDistance(viewProjectionMatrix[3][3] + viewProjectionMatrix[3][2]);
	front.Normalize();

	// back
	CPlane &back = m_planes[5];
	back.SetNormal(glm::vec3(viewProjectionMatrix[0][3] - viewProjectionMatrix[0][2],
		viewProjectionMatrix[1][3] - viewProjectionMatrix[1][2],
		viewProjectionMatrix[2][3] - viewProjectionMatrix[2][2]));
	back.SetDistance(viewProjectionMatrix[3][3] - viewProjectionMatrix[3][2]);
	back.Normalize();
}

bool CFrustum::IsSphereInside(const glm::vec3 &position, const float boundingSphereRadius) const
{
	// TODO multithreaded?
	for (const CPlane &plane : m_planes)
	{
		if (plane.DistanceToPlane(position) < -boundingSphereRadius)
		{
			return(false);
		}
	}

	return(true);
}