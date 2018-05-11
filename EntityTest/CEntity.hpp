#ifndef CENTITY_HPP
#define CENTITY_HPP

#include <string>
#include <memory>
#include <array>

#include "CLogger.hpp"

#include "CTransformComponent.hpp"
#include "CBoundingBox.hpp"


class CEntity final
{
public:
	explicit CEntity( const std::string &name );
	~CEntity();

	const std::string &Name( void ) const;

	const std::uint32_t Id = ++s_lastId;

	CTransformComponent Transform;
	CBoundingBox BoundingBox;

private:
	const std::string m_name;

	static std::uint32_t s_lastId;
};

#endif // COBJECT_HPP