#pragma once

#include <cstdint>

class Entity
{
public:
	Entity() :
		m_id { 0 }
	{}

	// TODO allow creation only from CScene
	Entity( const std::uint32_t id ) :
		m_id { id }
	{}

	const std::uint32_t &Id() const
	{
		return( m_id );
	}

private:
	std::uint32_t m_id;
};