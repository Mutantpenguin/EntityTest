#pragma once

#include <array>
#include <memory>
#include <set>

#include "CBoundingBox.hpp"

#include "CEntity.hpp"

class COcTree
{
public:
	COcTree( const CBoundingBox &region );
	~COcTree();

	void AddEntity(const std::shared_ptr<CEntity> &entity);

private:
	CBoundingBox m_region;

	std::array<std::unique_ptr<COcTree>, 8> m_childNodes;

	std::set<std::shared_ptr<const CEntity>> m_entities;

	static const float sMinSize;
};
