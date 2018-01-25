#include "CBoundingBox.hpp"

CBoundingBox::CBoundingBox()
{}

CBoundingBox::CBoundingBox( const glm::vec3 &min, const glm::vec3 &max ) :
	m_min { min },
	m_max { max }
{}

CBoundingBox::eIntersectionType CBoundingBox::Intersect( const CBoundingBox & boundingBox ) const
{
	if( ( m_min.x <= boundingBox.Min().x )
		&&
		( m_max.x >= boundingBox.Max().x )
		&&
		( m_min.y <= boundingBox.Min().y )
		&&
		( m_max.y >= boundingBox.Max().y )
		&&
		( m_min.z <= boundingBox.Min().z )
		&&
		( m_max.z >= boundingBox.Max().z ) )
	{
		return( eIntersectionType::INSIDE );
	}

	if( ( m_max.x < boundingBox.Min().x )
		||
		( m_min.x > boundingBox.Max().x )
		||
		( m_max.y < boundingBox.Min().y )
		||
		( m_min.y > boundingBox.Max().y )
		||
		( m_max.z < boundingBox.Min().z )
		||
		( m_min.z > boundingBox.Max().z ) )
	{
		return( eIntersectionType::OUTSIDE );
	}

	return( eIntersectionType::INTERSECT );
}

const glm::vec3 &CBoundingBox::Min() const
{
	return( m_min );
}

const glm::vec3 &CBoundingBox::Max() const
{
	return( m_max );
}