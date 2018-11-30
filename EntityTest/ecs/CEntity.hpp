#pragma once

#include <cstdint>
#include <limits>

namespace ecs
{
	class CEntity final
	{
		template < std::uint32_t _Size, typename... Types >
		friend class CEntityComponentSystem;

	public:
		CEntity() noexcept
		{}

		const std::uint32_t &Id() const
		{
			return( m_id );
		}

		const std::uint32_t &Version() const
		{
			return( m_version );
		}

		static const std::uint32_t nullId = std::numeric_limits< std::uint32_t >::max();

	private:
		CEntity( const std::uint32_t id ) :
			m_id { id }
		{}

		std::uint32_t m_id		= nullId;
		std::uint32_t m_version	= 0;
	};
}