#pragma once

#include <functional>

#include "ecs/Id.hpp"
#include "CSphere.hpp"
#include "CBoundingBox.hpp"

#include "CFrustum.hpp"

class CBVHBase
{
public:
	virtual ~CBVHBase()
	{};

	virtual void Clear() = 0;

	virtual bool Add( const ecs::Id &entity, const glm::vec3 &position, const CBoundingBox * const boundingBox ) = 0;

	virtual void ForEachIn( const glm::vec3 &spherePosition, const CSphere &sphere, const std::function< void( const ecs::Id &entity ) > lambda ) const = 0;
	virtual void ForEachIn( const glm::vec3 &boxPosition, const CBoundingBox &box, const std::function< void( const ecs::Id &entity ) > lambda ) const = 0;
	virtual void ForEachIn( const CFrustum &frustum, const std::function< void( const ecs::Id &entity ) > lambda ) const = 0;

	virtual bool ExistsIn( const glm::vec3 &spherePosition, const CSphere &sphere, const std::function< bool( const ecs::Id &entity ) > lambda ) const = 0;
	virtual bool ExistsIn( const glm::vec3 &boxPosition, const CBoundingBox &box, const std::function< bool( const ecs::Id &entity ) > lambda ) const = 0;
	virtual bool ExistsIn( const CFrustum &frustum, const std::function< bool( const ecs::Id &entity ) > lambda ) const = 0;
};