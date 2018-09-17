#pragma once

#include <functional>

#include "CSphere.hpp"

#include "CTransform.hpp"
#include "CBoundingBox.hpp"

#include "CEntity.hpp"

class CSpatialBase
{
public:
	virtual ~CSpatialBase()
	{};

	virtual void Clear() = 0;

	virtual bool Add( const CEntity &entity, const CTransform &transform, const CBoundingBox * const boundingBox ) = 0;

	virtual void ForEach( const std::function< void( const CEntity &entity ) > lambda ) = 0;

	virtual void ForEachIn( const CSphere &sphere, const std::function< void( const CEntity &entity ) > lambda ) = 0;

	virtual bool ExistsIn( const CSphere &sphere, const std::function< bool( const CEntity &entity ) > lambda ) const = 0;
};

