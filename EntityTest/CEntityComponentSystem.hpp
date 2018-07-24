#pragma once

#include <tuple>

#include <glm/gtx/norm.hpp>

#include "CSlotMap.hpp"

#include "TupleIterator.hpp"

#include "ObsoleteCEntity.hpp"

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
		TupleIterator::for_each( m_components, [ &entity ] ( auto &x )
		{
			x.Remove( entity );
		} );

		m_freeEntities.push_back( entity );
	}

	template< typename T >
	void AddComponent( const CEntity &entity, T& t )
	{
		static_assert( std::is_base_of< CBaseComponent< T >, T >::value, "not of base class 'CBaseComponent'" );

		auto &componentContainer = std::get< ComponentStorage< T > >( m_components );
	
		componentContainer.Add( entity, t );
	};
	
	template< typename T >
	void AddComponent( const CEntity &entity, T&& t )
	{
		static_assert( std::is_base_of< CBaseComponent< T >, T >::value, "not of base class 'CBaseComponent'" );

		auto &componentContainer = std::get< ComponentStorage< T > >( m_components );

		componentContainer.Add( entity, std::move( t ) );
	};

	template< typename T >
	void RemoveComponent( const CEntity &entity )
	{
		static_assert( std::is_base_of< CBaseComponent< T >, T >::value, "not of base class 'CBaseComponent'" );
		
		auto &componentContainer = std::get< ComponentStorage< T > >( m_components );

		componentContainer.Remove( entity );
	};
	
	template< typename T >
	void RemoveComponentAll()
	{
		static_assert( std::is_base_of< CBaseComponent< T >, T >::value, "not of base class 'CBaseComponent'" );

		auto &componentContainer = std::get< ComponentStorage< T > >( m_components );

		componentContainer.RemoveAll();
	}

	template< typename T >
	bool HasComponents( const CEntity &entity ) const
	{
		static_assert( std::is_base_of< CBaseComponent< T >, T >::value, "not of base class 'CBaseComponent'" );

		auto &componentContainer = std::get< ComponentStorage< T > >( m_components );

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
		static_assert( std::is_base_of< CBaseComponent< T >, T >::value, "not of base class 'CBaseComponent'" );

		auto &componentContainer = std::get< ComponentStorage< T > >( m_components );

		return( componentContainer.Get( entity ) );
	}

	template< typename T, typename L >
	void ForEach( L lambda )
	{
		static_assert( std::is_base_of< CBaseComponent< T >, T >::value, "not of base class 'CBaseComponent'" );

		std::get< ComponentStorage< T > >( m_components ).ForEach( lambda );
	};

	template< typename T, typename L >
	bool Exists( L lambda ) const
	{
		static_assert( std::is_base_of< CBaseComponent< T >, T >::value, "not of base class 'CBaseComponent'" );

		return( std::get< ComponentStorage< T > >( m_components ).Exists( lambda ) );
	}

	template< typename T >
	size_t Count() const
	{
		static_assert( std::is_base_of< CBaseComponent< T >, T >::value, "not of base class 'CBaseComponent'" );

		return( std::get< ComponentStorage< T > >( m_components ).Count() );
	}

public:
	const size_t MaxSize = { _Size };

private:
	template< typename T >
	using ComponentStorage = CSlotMap< _Size, T >;

	std::vector< CEntity > m_freeEntities;

	std::tuple< ComponentStorage< Types >... > m_components;
};