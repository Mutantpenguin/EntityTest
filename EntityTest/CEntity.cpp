#include "CEntity.hpp"

#include "CLogger.hpp"

std::uint32_t CEntity::s_lastId = 0;

CEntity::CEntity( const std::string &name ) :
	m_name { name }
{
	// CLogger::Log( "creating entity '" + m_name + "' with id '" + std::to_string( Id ) + "'" );
}

CEntity::~CEntity()
{}

const std::string &CEntity::Name( void ) const
{
	return( m_name );
}