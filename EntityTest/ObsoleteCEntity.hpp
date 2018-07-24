#ifndef CENTITY_HPP
#define CENTITY_HPP

#include "CBoundingBox.hpp"


class ObsoleteCEntity final
{
public:
	ObsoleteCEntity() noexcept
	{};

	~ObsoleteCEntity()
	{};

	CBoundingBox BoundingBox;
};

#endif // COBJECT_HPP