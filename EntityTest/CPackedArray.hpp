#pragma once

#include <array>
#include <functional>

#include "CComponent.hpp"

struct Index
{
	ID id;
	std::uint16_t index;
	std::uint16_t next;
};

template< typename T >
class CPackedArray
{
	static_assert( std::is_base_of< CComponent< T >, T >::value, "T must be a descendant of CComponent"  );

public:
	CPackedArray()
	{
		ID i = 0;

		for( auto &index : m_indices )
		{
			index.id = i;
			index.next = i + 1;
			i++;
		}
	}

	inline virtual bool has( ID id ) final
	{
		Index &in = m_indices[ id & INDEX_MASK ];

		return( ( in.id == id  ) && ( in.index != std::numeric_limits< ID >::max() ) );
	}

	inline virtual T &lookup( ID id ) final
	{
		return( m_components[ m_indices[ id & INDEX_MASK ].index ] );
	}

	inline virtual ID add() final
	{
		Index &in = m_indices[ m_freelist_dequeue ];
		m_freelist_dequeue = in.next;
		in.id += NEW_OBJECT_ID_ADD;
		in.index = m_componentsCount++;
		T &o = m_components[ in.index ];
		o.id = in.id;

		return( o.id );
	}

	inline virtual void remove( ID id ) final
	{
		Index &in = m_indices[ id & INDEX_MASK ];

		T &o = m_components[ in.index ];
		o = m_components[ --m_componentsCount ];
		m_indices[ o.id & INDEX_MASK ].index = in.index;

		in.index = std::numeric_limits< ID >::max();
		m_indices[ m_freelist_enqueue ].next = id & INDEX_MASK;
		m_freelist_enqueue = id & INDEX_MASK;
	}

	template<typename T>
	void ForEach( std::function<void( const T& )> lambda ) const
	{
		for( ID i = 0; i < m_componentsCount; i++ )
		{
			lambda( m_components[ i ] );
		}
	};

private:
	static const ID MAX_OBJECTS = 64 * 1024;
	static const auto INDEX_MASK = 0xffff;
	static const ID NEW_OBJECT_ID_ADD = 0x10000;

	ID m_componentsCount = 0;

	std::array< T, MAX_OBJECTS > m_components;
	std::array< Index, MAX_OBJECTS > m_indices;

	std::uint16_t m_freelist_enqueue = MAX_OBJECTS - 1;
	std::uint16_t m_freelist_dequeue = 0;

};