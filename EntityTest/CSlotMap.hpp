#pragma once

#include <stack>
#include <string>
#include <functional>
#include <vector>

#include "Entity.hpp"

template< typename T, size_t _Size >
class CSlotMap
{
public:
	CSlotMap() :
		m_ids( _Size, nullIndex ),
		m_objects( _Size )
	{
	}

	~CSlotMap()
	{
		CLogger::Log( "size: " + std::to_string( m_objects.size() ) );
		CLogger::Log( "size in KiBi: " + std::to_string( SizeInBytes() / 1024 ) );
	}

	size_t SizeInBytes()
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
		if( nullIndex != m_ids[ entity.Id() ] )
		{
			CLogger::Log( "component already exists" );
			return;
		}
		else
		{
			m_lastObjectIndex++;

			m_ids[ entity.Id() ] = m_lastObjectIndex;

			m_objects[ m_lastObjectIndex ] = std::make_pair( entity, t );
		}
	}

	void Remove( const Entity &entity )
	{
		auto id = m_ids[ entity.Id() ];

		// TODO
		if( id )
		{
			size_t index = it->second;

			m_ids.erase( it );

			if( m_lastObjectIndex > 0 )
			{
				m_objects[ index ] = m_objects[ m_lastObjectIndex ];

				m_ids[ m_objects[ index ].first ].second = index;
			}

			m_lastObjectIndex--;
		}
	}

	T* Get( const Entity &entity )
	{
		if( nullIndex == m_ids[ entity.Id() ] )
		{
			return( nullptr );
		}
		else
		{
			// TODO rename blah
			auto blah = &m_objects[ m_ids[ entity.Id() ] ];

			if( blah->first.Version() == entity.Version() )
			{
				return( &blah->second );
			}
			else
			{
				return( nullptr );
			}
		}
	}

	void Each( std::function<void( const Entity &entity, const T& )> lambda ) const
	{
		for( size_t i = 0; i <= m_lastObjectIndex; i++ )
		{
			auto &component = m_objects[ i ];
			lambda( component.first, component.second );
		}
	}

private:
	std::vector< size_t > m_ids;

	std::vector< std::pair< Entity, T > > m_objects;

	size_t m_lastObjectIndex = -1;

	const size_t m_initialCapacity = 0;

	static const size_t nullIndex = -1;
};

