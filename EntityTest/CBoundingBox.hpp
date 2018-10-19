#pragma once

#include <glm/glm.hpp>

class CBoundingBox final
{
public:
	CBoundingBox()
	{}

	CBoundingBox( const glm::vec3 &size );

	const glm::vec3 &Size() const;

	glm::vec3 Dimensions() const;

	glm::vec3 Min( const glm::vec3 &boxPosition ) const;
	glm::vec3 Max( const glm::vec3 &boxPosition ) const;

private:
	glm::vec3 m_size;
};
