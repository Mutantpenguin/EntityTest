#pragma once

#include <cstdint>
#include <limits>

#include "Types.hpp"

class CEntity final
{
	template < size_t _Size, typename... Types >
	friend class CEntityComponentSystem;

public:
	CEntity() noexcept
	{}

	const std::size_t &Id() const
	{
		return( m_id );
	}

	const u32 &Version() const
	{
		return( m_version );
	}

	static const size_t nullId = std::numeric_limits< size_t >::max();

private:
	CEntity( const size_t id ) :
		m_id { id }
	{}

	size_t m_id = nullId;
	u32 m_version = 0;
};