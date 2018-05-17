#pragma once

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
		m_idMappings( _Size, nullIndex ),
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
		if( nullIndex == m_idMappings[ entity.Id() ] )
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
		auto &mapping = m_idMappings[ entity.Id() ];

		if( nullIndex != mapping )
		{
			CLogger::Log( "component already exists" );
			return;
		}
		else
		{
			m_lastObjectIndex++;

			mapping = m_lastObjectIndex;

			auto &object = m_objects[ m_lastObjectIndex ];
			object.first = entity;
			object.second = component;
		}
	}

	void Add( const Entity &entity, T&& component )
	{
		auto &mapping = m_idMappings[ entity.Id() ];

		if( nullIndex != mapping )
		{
			CLogger::Log( "component already exists" );
			return;
		}
		else
		{
			m_lastObjectIndex++;

			mapping = m_lastObjectIndex;

			auto &object = m_objects[ m_lastObjectIndex ];
			object.first = entity;
			object.second = component;
		}
	}

	void Remove( const Entity &entity )
	{
		const auto index = m_idMappings[ entity.Id() ];

		if( nullIndex != index )
		{
			m_idMappings[ entity.Id() ] = nullIndex;

			if( m_lastObjectIndex > 0 )
			{
				m_objects[ index ] = m_objects[ m_lastObjectIndex ];

				m_idMappings[ m_objects[ index ].first.Id() ] = index;

				m_lastObjectIndex--;
			}
			else
			{
				m_lastObjectIndex = nullIndex;
			}
			
		}
	}

	T* Get( const Entity &entity )
	{
		auto &mapping = m_idMappings[ entity.Id() ];

		if( nullIndex == mapping )
		{
			return( nullptr );
		}
		else
		{
			// TODO move version check up to CScene.hpp?
			auto object = &m_objects[ mapping ];

			if( object->first.Version() == entity.Version() )
			{
				return( &object->second );
			}
			else
			{
				return( nullptr );
			}
		}
	}

	void Each( std::function<void( const Entity &entity, const T& )> lambda ) const
	{
		if( nullIndex != m_lastObjectIndex )
		{
			for( size_t i = 0; i <= m_lastObjectIndex; i++ )
			{
				auto &component = m_objects[ i ];
				lambda( component.first, component.second );
			}
		}
	}

private:
	std::vector< size_t > m_idMappings;

	std::vector< std::pair< Entity, T > > m_objects;

	size_t m_lastObjectIndex = nullIndex;

	static const size_t nullIndex = -1;
};

