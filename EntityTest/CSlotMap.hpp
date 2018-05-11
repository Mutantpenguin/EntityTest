#pragma once

#include <stack>
#include <string>
#include <functional>
#include <vector>

#include "Entity.hpp"

template< typename T >
class CSlotMap
{
public:
	CSlotMap()
	{}
	
	CSlotMap( std::size_t capacity ) :
		m_initialCapacity { capacity }
	{
		m_ids.reserve( m_initialCapacity * 4 ); // TODO is 4 times really enough?!?
		m_objects.reserve( m_initialCapacity );
	}

	~CSlotMap()
	{
		CLogger::Log( "size: " + std::to_string( m_objects.size() ) );
		CLogger::Log( "size in KiBi: " + std::to_string( SizeInBytes() / 1024 ) );

		if( m_objects.capacity() > m_initialCapacity )
		{
			CLogger::Log( "initial capacity was '" + std::to_string( m_initialCapacity ) + "', current capacity is '" + std::to_string( m_objects.capacity() ) + "'" );
		}
	}

	std::size_t SizeInBytes()
	{
		return( sizeof( T ) * m_objects.size() );
	}

	bool Has( const Entity &entity ) const
	{
		if( m_objects.size() > entity.Id() )
		{
			if( nullIndex == m_ids[ entity.Id() ] )
			{
				return( false );
			}
			else
			{
				return( true );
			}
		}
		else
		{
			return( true );
		}
	}

	void Add( const Entity &entity, T& t )
	{
		if( ( entity.Id() + 1 ) > m_ids.size() )
		{
			m_ids.resize( ( entity.Id() + 1 ), nullIndex );
		}

		if( nullIndex != m_ids[ entity.Id() ] )
		{
			CLogger::Log( "component already exists" );
			return;
		}
		else
		{
			std::size_t index;

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

			m_ids[ entity.Id() ] = index;

			m_objects[ index ] = std::make_pair( entity, t );
		}
	}

	void Remove( const Entity &entity )
	{
		auto it = m_ids.find( entity );

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

	T* Get( const Entity &entity )
	{
		if( m_objects.size() > entity.Id() )
		{
			if( nullIndex == m_ids[ entity.Id() ] )
			{
				return( nullptr );
			}
			else
			{
				return( &m_objects[ m_ids[ entity.Id() ] ].second );
			}
		}
		else
		{
			return( nullptr );
		}
	}

	void Each( std::function<void( const Entity &entity, const T& )> lambda ) const
	{
		for( const auto &component : m_objects )
		{
			lambda( component.first, component.second );
		}
	}

private:
	std::vector< std::size_t > m_ids;

	std::vector< std::pair< Entity, T > > m_objects;

	std::stack<std::size_t> m_freeIndices;

	std::size_t m_lastObjectIndex = -1;

	const std::size_t m_initialCapacity = 0;

	const std::size_t nullIndex = -1;
};

