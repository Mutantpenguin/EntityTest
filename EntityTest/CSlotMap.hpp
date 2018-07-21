#pragma once

#include <string>
#include <vector>

#include "CBaseComponent.hpp"

#include "Entity.hpp"

template< size_t _Size, typename T >
class CSlotMap
{
	static_assert( std::is_base_of< CBaseComponent< T >, T >::value, "not of base class 'CBaseComponent'" );

public:
	CSlotMap( const CSlotMap& ) = delete;

	CSlotMap() noexcept :
		m_idMappings( _Size, nullIndex ),
		m_entities( _Size ),
		m_objects( _Size )
	{
		CLogger::Log( "SlotMap for '" + std::string( typeid( T ).name() ) + "'" );
		// TODO round to 2 decimal places
		CLogger::Log( "\tsize: " + std::to_string( SizeInBytes() / 1024.0f / 1024.0f ) + " MiBi" );
	}

	size_t SizeInBytes()
	{
		return( sizeof( T ) * _Size );
	}

	bool Has( const Entity &entity ) const
	{
		const auto &mapping = m_idMappings[ entity.Id() ];

		if( nullIndex == mapping )
		{
			return( false );
		}
		else
		{
			if( m_entities[ mapping ].Version() == entity.Version() )
			{
				return( true );
			}
			else
			{
				return( false );
			}
		}
	}

	void Add( const Entity &entity, T& component )
	{
		// TODO only Add when version matches

		auto &mapping = m_idMappings[ entity.Id() ];

		if( nullIndex == mapping )
		{
			m_lastObjectIndex++;

			mapping = m_lastObjectIndex;

			m_entities[ m_lastObjectIndex ] = entity;
			m_objects[ m_lastObjectIndex ] = component;
		}
		else
		{
			CLogger::Log( "component already exists" );
		}
	}

	void Add( const Entity &entity, T&& component )
	{
		// TODO only Add when version matches

		auto &mapping = m_idMappings[ entity.Id() ];

		if( nullIndex == mapping )
		{
			m_lastObjectIndex++;

			mapping = m_lastObjectIndex;

			m_entities[ m_lastObjectIndex ] = entity;
			m_objects[ m_lastObjectIndex ] = component;
		}
		else
		{
			CLogger::Log( "component already exists" );
		}
	}

	void Remove( const Entity &entity )
	{
		auto &mapping = m_idMappings[ entity.Id() ];

		if( nullIndex != mapping )
		{
			if( m_entities[ mapping ].Version() == entity.Version() )
			{
				if( m_lastObjectIndex > 0 )
				{
					m_idMappings[ m_entities[ m_lastObjectIndex ].Id() ] = mapping;

					m_entities[ mapping ] = m_entities[ m_lastObjectIndex ];
					m_objects[ mapping ]  = m_objects[ m_lastObjectIndex ];

					m_lastObjectIndex--;
				}
				else
				{
					m_lastObjectIndex = nullIndex;
				}

				mapping = nullIndex;
			}
		}
	}

	T* Get( const Entity &entity )
	{
		const auto &mapping = m_idMappings[ entity.Id() ];

		if( nullIndex == mapping )
		{
			return( nullptr );
		}
		else
		{
			if( m_entities[ mapping ].Version() == entity.Version() )
			{
				return( &m_objects[ mapping ] );
			}
			else
			{
				return( nullptr );
			}
		}
	}

	template< typename L >
	void ForEach( L lambda )
	{
		if( nullIndex != m_lastObjectIndex )
		{
			for( size_t i = 0; i <= m_lastObjectIndex; i++ )
			{
				lambda( m_entities[ i ], &m_objects[ i ] );
			}
		}
	}

	template< typename L >
	bool Exists( L lambda ) const
	{
		if( nullIndex != m_lastObjectIndex )
		{
			for( size_t i = 0; i <= m_lastObjectIndex; i++ )
			{
				if( lambda( m_entities[ i ], &m_objects[ i ] ) )
				{
					return( true );
				}
			}
		}
		
		return( false );
	}

	size_t Count() const
	{
		return( m_lastObjectIndex );
	}

private:
	const size_t nullIndex = std::numeric_limits< size_t >::max();

	std::vector< size_t > m_idMappings;

	std::vector< Entity >	m_entities;
	std::vector< T >		m_objects;

	size_t m_lastObjectIndex = nullIndex;
};

