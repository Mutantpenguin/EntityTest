#pragma once

#include <glm/glm.hpp>

#include "Types.hpp"

class CSphere final
{
public:
	CSphere( const f16 radius );

	const f16 &Radius() const;
	const f16 &Radius2() const;

private:
	const f16	m_radius { 0.0f };
	const f16	m_radius2 { 0.0f };
};
