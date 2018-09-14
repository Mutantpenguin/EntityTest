#pragma once

#include "CTransform.hpp"
#include "CBoundingBox.hpp"

#include "CEntity.hpp"

class CSpatialBase
{
public:
	CSpatialBase()
	{};
	
	virtual ~CSpatialBase()
	{};

	virtual void Clear() = 0;

	virtual bool Add( const CEntity &entity, const CTransform &transform, const CBoundingBox * const boundingBox ) = 0;
};

