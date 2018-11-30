#pragma once

#include <string>
#include <vector>

#include "ComponentTraits.hpp"

#include "CLogger.hpp"

#include "CEntity.hpp"

namespace ecs
{
	template< u32 _Size, typename T >
	class CSlotMap
	{
	public:
		CSlotMap( const CSlotMap& ) = delete;

		CSlotMap() noexcept :
			ComponentName { ecs::ComponentTraits<T>::Name },
			SizeInBytes { sizeof( T ) * _Size },
			m_idMappings( _Size, nullIndex ),
			m_entities( _Size ),
			m_objects( _Size )
		{}

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
					throw std::runtime_error( "using stale entity id" );
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
					throw std::runtime_error( "using stale entity id" );
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
						m_objects[ mapping ] = m_objects[ m_lastObjectIndex ];

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
					throw std::runtime_error( "using stale entity id" );
				}
#endif
			}
		}

		void RemoveAll()
		{
			if( nullIndex != m_lastObjectIndex )
			{
				for( u32 i = 0; i <= m_lastObjectIndex; i++ )
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
				for( u32 i = 0; i <= m_lastObjectIndex; i++ )
				{
					lambda( m_entities[ i ], &m_objects[ i ] );
				}
			}
		}

		template< typename L >
		void ForEachParralel( L lambda )
		{
			if( nullIndex != m_lastObjectIndex )
			{
#pragma omp parallel
				for( u32 i = 0; i <= m_lastObjectIndex; i++ )
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
				for( u32 i = 0; i <= m_lastObjectIndex; i++ )
				{
					if( lambda( m_entities[ i ], &m_objects[ i ] ) )
					{
						return( true );
					}
				}
			}

			return( false );
		}

		u32 Count() const
		{
			return( m_lastObjectIndex + 1 );
		}

		const std::string &ComponentName;
		const size_t SizeInBytes;

	private:
		const u32 nullIndex = std::numeric_limits< u32 >::max();

		std::vector< u32 > m_idMappings;

		std::vector< CEntity >	m_entities;
		std::vector< T >		m_objects;

		u32 m_lastObjectIndex = nullIndex;
	};
}