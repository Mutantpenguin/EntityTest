#pragma once

#include <unordered_map>
#include <functional>
#include <tuple>
#include <utility>

#include <glm/gtx/norm.hpp>

#include "CEntity.hpp"

#include "CSlotMap.hpp"

#include "TupleIterator.hpp"

template <typename... Types>
class CScene final
{
public:
	CScene()
	{}

	CScene( const std::uint32_t reserveSize ) :
		m_components( (sizeof( Types ), reserveSize )... )
	{
	}

	~CScene()
	{}

	std::uint32_t CreateEntity()
	{
		return( m_lastId++ );
	}

	template< typename T >
	void AddComponent( const std::uint32_t &id, T& t )
	{
		auto &componentContainer = std::get< CSlotMap< T > >( m_components );
	
		componentContainer.Add( id, t );
	};
	
	template< typename T >
	void AddComponent( const std::uint32_t &id, T&& t )
	{
		auto &componentContainer = std::get< CSlotMap< T > >( m_components );

		componentContainer.Add( id, t );
	};

	template<typename T>
	bool HasComponents( const std::uint32_t id ) const
	{
		auto &componentContainer = std::get< CSlotMap< T > >( m_components );

		if( componentContainer.Has( id ) )
		{
			return( true );
		}
		else
		{
			return( false );
		}
	}

	template< typename First, typename Second, typename ... Rest >
	bool HasComponents( const std::uint32_t id ) const
	{
		return( HasComponents<First>( id ) && HasComponents<Second, Rest...>( id ) );
	}

	template< typename First, typename Second, typename ... Rest >
	bool HasAnyComponents( const std::uint32_t id ) const
	{
		return( HasComponents<First>( id ) || HasComponents<Second, Rest...>( id ) );
	}

	template< typename T >
	T *GetComponent( const std::uint32_t id )
	{
		auto &componentContainer = std::get< CSlotMap< T > >( m_components );

		return( componentContainer.Get( id ) );
	}

	template<typename T>
	void EachComponent( std::function<void( const std::uint32_t id, const T& )> lambda ) const
	{
		std::get< CSlotMap< T > >( m_components ).Each( lambda );
	};
	/* TODO
	template<typename... T_Components>
	void EachWithAnyComponents( std::function<void( const std::uint32_t id, const T& )> lambda ) const
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