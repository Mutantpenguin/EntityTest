#ifndef CFRUSTUM_HPP
#define CFRUSTUM_HPP

#include <array>

#include "CPlane.hpp"

class CFrustum
{
public:
	explicit CFrustum(const glm::mat4 &viewProjectionMatrix);

	bool IsSphereInside(const glm::vec3 &position, const float boundingSphereRadius) const;

private:
	std::array< CPlane, 6 > m_planes;
};

#endif // CFRUSTUM_HPP