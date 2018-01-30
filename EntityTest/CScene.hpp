#ifndef CSCENE_HPP
#define CSCENE_HPP

#include <vector>
#include <set>
#include <functional>

#include <glm/gtx/norm.hpp>

#include "CEntity.hpp"

#include "CCameraComponent.hpp"

class CScene
{
public:
	struct MeshInstance
	{
		CTransform Transform;
		float viewDepth;
	};

	using TMeshes = std::vector< MeshInstance >;

public:
	CScene();
	~CScene();

	std::shared_ptr< CEntity > CreateEntity( const std::string &name );
	void DeleteEntity( const std::shared_ptr< const CEntity > &entity );

	const std::shared_ptr< const CEntity > &Camera( void ) const;
	void Camera( const std::shared_ptr< const CEntity > &cameraEntity );

	template<typename... T_Components>
	std::vector<std::shared_ptr<const CEntity>> GetEntitiesWithComponents() const
	{
		std::vector<std::shared_ptr<const CEntity>> entities;
		entities.reserve( m_entities.size() / 4 );

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
	void Each( std::function<void( const std::shared_ptr<const CEntity>& )> lambda ) const
	{
		for( const auto &entity : m_entities )
		{
			if( entity->HasComponents<T_Components...>() )
			{
				lambda( entity );
			}
		}
	};

	template<typename... T_Components>
	void EachInRadius( const glm::vec3 &position, const float radius, std::function<void( const std::shared_ptr<const CEntity>& )> lambda2 ) const
	{
		const auto radiusSquared = std::pow( radius, 2 );

		Each<T_Components...>( [ &position, &radiusSquared, &lambda2 ] ( const std::shared_ptr<const CEntity> &entity )
		{
			// TODO use OcTree
			// TODO use BoundingSphere/BoundingBox of entity?
			if( glm::length2( position - entity->Transform.Position() ) <= radiusSquared )
			{
				lambda2( entity );
			}
		} );
	};

private:
	std::set< std::shared_ptr< const CEntity > > m_entities;

	std::shared_ptr< const CEntity > m_cameraEntity;

	const std::uint16_t m_id = ++s_lastId;

	static std::uint16_t s_lastId;
};

#endif // CSCENE_HPP