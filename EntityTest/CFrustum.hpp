#pragma once

#include <array>

#include "Types.hpp"

#include "CPlane.hpp"

class CFrustum
{
public:
	explicit CFrustum( const glm::mat4 &viewProjectionMatrix );

	const std::array< CPlane, 6 > &Planes() const;

private:
	std::array< CPlane, 6 > m_planes;
};
