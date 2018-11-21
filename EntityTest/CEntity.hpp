#pragma once

#include <cstdint>
#include <limits>

#include "Types.hpp"

class CEntity final
{
	template < u32 _Size, typename... Types >
	friend class CEntityComponentSystem;

public:
	CEntity() noexcept
	{}

	const u32 &Id() const
	{
		return( m_id );
	}

	const u32 &Version() const
	{
		return( m_version );
	}

	static const u32 nullId = std::numeric_limits< u32 >::max();

private:
	CEntity( const u32 id ) :
		m_id { id }
	{}

	u32 m_id = nullId;
	u32 m_version = 0;
};