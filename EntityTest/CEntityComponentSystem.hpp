#pragma once

#include <typeindex>
#include <typeinfo>
#include <tuple>
#include <memory>
#include <map>
#include <unordered_map>

#include "ComponentTraits.hpp"

#include "Types.hpp"

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
		CLogger::Info( "EntityComponentSystem for:" );
		CLogger::Info( "\tup to " + std::to_string( _Size ) + " entities" );
		CLogger::Info( "\twith these components:" );

		TupleIterator::for_each( m_componentStorage, [] ( auto &slotMap )
		{
			// TODO round MiBi to two decimal places
			CLogger::Info( "\t\t- " + slotMap.ComponentName + " / " + std::to_string( slotMap.SizeInBytes / 1024.0f / 1024.0f ) + " MiBi" );
		} );

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
		if( !m_freeEntities.empty() )
		{
			auto entity = m_freeEntities.back();
			m_freeEntities.pop_back();
			entity.m_version++;
			return( entity );
		}
		else
		{
			CLogger::Info( "exceeded maximum entity count of '" + std::to_string( _Size ) + "'" );
			return( CEntity( CEntity::nullId ) );
		}
	}

	void Destroy( const CEntity &entity )
	{
		TupleIterator::for_each( m_componentStorage, [ &entity ] ( auto &slotMap )
		{
			slotMap.Remove( entity );
		} );

		m_freeEntities.push_back( entity );
	}

	size_t Count() const
	{
		return( _Size - m_freeEntities.size() );
	}

	template< typename T >
	size_t Count() const
	{
		static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

		return( std::get< ComponentSlotMap< T > >( m_componentStorage ).Count() );
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
	void ForEachParralel( L lambda )
	{
		static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

		std::get< ComponentSlotMap< T > >( m_componentStorage ).ForEachParralel( lambda );
	};

	template< typename T, typename L >
	bool Exists( L lambda ) const
	{
		static_assert( tuple_contains_type< ComponentSlotMap< T >, ComponentStorage >::value, "not an allowed type for this ECS" );

		return( std::get< ComponentSlotMap< T > >( m_componentStorage ).Exists( lambda ) );
	}

	template< typename T, typename... Args >
	void CreateSystem( Args... args )
	{
		static_assert( std::is_base_of< CComponentSystem< CEntityComponentSystem< _Size, Types ... > >, T >::value, "must derive from CComponentSystem" );

		auto it = m_systemTypes.find( typeid( T ) );

		if( std::end( m_systemTypes ) != it )
		{
			CLogger::Info( "system '" + std::string( typeid( T ).name() ) + "' already exists" );
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
		static_assert( std::is_base_of< CComponentSystem< CEntityComponentSystem< _Size, Types ... > >, T >::value, "must derive from CComponentSystem" );

		auto it = m_systemTypes.find( typeid( T ) );

		if( std::end( m_systemTypes ) != it )
		{
			m_systems.erase( it->second );
			m_systemTypes.erase( it );
		}
		else
		{
			CLogger::Info( "system '" + std::string( typeid( T ).name() ) + "' does not exist" );
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
		static_assert( std::is_base_of< CComponentSystem< CEntityComponentSystem< _Size, Types ... > >, T >::value, "must derive from CComponentSystem" );

		auto it = m_systemTypes.find( typeid( T ) );

		if( std::end( m_systemTypes ) != it )
		{
			m_systems[ it->second ]->Paused = true;
		}
		else
		{
			CLogger::Info( "system '" + std::string( typeid( T ).name() ) + "' does not exist" );
		}
	}

	template< typename T >
	void UnPauseSystem()
	{
		static_assert( std::is_base_of< CComponentSystem< CEntityComponentSystem< _Size, Types ... > >, T >::value, "must derive from CComponentSystem" );

		auto it = m_systemTypes.find( typeid( T ) );

		if( std::end( m_systemTypes ) != it )
		{
			m_systems[ it->second ]->Paused = false;
		}
		else
		{
			CLogger::Info( "system '" + std::string( typeid( T ).name() ) + "' does not exist" );
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

	u16 m_systemId = 0;

	std::unordered_map< std::type_index, std::string > m_typeNames;

	// two structures needed, so we can check against the type AND have a proper order
	std::unordered_map< std::type_index, u16 > m_systemTypes;
	std::map< u16, std::unique_ptr< CComponentSystem< CEntityComponentSystem< _Size, Types ... > > > > m_systems;
};
