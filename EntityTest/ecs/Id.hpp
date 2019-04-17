#pragma once

#include <cstdint>
#include <limits>

namespace ecs
{
	class Id final
	{
		template < std::uint32_t _Size, typename... Types >
		friend class ECS;

		template< std::uint32_t _Size, typename T >
		friend class SlotMap;

	public:
		Id() noexcept
		{}

		const std::uint32_t &Index() const
		{
			return( m_index );
		}

		const std::uint8_t &Generation() const
		{
			return( m_generation );
		}

		static const std::uint32_t	nullIndex		= std::numeric_limits< std::uint32_t >::max();
		static const std::uint8_t	maxGeneration	= std::numeric_limits< std::uint8_t >::max();

	private:
		Id( const std::uint32_t &index, const std::uint8_t &generation ) :
			m_index { index },
			m_generation { generation }
		{}

		// TODO use bitfield
		std::uint32_t	m_index			{ nullIndex };
		std::uint8_t	m_generation	{ 0 };
	};
}