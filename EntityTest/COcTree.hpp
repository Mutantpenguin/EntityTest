#pragma once

#include <array>
#include <memory>
#include <vector>

#include "CTransform.hpp"
#include "CBoundingBox.hpp"

#include "CEntity.hpp"

class COcTree
{
public:
	COcTree( const CBoundingBox &region );

	void Clear();

	bool Add( const CEntity &entity, const CTransform &transform, const CBoundingBox * const boundingBox );

private:
	CBoundingBox m_region;

	std::unique_ptr< std::array< COcTree, 8 > > m_childNodes;

	bool m_containsEntities = false;

	std::vector<CEntity> m_entities;

	static const float sMinSize;
};
