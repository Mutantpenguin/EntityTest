#pragma once

#include <glm/glm.hpp>

class CBoundingBox final
{
public:
	CBoundingBox( const glm::vec3 &min, const glm::vec3 &max );

	CBoundingBox()
	{}

	enum class eIntersectionType
	{
		INSIDE,
		INTERSECT,
		OUTSIDE
	};

	glm::vec3 Center() const;
	glm::vec3 Dimensions() const;

	void MoveTo( const glm::vec3 &position );

	eIntersectionType Intersect( const CBoundingBox &boundingBox ) const;
	bool Contains( const glm::vec3 &position ) const;

	const glm::vec3 &Min() const;
	const glm::vec3 &Max() const;

private:
	glm::vec3 m_min;
	glm::vec3 m_max;
};
