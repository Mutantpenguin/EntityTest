#pragma once

#include <array>
#include <memory>
#include <vector>

#include "CSpatialBase.hpp"

class COcTree final : public CSpatialBase
{
public:
	COcTree( const CBoundingBox &region );

	void Clear() override;

	bool Add( const CEntity &entity, const CTransform &transform, const CBoundingBox * const boundingBox ) override;

	virtual void ForEach( const std::function< void( const CEntity &entity ) > lambda ) override;
	
	virtual void ForEachIn( const CSphere &sphere, const std::function< void( const CEntity &entity ) > lambda ) override;

	virtual bool ExistsIn( const CSphere &sphere, const std::function< bool( const CEntity &entity ) > lambda ) const override;

private:
	const CBoundingBox m_region;

	std::unique_ptr< std::array< COcTree, 8 > > m_octants;

	bool m_containsEntities = false;

	std::vector< CEntity > m_entities;

	static const float sMinSize;
};
