#pragma once

#include <cstdint>
#include <limits>

namespace ecs
{
	class Id final
	{
		template < std::uint32_t _Size, typename... Types >
		friend class ECS;

	public:
		Id() noexcept
		{}

		const std::uint32_t &Value() const
		{
			return( m_value );
		}

		const std::uint32_t &Generation() const
		{
			return( m_generation );
		}

		static const std::uint32_t nullValue		= std::numeric_limits< std::uint32_t >::max();
		static const std::uint32_t maxGeneration	= std::numeric_limits< std::uint32_t >::max();

	private:
		Id( const std::uint32_t value ) :
			m_value { value }
		{}

		std::uint32_t m_value		{ nullValue };
		std::uint32_t m_generation	{ 0 };
	};
}