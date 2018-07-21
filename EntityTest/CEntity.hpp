#ifndef CENTITY_HPP
#define CENTITY_HPP

#include "CBoundingBox.hpp"


class CEntity final
{
public:
	CEntity() noexcept
	{};

	~CEntity()
	{};

	CBoundingBox BoundingBox;
};

#endif // COBJECT_HPP