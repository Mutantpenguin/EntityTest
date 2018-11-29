#pragma once

#include <string>

template< typename T >
struct ComponentTraits
{
	static const std::string	Name;
};

#define REGISTER_COMPONENT( X ) \
	template <> const std::string ComponentTraits<X>::Name { #X };