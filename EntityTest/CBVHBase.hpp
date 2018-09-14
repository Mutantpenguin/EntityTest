#pragma once

#include "CTransform.hpp"
#include "CBoundingBox.hpp"

#include "CEntity.hpp"

class CBVHBase
{
public:
	CBVHBase( const CBoundingBox &region );
	
	virtual ~CBVHBase()
	{};

	virtual void Clear() = 0;

	virtual bool Add( const CEntity &entity, const CTransform &transform, const CBoundingBox * const boundingBox ) = 0;

protected:
	CBoundingBox m_region;
};

