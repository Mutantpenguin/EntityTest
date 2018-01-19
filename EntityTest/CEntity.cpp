#include "CEntity.hpp"

#include "CLogger.hpp"

std::uint32_t CEntity::s_lastId = 0;

CEntity::CEntity(const std::string &name, const std::uint16_t sceneId) :
	m_name{ name },
	m_sceneId { sceneId }
{
	CLogger::Log( "creating entity '" + m_name + "' with id '" + std::to_string( Id ) + "'" );
}

CEntity::~CEntity()
{
	for (auto &component : m_components)
	{
		component = nullptr;
	}
}

const std::string &CEntity::Name(void) const
{
	return(m_name);
}