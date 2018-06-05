#ifndef CENTITY_HPP
#define CENTITY_HPP

#include "CBoundingBox.hpp"


class CEntity final
{
public:
	CEntity()
	{};

	~CEntity()
	{};

	CBoundingBox BoundingBox;
};

#endif // COBJECT_HPP