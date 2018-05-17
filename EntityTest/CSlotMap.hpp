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
	CSlotMap( const CSlotMap& ) = delete;

	CSlotMap() :
		m_idMapping( _Size, nullIndex ),
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
		if( nullIndex == m_idMapping[ entity.Id() ] )
		{
			return( false );
		}
		else
		{
			return( true );
		}
	}

	void Add( const Entity &entity, T& component )
	{
		if( nullIndex != m_idMapping[ entity.Id() ] )
		{
			CLogger::Log( "component already exists" );
			return;
		}
		else
		{
			m_lastObjectIndex++;

			m_idMapping[ entity.Id() ] = m_lastObjectIndex;

			m_objects[ m_lastObjectIndex ].first = entity;
			m_objects[ m_lastObjectIndex ].second = component;
		}
	}

	void Add( const Entity &entity, T&& component )
	{
		// TODO FIXME why is this function never reached?

		if( nullIndex != m_idMapping[ entity.Id() ] )
		{
			CLogger::Log( "component already exists" );
			return;
		}
		else
		{
			m_lastObjectIndex++;

			m_idMapping[ entity.Id() ] = m_lastObjectIndex;

			m_objects[ m_lastObjectIndex ].first = entity;
			m_objects[ m_lastObjectIndex ].second = component;
		}
	}

	void Remove( const Entity &entity )
	{
		const auto index = m_idMapping[ entity.Id() ];

		if( nullIndex != index )
		{
			m_idMapping[ entity.Id() ] = nullIndex;

			if( m_lastObjectIndex > 0 )
			{
				m_objects[ index ] = m_objects[ m_lastObjectIndex ];

				m_idMapping[ m_objects[ index ].first.Id() ] = index;
			}

			m_lastObjectIndex--;
		}
	}

	T* Get( const Entity &entity )
	{
		if( nullIndex == m_idMapping[ entity.Id() ] )
		{
			return( nullptr );
		}
		else
		{
			// TODO rename blah
			// TODO move version check up to CScene.hpp?
			auto blah = &m_objects[ m_idMapping[ entity.Id() ] ];

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
		if( -1 != m_lastObjectIndex )
		{
			for( size_t i = 0; i <= m_lastObjectIndex; i++ )
			{
				auto &component = m_objects[ i ];
				lambda( component.first, component.second );
			}
		}
	}

private:
	std::vector< size_t > m_idMapping;

	std::vector< std::pair< Entity, T > > m_objects;

	size_t m_lastObjectIndex = -1;

	static const size_t nullIndex = -1;
};

