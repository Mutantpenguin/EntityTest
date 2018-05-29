#pragma once

#include <cstdint>
#include <cstddef>
#include <limits>

class Entity
{
	template < size_t _Size, typename... Types >
	friend class CScene;

public:
	Entity()
	{}

	const std::size_t &Id() const
	{
		return( m_id );
	}

	const std::uint32_t &Version() const
	{
		return( m_version );
	}

	static const size_t nullId = std::numeric_limits< size_t >::max();

private:
	Entity( const size_t id ) :
		m_id { id }
	{}

	size_t m_id = nullId;
	std::uint32_t m_version;
};