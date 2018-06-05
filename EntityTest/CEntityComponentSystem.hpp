#pragma once

#include <functional>
#include <tuple>

#include <glm/gtx/norm.hpp>

#include "CSlotMap.hpp"

#include "TupleIterator.hpp"

#include "Entity.hpp"

template < size_t _Size, typename... Types >
class CEntityComponentSystem final
{
public:
	CEntityComponentSystem( const CEntityComponentSystem& ) = delete;

	CEntityComponentSystem()
	{
		CLogger::Log( std::string( typeid( this ).name() ) );
		CLogger::Log( "\tmax entities: " + std::to_string( _Size ) );

		m_freeEntities.reserve( _Size );
	}

	~CEntityComponentSystem()
	{}

	Entity CreateEntity()
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
			m_lastId++;

			if( m_lastId > maxId )
			{
				CLogger::Log( "exceeded maximum entity count of '" + std::to_string( _Size ) + "'" );
				return( Entity( Entity::nullId ) );
			}
			else
			{
				return( Entity( m_lastId ) );
			}
		}
	}

	void DestroyEntity( const Entity &entity )
	{
		TupleIterator::for_each( m_components, [ &entity ] ( auto &x )
		{
			x.Remove( entity );
		} );

		m_freeEntities.push_back( entity );
	}

	template< typename T >
	void AddComponent( const Entity &entity, T& t )
	{
		auto &componentContainer = std::get< ComponentStorage< T > >( m_components );
	
		componentContainer.Add( entity, t );
	};
	
	template< typename T >
	void AddComponent( const Entity &entity, T&& t )
	{
		auto &componentContainer = std::get< ComponentStorage< T > >( m_components );

		componentContainer.Add( entity, std::move( t ) );
	};

	template< typename T >
	bool HasComponents( const Entity &entity ) const
	{
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
		auto &componentContainer = std::get< ComponentStorage< T > >( m_components );

		return( componentContainer.Get( entity ) );
	}

	template< typename T >
	void EachComponent( std::function< void( const Entity &entity, const T& ) > lambda ) const
	{
		std::get< ComponentStorage< T > >( m_components ).Each( lambda );
	};


private:
	template< typename T >
	using ComponentStorage = CSlotMap< T, _Size >;

	static const size_t maxId = _Size - 1;

	size_t m_lastId = Entity::nullId;
	std::vector< Entity > m_freeEntities;

	std::tuple< ComponentStorage< Types >... > m_components;
};