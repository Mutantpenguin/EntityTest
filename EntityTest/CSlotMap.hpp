#pragma once

#include <string>
#include <vector>

#include "CLogger.hpp"

#include "CEntity.hpp"

template< size_t _Size, typename T >
class CSlotMap
{
public:
	CSlotMap( const CSlotMap& ) = delete;

	CSlotMap() noexcept :
		m_idMappings( _Size, nullIndex ),
		m_entities( _Size ),
		m_objects( _Size )
	{
		CLogger::Info( "SlotMap for '" + std::string( typeid( T ).name() ) + "'" );
		// TODO round to 2 decimal places
		CLogger::Info( "\tsize: " + std::to_string( SizeInBytes() / 1024.0f / 1024.0f ) + " MiBi" );
	}

	size_t SizeInBytes()
	{
		return( sizeof( T ) * _Size );
	}

	bool Has( const CEntity &entity ) const
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

	void Add( const CEntity &entity, T& component )
	{
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
			if( m_entities[ mapping ].Version() == entity.Version() )
			{
				m_objects[ mapping ] = component;
			}
#ifndef NDEBUG
			else
			{
				CLogger::Info( "using stale entity id" );
			}
#endif
		}
	}

	void Add( const CEntity &entity, T&& component )
	{
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
			if( m_entities[ mapping ].Version() == entity.Version() )
			{
				m_objects[ mapping ] = component;
			}
#ifndef NDEBUG
			else
			{
				CLogger::Info( "using stale entity id" );
			}
#endif
		}
	}

	void Remove( const CEntity &entity )
	{
		auto &mapping = m_idMappings[ entity.Id() ];

		if( nullIndex != mapping )
		{
			if( m_entities[ mapping ].Version() == entity.Version() )
			{
				if( m_lastObjectIndex > 0 )
				{
					// let the entity which lied at the lastObjectIndex point to the one we deleted
					m_idMappings[ m_entities[ m_lastObjectIndex ].Id() ] = mapping;

					//then copy over the data of the last entity
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
#ifndef NDEBUG
			else
			{
				CLogger::Info( "using stale entity id" );
			}
#endif
		}
	}

	void RemoveAll()
	{
		if( nullIndex != m_lastObjectIndex )
		{
			for( size_t i = 0; i <= m_lastObjectIndex; i++ )
			{
				const auto &entity = m_entities[ i ];
				m_idMappings[ entity.Id() ] = nullIndex;
			}

			m_lastObjectIndex = nullIndex;
		}
	}

	T* Get( const CEntity &entity )
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

	std::vector< CEntity >	m_entities;
	std::vector< T >		m_objects;

	size_t m_lastObjectIndex = nullIndex;
};

