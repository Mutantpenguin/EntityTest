#include "CBoundingBox.hpp"

#include <glm/gtx/norm.hpp>

CBoundingBox::CBoundingBox( const CBoundingBox &box ) :
	m_size { box.m_size }
{}

CBoundingBox::CBoundingBox( const glm::vec3 &size ) :
	m_size { size }
{}

const glm::vec3 &CBoundingBox::Size() const
{
	return( m_size );
}

glm::vec3 CBoundingBox::Dimensions() const
{
	return( m_size + m_size );
}

glm::vec3 CBoundingBox::Min( const glm::vec3 &position ) const
{
	return( position - m_size );
}

glm::vec3 CBoundingBox::Max( const glm::vec3 &position ) const
{
	return( position + m_size );
}