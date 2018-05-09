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

	CScene( const std::uint32_t reserveSize )
	{
		TupleIterator::for_each( m_components, [&reserveSize]( auto x )
		{
			x.Reserve( reserveSize );
		} );
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
		auto &componentContainer = std::get<Container<T>>( m_components );
	
		componentContainer.Add( id, t );
	};

	template< typename T >
	using Container = CSlotMap< T >;

	template<typename T>
	bool HasComponents( const std::uint32_t id ) const
	{
		auto &componentContainer = std::get<Container<T>>( m_components );

		const auto it = componentContainer.find( id );

		if( std::cend( componentContainer ) != it )
		{
			return( true );
		}
		else
		{
			return( false );
		}
	}

	/* TODO
	template< typename First, typename Second, typename ... Rest >
	bool HasComponents( const std::uint32_t id ) const
	{
		return( HasComponents<First>( id ) && HasComponents<Second, Rest...>( id ) );
	}
	*/
	/* TODO
	template< typename T >
	T *GetComponent( const std::uint32_t id )
	{
		auto &componentContainer = std::get<Container<T>>( m_components );

		const auto it = componentContainer.find( id );

		if( std::cend( componentContainer ) != it )
		{
			return( &(*it).second );
		}
		else
		{
			return( nullptr );
		}
	}
	*/
	/* TODO
	template<typename... T_Components>
	std::vector<const CEntity &> GetEntitiesWithComponents() const
	{
		std::vector<const CEntity &> entities;
		entities.reserve( m_entities.size() / 10 );

		const auto it = 

		for( const auto &entity : m_entities )
		{
			if( entity->HasComponents<T_Components...>() )
			{
				entities.push_back( entity );
			}
		}

		return( entities );
	};
	
	template<typename... T_Components>
	std::vector<std::shared_ptr<const CEntity>> GetEntitiesWithAnyComponent() const
	{
		std::vector<std::shared_ptr<const CEntity>> entities;
		entities.reserve( m_entities.size() / 4 );

		for( const auto &entity : m_entities )
		{
			if( entity->HasAnyComponents<T_Components...>() )
			{
				entities.push_back( entity );
			}
		}

		return( entities );
	};
	*/

	/* TODO
	template<typename T>
	void EachComponent( std::function<void( const std::uint32_t id, const T& )> lambda ) const
	{
		for( const auto &component : std::get<Container<T>>( m_components ) )
		{
			lambda( component.first, component.second );
		}
	};
	*/
	/*
	template<typename... T_Components>
	void EachWithComponentsInRadius( const glm::vec3 &position, const float radius, std::function<void( const std::shared_ptr<const CEntity>& )> lambda2 ) const
	{
		const auto radiusSquared = std::pow( radius, 2 );

		EachWithComponents<T_Components...>( [ &position, &radiusSquared, &lambda2 ] ( const std::shared_ptr<const CEntity> &entity )
		{
			// TODO use OcTree
			if( glm::length2( position - entity->Transform.Position() ) <= radiusSquared )
			{
				lambda2( entity );
			}
		} );
	};

	template<typename... T_Components>
	void EachWithAnyComponents( std::function<void( const std::shared_ptr<const CEntity>& )> lambda ) const
	{
		for( const auto &entity : m_entities )
		{
			if( entity->HasAnyComponents<T_Components...>() )
			{
				lambda( entity );
			}
		}
	};

	template<typename... T_Components>
	void EachWithAnyComponentsInRadius( const glm::vec3 &position, const float radius, std::function<void( const std::shared_ptr<const CEntity>& )> lambda2 ) const
	{
		const auto radiusSquared = std::pow( radius, 2 );

		EachWithAnyComponents<T_Components...>( [ &position, &radiusSquared, &lambda2 ] ( const std::shared_ptr<const CEntity> &entity )
		{
			// TODO use OcTree
			if( glm::length2( position - entity->Transform.Position() ) <= radiusSquared )
			{
				lambda2( entity );
			}
		} );
	};
	*/

private:
	std::uint32_t m_lastId = 0;

	std::tuple<Container<Types>...> m_components;
};