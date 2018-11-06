#pragma once

#include <array>

#include "CPlane.hpp"

class CFrustum
{
public:
	explicit CFrustum( const glm::mat4 &viewProjectionMatrix );

	bool IsSphereInside( const glm::vec3 &position, const float boundingSphereRadius ) const;

	const std::array< CPlane, 6 > &Planes() const;

private:
	std::array< CPlane, 6 > m_planes;
};
