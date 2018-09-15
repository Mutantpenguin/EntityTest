#pragma once

#include <glm/glm.hpp>

class CBoundingBox final
{
public:
	CBoundingBox()
	{}
	
	CBoundingBox( const glm::vec3 &min, const glm::vec3 &max );

	glm::vec3 Center() const;
	glm::vec3 Dimensions() const;

	void MoveTo( const glm::vec3 &position );

	const glm::vec3 &Min() const;
	const glm::vec3 &Max() const;

private:
	glm::vec3 m_min;
	glm::vec3 m_max;
};
