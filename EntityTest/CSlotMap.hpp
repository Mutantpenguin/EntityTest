#pragma once

#include <unordered_map>
#include <stack>
#include <string>

template< typename T >
class CSlotMap
{
public:
	CSlotMap()
	{}
	
	CSlotMap( std::size_t capacity ) :
		m_initialCapacity { capacity }
	{
		Reserve( capacity );
	}

	~CSlotMap()
	{
		if( m_objects.capacity() > m_initialCapacity )
		{
			CLogger::Log( "initial capacity was '" + std::to_string( m_initialCapacity ) + "', current capacity is '" + std::to_string( m_objects.capacity() ) + "'" );
		}
	}

	void Reserve( std::size_t capacity )
	{
		m_objects.reserve( capacity );
	}

	void Add( std::uint32_t id, T& t )
	{
		std::size_t index;

		auto it = m_ids.find( id );

		if( std::cend( m_ids ) != it )
		{
			index = it->second;
		}
		else
		{
			if( !m_freeIndices.empty() )
			{
				index = m_freeIndices.top();

				m_freeIndices.pop();
			}
			else
			{
				m_lastObjectIndex++;

				if( m_objects.size() <= ( m_lastObjectIndex + 1 ) )
				{
					m_objects.resize( m_lastObjectIndex + 1 );
				}

				index = m_lastObjectIndex;
			}

			m_ids[ id ] = index;
		}

		m_objects[ index ] = std::make_pair( id, t );
	}

	void Remove( std::uint32_t id )
	{
		auto it = m_ids.find( id );

		if( std::cend( m_ids ) != it )
		{
			std::size_t index = it->second;

			m_ids.erase( it );

			if( m_lastObjectIndex > 0 )
			{
				m_objects[ index ] = m_objects[ m_lastObjectIndex ];

				m_ids[ m_objects[ index ].first ].second = index;
			}

			m_freeIndices.push( index );

			m_lastObjectIndex--;
		}
	}

private:
	std::unordered_map< std::uint32_t, std::size_t > m_ids;

	std::vector< std::pair< std::uint32_t, T > > m_objects;

	std::stack<std::size_t> m_freeIndices;

	std::size_t m_lastObjectIndex = -1;

	const std::size_t m_initialCapacity = 0;
};

