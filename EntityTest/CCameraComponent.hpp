#ifndef CCAMERACOMPONENT_HPP
#define CCAMERACOMPONENT_HPP

#include <glm/gtc/quaternion.hpp>

#include "EComponentIndex.hpp"
#include "CBaseComponent.hpp"

#include "CFrustum.hpp"

#include "CSize.hpp"

class CCameraComponent : public CBaseComponent
{
public:
	CCameraComponent( const std::shared_ptr< CEntity > &parent, float zNear, float zFar );
	virtual ~CCameraComponent();

	static const std::uint16_t Index = static_cast<std::uint16_t>( EComponentIndex::CAMERA );

	void	ZNear( float zNear );
	float	ZNear( void ) const;

	void	ZFar( float zFar );
	float	ZFar( void ) const;

	glm::vec3 const Up( void ) const;

	void Direction( const glm::vec3 &direction );
	const glm::vec3 Direction( void ) const;

	const CFrustum Frustum( void ) const;

	virtual const glm::mat4 ProjectionMatrix( void ) const = 0;
	const glm::mat4 ViewProjectionMatrix( void ) const;

protected:
	float	m_zNear;
	float	m_zFar;
};

#endif // CCAMERACOMPONENT_HPP