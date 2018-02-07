#pragma once

#include <tuple>
#include <unordered_map>

#include "CEntity.hpp"

template <typename... Types>
class CDodTest
{
private:
	static const std::uint32_t MAX_ENTITIES { 10000 };

public:
	CDodTest()
	{}

	~CDodTest()
	{}

	template<typename T>
	using Container = std::unordered_map< std::uint32_t, T >;

	template<typename T>
	Container<T> &GetComponentsArray()
	{
		return( std::get<Container<T>>( m_components ) );
	}

private:
	Container<CEntity> m_entities;

	std::tuple<Container<Types>...> m_components;
};

