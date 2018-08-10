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
	
	~COcTree()
	{};

	void Clear();

	void Add( const CEntity &entity, const CTransform &transform, const CBoundingBox * const boundingBox );

private:
	CBoundingBox m_region;

	std::array<std::unique_ptr<COcTree>, 8> m_childNodes;

	std::vector<CEntity> m_entities;

	static const float sMinSize;
};
