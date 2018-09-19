#pragma once

#include <array>
#include <memory>
#include <vector>
#include <tuple>

#include "CSpatialBase.hpp"

class COcTree final : public CSpatialBase
{
public:
	COcTree( const CBoundingBox &region );

	void Clear() override;

	bool Add( const CEntity &entity, const CTransform &transform, const CBoundingBox * const boundingBox ) override;

	virtual void ForEachIn( const CSphere &sphere, const std::function< void( const CEntity &entity ) > lambda ) override;

	virtual bool ExistsIn( const CSphere &sphere, const std::function< bool( const CEntity &entity ) > lambda ) const override;

private:
	void ForEach( const std::function< void( const CEntity &entity ) > lambda );
	bool Exists( const std::function< bool( const CEntity &entity ) > lambda ) const;
	
	const CBoundingBox m_region;

	std::unique_ptr< std::array< COcTree, 8 > > m_octants;

	bool m_containsEntities = false;

	std::vector< std::tuple< CEntity, CTransform, std::unique_ptr< CBoundingBox > > > m_children;

	static const float sMinSize;
};
