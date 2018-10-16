#pragma once

#include <functional>

#include "CSphere.hpp"

#include "CSpatial.hpp"
#include "CBoundingBox.hpp"

#include "CEntity.hpp"

// TODO rename, conflicts with naming of CSpatial
class CSpatialBase
{
public:
	virtual ~CSpatialBase()
	{};

	virtual void Clear() = 0;

	virtual bool Add( const CEntity &entity, const glm::vec3 &position, const CBoundingBox * const boundingBox ) = 0;

	virtual void ForEachIn( const CSphere &sphere, const std::function< void( const CEntity &entity ) > lambda ) = 0;

	virtual bool ExistsIn( const CSphere &sphere, const std::function< bool( const CEntity &entity ) > lambda ) const = 0;
};

