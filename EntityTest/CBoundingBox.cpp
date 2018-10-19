#include "CBoundingBox.hpp"

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

glm::vec3 CBoundingBox::Min( const glm::vec3 &boxPosition ) const
{
	return( boxPosition - m_size );
}

glm::vec3 CBoundingBox::Max( const glm::vec3 &boxPosition ) const
{
	return( boxPosition + m_size );
}