#include "CScene.hpp"

#include <glm/gtx/norm.hpp>

#include "CLogger.hpp"

std::uint16_t CScene::s_lastId = 0;

CScene::CScene()
{}

CScene::~CScene()
{}

std::shared_ptr< CEntity > CScene::CreateEntity( const std::string &name )
{
	auto entity = std::make_shared< CEntity >( name, m_id );

	m_entities.insert( entity );

	return( entity );
}

void CScene::DeleteEntity( const std::shared_ptr< const CEntity > &entity )
{
	m_entities.erase( entity );
}

const std::shared_ptr< const CEntity > &CScene::Camera( void ) const
{
	return( m_cameraEntity );
}

void CScene::Camera( const std::shared_ptr< const CEntity > &cameraEntity )
{
	if( !cameraEntity->HasComponents<CCameraComponent>() )
	{
		CLogger::Log( "entity '" + cameraEntity->Name() + "' with id '" + std::to_string( cameraEntity->Id ) + "' has no CCameraComponent" );
		return;
	}

	if( cameraEntity->m_sceneId != m_id )
	{
		CLogger::Log( "camera '" + cameraEntity->Name() + "' with id '" + std::to_string( cameraEntity->Id ) + "' does not belong to this scene" );
	}

	m_cameraEntity = cameraEntity;
}