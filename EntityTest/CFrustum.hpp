#pragma once

#include <array>

#include "Types.hpp"

#include "CPlane.hpp"

class CFrustum
{
public:
	CFrustum() = delete;
	
	explicit CFrustum( const glm::mat4 &viewProjectionMatrix );

	const std::array< CPlane, 6 > &Planes() const;

private:
	const std::array< CPlane, 6 > m_planes;
};
