#pragma once

#include <string>

namespace ecs
{
	template< typename T >
	struct ComponentTraits
	{
		static const std::string	Name;
	};

#define REGISTER_COMPONENT( X ) \
		template <> const std::string ecs::ComponentTraits<X>::Name { #X };
}