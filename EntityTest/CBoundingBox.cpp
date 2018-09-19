#include "CBoundingBox.hpp"

CBoundingBox::CBoundingBox( const CBoundingBox &box ) :
	m_min { box.m_min },
	m_max { box.m_max }
{}

CBoundingBox::CBoundingBox( const glm::vec3 &min, const glm::vec3 &max ) :
	m_min { min },
	m_max { max }
{}

glm::vec3 CBoundingBox::Center() const
{
	return( ( m_min + m_max ) / 2.0f );
}

glm::vec3 CBoundingBox::Dimensions() const
{
	return( m_max - m_min );
}

void CBoundingBox::MoveTo( const glm::vec3 &position )
{
	auto const movement = position - Center();

	m_min += movement;
	m_max += movement;
}

const glm::vec3 &CBoundingBox::Min() const
{
	return( m_min );
}

const glm::vec3 &CBoundingBox::Max() const
{
	return( m_max );
}