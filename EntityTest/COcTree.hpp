#pragma once

#include <array>
#include <memory>
#include <vector>
#include <tuple>
#include <optional>

#include "CSpatialBase.hpp"

class COcTree final : public CSpatialBase
{
public:
	COcTree( const glm::vec3 &position, const CBoundingBox &region );

	void Clear() override;

	bool Add( const CEntity &entity, const glm::vec3 &position, const CBoundingBox * const boundingBox ) override;

	virtual void ForEachIn( const CSphere &sphere, const std::function< void( const CEntity &entity ) > lambda ) override;

	virtual bool ExistsIn( const CSphere &sphere, const std::function< bool( const CEntity &entity ) > lambda ) const override;

private:
	void ForEach( const std::function< void( const CEntity &entity ) > lambda );
	bool Exists( const std::function< bool( const CEntity &entity ) > lambda ) const;
	
	const glm::vec3		m_position;
	const CBoundingBox	m_region;

	std::unique_ptr< std::array< COcTree, 8 > > m_octants;

	bool m_containsEntities = false;

	std::vector< std::tuple< CEntity, glm::vec3, std::optional< CBoundingBox > > > m_children;

	static const float sMinSize;
};
