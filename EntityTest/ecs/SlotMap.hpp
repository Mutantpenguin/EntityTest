#pragma once

#include <string>
#include <vector>

#include "ComponentTraits.hpp"

#include "Id.hpp"

namespace ecs
{
	template< std::uint32_t _Size, typename T >
	class SlotMap
	{
	public:
		SlotMap( const SlotMap& ) = delete;

		SlotMap() noexcept :
			ComponentName { ecs::ComponentTraits<T>::Name },
			SizeInBytes { sizeof( T ) * _Size },
			m_idMappings( _Size, nullIndex ),
			m_ids( _Size ),
			m_objects( _Size )
		{}

		bool Has( const Id &id ) const
		{
			const auto &mapping = m_idMappings[ id.Value() ];

			if( nullIndex == mapping )
			{
				return( false );
			}
			else
			{
				if( m_ids[ mapping ].Generation() == id.Generation() )
				{
					return( true );
				}
				else
				{
					return( false );
				}
			}
		}

		void Add( const Id &id, T& component )
		{
			auto &mapping = m_idMappings[ id.Value() ];

			if( nullIndex == mapping )
			{
				m_lastObjectIndex++;

				mapping = m_lastObjectIndex;

				m_ids[ m_lastObjectIndex ] = id;
				m_objects[ m_lastObjectIndex ] = component;
			}
			else
			{
				if( m_ids[ mapping ].Generation() == id.Generation() )
				{
					m_objects[ mapping ] = component;
				}
#ifndef NDEBUG
				else
				{
					throw std::runtime_error( "using stale id id" );
				}
#endif
			}
		}

		void Add( const Id &id, T&& component )
		{
			auto &mapping = m_idMappings[ id.Value() ];

			if( nullIndex == mapping )
			{
				m_lastObjectIndex++;

				mapping = m_lastObjectIndex;

				m_ids[ m_lastObjectIndex ]		= id;
				m_objects[ m_lastObjectIndex ]	= component;
			}
			else
			{
				if( m_ids[ mapping ].Generation() == id.Generation() )
				{
					m_objects[ mapping ] = component;
				}
#ifndef NDEBUG
				else
				{
					throw std::runtime_error( "using stale id id" );
				}
#endif
			}
		}

		void Remove( const Id &id )
		{
			auto &mapping = m_idMappings[ id.Value() ];

			if( nullIndex != mapping )
			{
				if( m_ids[ mapping ].Generation() == id.Generation() )
				{
					if( m_lastObjectIndex > 0 )
					{
						// let the id which lied at the lastObjectIndex point to the one we deleted
						m_idMappings[ m_ids[ m_lastObjectIndex ].Value() ] = mapping;

						//then copy over the data of the last id
						m_ids[ mapping ]		= m_ids[ m_lastObjectIndex ];
						m_objects[ mapping ]	= m_objects[ m_lastObjectIndex ];

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
					throw std::runtime_error( "using stale id id" );
				}
#endif
			}
		}

		void RemoveAll()
		{
			if( nullIndex != m_lastObjectIndex )
			{
				for( std::uint32_t i = 0; i <= m_lastObjectIndex; i++ )
				{
					const auto &id = m_ids[ i ];
					m_idMappings[ id.Value() ] = nullIndex;
				}

				m_lastObjectIndex = nullIndex;
			}
		}

		T* Get( const Id &id )
		{
			const auto &mapping = m_idMappings[ id.Value() ];

			if( nullIndex == mapping )
			{
				return( nullptr );
			}
			else
			{
				if( m_ids[ mapping ].Generation() == id.Generation() )
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
				for( std::uint32_t i = 0; i <= m_lastObjectIndex; i++ )
				{
					lambda( m_ids[ i ], &m_objects[ i ] );
				}
			}
		}

		template< typename L >
		void ForEachParralel( L lambda )
		{
			if( nullIndex != m_lastObjectIndex )
			{
#pragma omp parallel
				for( std::uint32_t i = 0; i <= m_lastObjectIndex; i++ )
				{
					lambda( m_ids[ i ], &m_objects[ i ] );
				}
			}
		}

		template< typename L >
		bool Exists( L lambda ) const
		{
			if( nullIndex != m_lastObjectIndex )
			{
				for( std::uint32_t i = 0; i <= m_lastObjectIndex; i++ )
				{
					if( lambda( m_ids[ i ], &m_objects[ i ] ) )
					{
						return( true );
					}
				}
			}

			return( false );
		}

		std::uint32_t Count() const
		{
			return( m_lastObjectIndex + 1 );
		}

		const std::string &ComponentName;
		const size_t SizeInBytes;

	private:
		const std::uint32_t nullIndex = std::numeric_limits< std::uint32_t >::max();

		std::vector< std::uint32_t > m_idMappings;

		std::vector< Id >	m_ids;
		std::vector< T >	m_objects;

		std::uint32_t m_lastObjectIndex = nullIndex;
	};
}