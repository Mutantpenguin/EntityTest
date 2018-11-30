#pragma once

#include <array>
#include <memory>
#include <vector>
#include <tuple>
#include <optional>

#include "Types.hpp"

#include "CBVHBase.hpp"

class COcTree final : public CBVHBase
{
public:
	COcTree( const glm::vec3 &position, const CBoundingBox &region );

	void Clear() override;

	bool Add( const ecs::CEntity &entity, const glm::vec3 &position, const CBoundingBox * const boundingBox ) override;

	virtual void ForEachIn( const glm::vec3 &spherePosition, const CSphere &sphere, const std::function< void( const ecs::CEntity &entity ) > lambda ) const override;
	virtual void ForEachIn( const glm::vec3 &boxPosition, const CBoundingBox &box, const std::function< void( const ecs::CEntity &entity ) > lambda ) const override;
	virtual void ForEachIn( const CFrustum &frustum, const std::function< void( const ecs::CEntity &entity ) > lambda ) const override;

	virtual bool ExistsIn( const glm::vec3 &spherePosition, const CSphere &sphere, const std::function< bool( const ecs::CEntity &entity ) > lambda ) const override;
	virtual bool ExistsIn( const glm::vec3 &boxPosition, const CBoundingBox &box, const std::function< bool( const ecs::CEntity &entity ) > lambda ) const override;
	virtual bool ExistsIn( const CFrustum &frustum, const std::function< bool( const ecs::CEntity &entity ) > lambda ) const override;

private:
	void ForEach( const std::function< void( const ecs::CEntity &entity ) > lambda ) const;
	bool Exists( const std::function< bool( const ecs::CEntity &entity ) > lambda ) const;
	
	const glm::vec3		m_position;
	const CBoundingBox	m_region;

	std::unique_ptr< std::array< COcTree, 8 > > m_octants;

	bool m_containsEntities = false;

	std::vector< std::tuple< ecs::CEntity, glm::vec3, std::optional< CBoundingBox > > > m_children;

	static const f16 sMinSize;
};
