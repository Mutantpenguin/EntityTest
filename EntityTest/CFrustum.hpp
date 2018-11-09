#pragma once

#include <array>

#include "Types.hpp"

#include "CPlane.hpp"

class CFrustum
{
public:
	explicit CFrustum( const glm::mat4 &viewProjectionMatrix );

	bool IsSphereInside( const glm::vec3 &position, const f16 boundingSphereRadius ) const;

	const std::array< CPlane, 6 > &Planes() const;

private:
	std::array< CPlane, 6 > m_planes;
};
