#pragma once

#include <typeindex>
#include <typeinfo>
#include <tuple>
#include <memory>
#include <map>
#include <unordered_map>

#include "ComponentTraits.hpp"

#include "SlotMap.hpp"
#include "ComponentSystemBase.hpp"

#include "TupleIterator.hpp"
#include "TupleChecker.hpp"

namespace ecs
{
	template < std::uint32_t _Size, typename... Types >
	class ECS final
	{
		static_assert( _Size != std::numeric_limits<std::uint32_t>::max(), "a maximum of 4294967294 entities is allowed" );

	public:
		ECS( const ECS& ) = delete;

		ECS() noexcept
		{
			m_freeEntities.reserve( _Size );

			for( std::uint32_t i = _Size; i > 0; i-- )
			{
				m_freeEntities.push_back( Entity( i - 1 ) );
			}
		}

		template< typename L >
		void ForEachComponentStorage( L lambda )
		{
			TupleIterator::for_each( m_componentStorage, lambda );
		}

		Entity Create()
		{
			if( !m_freeEntities.empty() )
			{
				auto entity = m_freeEntities.back();
				m_freeEntities.pop_back();
				return( entity );
			}
			else
			{
				throw std::runtime_error( "exceeded maximum entity count of '" + std::to_string( _Size ) + "'" );
			}
		}

		void Destroy( Entity &entity )
		{
			TupleIterator::for_each( m_componentStorage, [ &entity ] ( auto &slotMap )
			{
				slotMap.Remove( entity );
			} );

			// entities with max version can't be reused
			if( entity.Version() != std::numeric_limits<std::uint32_t>::max() )
			{
				entity.m_version++;
				m_freeEntities.push_back( entity );
			}
		}

		std::uint32_t Count() const
		{
			return( _Size - m_freeEntities.size() );
		}

		template< typename T >
		std::uint32_t Count() const
		{
			static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

			return( std::get< ComponentSlotMap< T > >( m_componentStorage ).Count() );
		}

		template< typename T >
		void AddComponent( const Entity &entity, T& t )
		{
			static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

			auto &componentContainer = std::get< ComponentSlotMap< T > >( m_componentStorage );

			componentContainer.Add( entity, t );
		}

		template< typename T >
		void AddComponent( const Entity &entity, T&& t )
		{
			static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

			auto &componentContainer = std::get< ComponentSlotMap< T > >( m_componentStorage );

			componentContainer.Add( entity, std::move( t ) );
		}

		template< typename T >
		void RemoveComponent( const Entity &entity )
		{
			static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

			auto &componentContainer = std::get< ComponentSlotMap< T > >( m_componentStorage );

			componentContainer.Remove( entity );
		}

		template< typename T >
		void RemoveComponentAll()
		{
			static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

			auto &componentContainer = std::get< ComponentSlotMap< T > >( m_componentStorage );

			componentContainer.RemoveAll();
		}

		template< typename T >
		bool HasComponents( const Entity &entity ) const
		{
			static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

			auto &componentContainer = std::get< ComponentSlotMap< T > >( m_componentStorage );

			if( componentContainer.Has( entity ) )
			{
				return( true );
			}
			else
			{
				return( false );
			}
		}

		template< typename First, typename Second, typename ... Rest >
		bool HasComponents( const Entity &entity ) const
		{
			return( HasComponents< First >( entity ) && HasComponents<Second, Rest...>( entity ) );
		}

		template< typename First, typename Second, typename ... Rest >
		bool HasAnyComponents( const Entity &entity ) const
		{
			return( HasComponents< First >( entity ) || HasComponents<Second, Rest...>( entity ) );
		}

		template< typename T >
		T *GetComponent( const Entity &entity )
		{
			static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

			auto &componentContainer = std::get< ComponentSlotMap< T > >( m_componentStorage );

			return( componentContainer.Get( entity ) );
		}

		template< typename T, typename L >
		void ForEachComponent( L lambda )
		{
			static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

			std::get< ComponentSlotMap< T > >( m_componentStorage ).ForEach( lambda );
		}

		template< typename T, typename L >
		void ForEachComponentParralel( L lambda )
		{
			static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

			std::get< ComponentSlotMap< T > >( m_componentStorage ).ForEachParralel( lambda );
		}

		template< typename T, typename L >
		bool Exists( L lambda ) const
		{
			static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

			return( std::get< ComponentSlotMap< T > >( m_componentStorage ).Exists( lambda ) );
		}

		template< typename T, typename... Args >
		void CreateSystem( Args... args )
		{
			static_assert( std::is_base_of< ComponentSystemBase< ECS< _Size, Types ... > >, T >::value, "must derive from ComponentSystemBase" );

			auto it = m_systemTypes.find( typeid( T ) );

			if( std::end( m_systemTypes ) != it )
			{
				throw std::runtime_error( "system '" + std::string( typeid( T ).name() ) + "' already exists" );
			}
			else
			{
				m_systemTypes[ typeid( T ) ] = m_systemIdNext;

				m_systems[ m_systemIdNext ] = std::make_unique< T >( *this, args... );

				m_systemIdNext++;
			}
		}

		template< typename T >
		void DestroySystem()
		{
			static_assert( std::is_base_of< ComponentSystemBase< ECS< _Size, Types ... > >, T >::value, "must derive from ComponentSystemBase" );

			auto it = m_systemTypes.find( typeid( T ) );

			if( std::end( m_systemTypes ) != it )
			{
				m_systems.erase( it->second );
				m_systemTypes.erase( it );
			}
			else
			{
				throw std::runtime_error( "system '" + std::string( typeid( T ).name() ) + "' does not exist" );
			}
		}

		void DestroySystemAll()
		{
			for( auto &systemType : m_systemTypes )
			{
				m_systems.erase( systemType.second );
			}

			m_systemTypes.clear();
		}


		template< typename T >
		void PauseSystem()
		{
			static_assert( std::is_base_of< ComponentSystemBase< ECS< _Size, Types ... > >, T >::value, "must derive from ComponentSystemBase" );

			auto it = m_systemTypes.find( typeid( T ) );

			if( std::end( m_systemTypes ) != it )
			{
				m_systems[ it->second ]->Paused = true;
			}
			else
			{
				throw std::runtime_error( "system '" + std::string( typeid( T ).name() ) + "' does not exist" );
			}
		}

		template< typename T >
		void UnPauseSystem()
		{
			static_assert( std::is_base_of< ComponentSystemBase< ECS< _Size, Types ... > >, T >::value, "must derive from ComponentSystemBase" );

			auto it = m_systemTypes.find( typeid( T ) );

			if( std::end( m_systemTypes ) != it )
			{
				m_systems[ it->second ]->Paused = false;
			}
			else
			{
				throw std::runtime_error( "system '" + std::string( typeid( T ).name() ) + "' does not exist" );
			}
		}

		void ProcessSystems()
		{
			for( auto &system : m_systems )
			{
				if( !system.second->Paused )
				{
					system.second->Process();
				}
			}
		}

	public:
		const std::uint32_t MaxSize = { _Size };

	private:
		template< typename T >
		using ComponentSlotMap = SlotMap< _Size, T >;

		using ComponentStorage = std::tuple< ComponentSlotMap< Types >... >;

		std::vector< Entity > m_freeEntities;

		ComponentStorage m_componentStorage;

		std::uint16_t m_systemIdNext { 0 };

		std::unordered_map< std::type_index, std::string > m_typeNames;

		// two structures needed, so we can check against the type AND have a proper order
		std::unordered_map< std::type_index, std::uint16_t > m_systemTypes;
		std::map< std::uint16_t, std::unique_ptr< ComponentSystemBase< ECS< _Size, Types ... > > > > m_systems;
	};
}