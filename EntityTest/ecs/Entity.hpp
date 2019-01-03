#pragma once

#include <cstdint>
#include <limits>

namespace ecs
{
	class Entity final
	{
		template < std::uint32_t _Size, typename... Types >
		friend class ECS;

	public:
		Entity() noexcept
		{}

		const std::uint32_t &Id() const
		{
			return( m_id );
		}

		const std::uint32_t &Generation() const
		{
			return( m_generation );
		}

		static const std::uint32_t nullId = std::numeric_limits< std::uint32_t >::max();

	private:
		Entity( const std::uint32_t id ) :
			m_id { id }
		{}

		std::uint32_t m_id			= nullId;
		std::uint32_t m_generation	= 0;
	};
}