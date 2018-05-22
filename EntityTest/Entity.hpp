#pragma once

#include <cstdint>
#include <cstddef>

class Entity
{
	template < size_t _Size, typename... Types >
	friend class CScene;

public:
	Entity() :
		m_id { 0 }
	{}

	const std::size_t &Id() const
	{
		return( m_id );
	}

	const std::uint32_t &Version() const
	{
		return( m_version );
	}

private:
	Entity( const std::uint32_t id ) :
		m_id { id }
	{}

	size_t m_id;
	std::uint32_t m_version;
};