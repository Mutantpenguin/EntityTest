#pragma once

#include <unordered_map>
#include <functional>

#include <glm/gtx/norm.hpp>

#include "CEntity.hpp"

template <typename... Types>
class CScene final
{
public:
	CScene()
	{}

	~CScene()
	{}
	
	CEntity &CreateEntity( const std::string &name )
	{
		auto id = s_lastId++;

		m_entities.insert( std::make_pair( id, CEntity( name ) ) );

		return( m_entities.at( id ) );
	}

	void DeleteEntity( const std::uint32_t &id )
	{
		m_entities.erase( id );

		// TODO iterate components and delete them
	}

	template< typename T, typename... Args >
	T &AddComponent( const CEntity &entity, Args... args )
	{
		auto &componentContainer = std::get<Container<T>>( m_components );
	
		auto it = componentContainer.find( entity.Id );

		if( std::cend( componentContainer ) != it )
		{
			CLogger::Log( "entity '" + entity.Name() + "' with id '" + std::to_string( entity.Id ) + "' already has a component of type '" + typeid( T ).name() + "'" );

			return( it->second );
		}
		else
		{
			auto it = componentContainer.emplace( entity.Id, T( args... ) );

			return( it.first->second );
		}
	};

	template< typename T >
	using Container = std::unordered_map< std::uint32_t, T >;

	template<typename T>
	bool HasComponents( const CEntity &entity ) const
	{
		auto &componentContainer = std::get<Container<T>>( m_components );

		const auto it = componentContainer.find( entity.Id );

		if( std::cend( componentContainer ) != it )
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
		return( HasComponents<First>( entity ) && HasComponents<Second, Rest...>( entity ) );
	}

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

	template<typename First, typename ... Rest>
	void EachWithComponent( std::function<void( const std::shared_ptr<const CEntity>& )> lambda ) const
	{
		for( const auto &component : auto &componentContainer = std::get<Container<T>>( m_components ); )
		{
			if( entity->HasComponents<T_Components...>() )
			{
				lambda( entity );
			}
		}
	};

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
	Container<CEntity> m_entities;
	
	std::tuple<Container<Types>...> m_components;

	std::uint32_t s_lastId { 0 };
};