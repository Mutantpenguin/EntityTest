#pragma once

#include <glm\glm.hpp>

class CBoundingBox final
{
public:
	CBoundingBox();
	CBoundingBox( const glm::vec3 &min, const glm::vec3 &max );

	enum class eIntersectionType
	{
		INSIDE,
		INTERSECT,
		OUTSIDE
	};

	eIntersectionType Intersect( const CBoundingBox &boundingBox ) const;

	const glm::vec3 &Min() const;
	const glm::vec3 &Max() const;

private:
	glm::vec3 m_min;
	glm::vec3 m_max;

};
