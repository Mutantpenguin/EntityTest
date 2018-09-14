#pragma once

#include <typeindex>
#include <typeinfo>
#include <tuple>
#include <memory>
#include <map>
#include <unordered_map>

#include "CSlotMap.hpp"
#include "CComponentSystem.hpp"

#include "TupleIterator.hpp"
#include "TupleChecker.hpp"

template < size_t _Size, typename... Types >
class CEntityComponentSystem final
{
public:
	CEntityComponentSystem( const CEntityComponentSystem& ) = delete;

	CEntityComponentSystem() noexcept
	{
		CLogger::Log( std::string( typeid( this ).name() ) );
		CLogger::Log( "\tmax entities: " + std::to_string( _Size ) );

		m_freeEntities.reserve( _Size );

		for( size_t i = _Size; i > 0; i-- )
		{
			m_freeEntities.push_back( CEntity( i - 1 ) );
		}
	}

	~CEntityComponentSystem()
	{}

	CEntity Create()
	{
		// TODO implement "version" in Entity when stack is used. increment "version" when popping from stack
		// TODO use "version" in Entity to check against it in several places

		if( !m_freeEntities.empty() )
		{
			auto entity = m_freeEntities.back();
			m_freeEntities.pop_back();
			entity.m_version++;
			return( entity );
		}
		else
		{
			CLogger::Log( "exceeded maximum entity count of '" + std::to_string( _Size ) + "'" );
			return( CEntity( CEntity::nullId ) );
		}
	}

	void Destroy( const CEntity &entity )
	{
		TupleIterator::for_each( m_componentStorage, [ &entity ] ( auto &x )
		{
			x.Remove( entity );
		} );

		m_freeEntities.push_back( entity );
	}

	template< typename T >
	void AddComponent( const CEntity &entity, T& t )
	{
		static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

		auto &componentContainer = std::get< ComponentSlotMap< T > >( m_componentStorage );
	
		componentContainer.Add( entity, t );
	};
	
	template< typename T >
	void AddComponent( const CEntity &entity, T&& t )
	{
		static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

		auto &componentContainer = std::get< ComponentSlotMap< T > >( m_componentStorage );

		componentContainer.Add( entity, std::move( t ) );
	};

	template< typename T >
	void RemoveComponent( const CEntity &entity )
	{
		static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );
		
		auto &componentContainer = std::get< ComponentSlotMap< T > >( m_componentStorage );

		componentContainer.Remove( entity );
	};
	
	template< typename T >
	void RemoveComponentAll()
	{
		static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

		auto &componentContainer = std::get< ComponentSlotMap< T > >( m_componentStorage );

		componentContainer.RemoveAll();
	}

	template< typename T >
	bool HasComponents( const CEntity &entity ) const
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
	bool HasComponents( const CEntity &entity ) const
	{
		return( HasComponents< First >( entity ) && HasComponents<Second, Rest...>( entity ) );
	}

	template< typename First, typename Second, typename ... Rest >
	bool HasAnyComponents( const CEntity &entity ) const
	{
		return( HasComponents< First >( entity ) || HasComponents<Second, Rest...>( entity ) );
	}

	template< typename T >
	T *GetComponent( const CEntity &entity )
	{
		static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

		auto &componentContainer = std::get< ComponentSlotMap< T > >( m_componentStorage );

		return( componentContainer.Get( entity ) );
	}

	template< typename T, typename L >
	void ForEach( L lambda )
	{
		static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

		std::get< ComponentSlotMap< T > >( m_componentStorage ).ForEach( lambda );
	};

	template< typename T, typename L >
	bool Exists( L lambda ) const
	{
		static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

		return( std::get< ComponentSlotMap< T > >( m_componentStorage ).Exists( lambda ) );
	}

	template< typename T >
	size_t Count() const
	{
		static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

		return( std::get< ComponentSlotMap< T > >( m_componentStorage ).Count() );
	}

	template< typename T, typename... Args >
	void CreateSystem( Args... args )
	{
		auto it = m_systemTypes.find( typeid( T ) );

		if( std::end( m_systemTypes ) != it )
		{
			CLogger::Log( "system '" + std::string( typeid( T ).name() ) + "' already exists" );
		}
		else
		{
			m_systemTypes[ typeid( T ) ] = m_systemId;

			m_systems[ m_systemId ] = std::make_unique< T >( *this, args... );

			m_systemId++;
		}
	}

	template< typename T >
	void DestroySystem()
	{
		auto it = m_systemTypes.find( typeid( T ) );

		if( std::end( m_systemTypes ) != it )
		{
			m_systems.erase( it->second );
			m_systemTypes.erase( it );
		}
		else
		{
			CLogger::Log( "system '" + std::string( typeid( T ).name() ) + "' does not exist" );
		}
	}

	template< typename T >
	void PauseSystem()
	{
		auto it = m_systemTypes.find( typeid( T ) );

		if( std::end( m_systemTypes ) != it )
		{
			m_systems[ it->second ]->Paused = true;
		}
		else
		{
			CLogger::Log( "system '" + std::string( typeid( T ).name() ) + "' does not exist" );
		}
	}

	template< typename T >
	void UnPauseSystem()
	{
		auto it = m_systemTypes.find( typeid( T ) );

		if( std::end( m_systemTypes ) != it )
		{
			m_systems[ it->second ]->Paused = false;
		}
		else
		{
			CLogger::Log( "system '" + std::string( typeid( T ).name() ) + "' does not exist" );
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
	const size_t MaxSize = { _Size };

private:
	template< typename T >
	using ComponentSlotMap = CSlotMap< _Size, T >;

	using ComponentStorage = std::tuple< ComponentSlotMap< Types >... >;

	std::vector< CEntity > m_freeEntities;

	ComponentStorage m_componentStorage;

	std::uint16_t m_systemId = 0;

	// two structures needed, so we can check against the type AND have a proper order
	std::unordered_map< std::type_index, std::uint16_t > m_systemTypes;
	std::map< std::uint16_t, std::unique_ptr< CComponentSystem > > m_systems;
};
