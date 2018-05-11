#pragma once

#include <cstdint>

class Entity
{
	friend class CScene;
	friend class CSlotMap;

private:
	Entity( const std::uint32_t id ) :
		m_id { id }
	{}

	const std::uint32_t &Id() const
	{
		return( m_id );
	}

	std::uint32_t m_id;
};