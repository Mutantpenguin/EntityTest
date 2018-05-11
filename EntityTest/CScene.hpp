#pragma once

#include <functional>
#include <tuple>
#include <utility>

#include <glm/gtx/norm.hpp>

#include "CSlotMap.hpp"

#include "TupleIterator.hpp"

#include "Entity.hpp"

template <typename... Types>
class CScene final
{
public:
	CScene()
	{}

	CScene( const std::size_t reserveSize ) :
		m_components( (sizeof( Types ), reserveSize )... )
	{
	}

	~CScene()
	{}

	Entity CreateEntity()
	{
		// TODO implement stack for freed ids
		// TODO implement "version" in Entity when stack is used. increment "version" when popping from stack
		// TODO use "version" in Entity to check against it in several places
		return( Entity( m_lastId++ ) );
	}

	void DestroyEntity( const Entity &entity )
	{
		TupleIterator::for_each( m_components, [ &entity ] ( auto x )
		{
			x.Remove( entity );
		} );

		// TODO push id to stack for freed ids
	}

	template< typename T >
	void AddComponent( const Entity &entity, T& t )
	{
		auto &componentContainer = std::get< CSlotMap< T > >( m_components );
	
		componentContainer.Add( entity, t );
	};
	
	template< typename T >
	void AddComponent( const Entity &entity, T&& t )
	{
		auto &componentContainer = std::get< CSlotMap< T > >( m_components );

		componentContainer.Add( entity, t );
	};

	template<typename T>
	bool HasComponents( const Entity &entity ) const
	{
		auto &componentContainer = std::get< CSlotMap< T > >( m_components );

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
		return( HasComponents<First>( entity ) && HasComponents<Second, Rest...>( entity ) );
	}

	template< typename First, typename Second, typename ... Rest >
	bool HasAnyComponents( const Entity &entity ) const
	{
		return( HasComponents<First>( entity ) || HasComponents<Second, Rest...>( entity ) );
	}

	template< typename T >
	T *GetComponent( const Entity &entity )
	{
		auto &componentContainer = std::get< CSlotMap< T > >( m_components );

		return( componentContainer.Get( entity ) );
	}

	template<typename T>
	void EachComponent( std::function<void( const Entity &entity, const T& )> lambda ) const
	{
		std::get< CSlotMap< T > >( m_components ).Each( lambda );
	};

	/* TODO
	template<typename... T_Components>
	void EachWithAnyComponents( std::function<void( const Entity &entity, const T& )> lambda ) const
	{
		for( const auto &entity : m_entities )
		{
			if( entity->HasAnyComponents<T_Components...>() )
			{
				lambda( entity );
			}
		}
	};
	*/
private:
	std::uint32_t m_lastId = 0;

	std::tuple< CSlotMap< Types >... > m_components;
};