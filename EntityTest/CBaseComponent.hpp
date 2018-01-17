#ifndef CBASECOMPONENT_HPP
#define CBASECOMPONENT_HPP

#include <memory>

#include "CEntity.hpp"

class CBaseComponent
{
public:
	CBaseComponent( const std::shared_ptr< CEntity > &parent ) :
		m_parent { parent }
	{};

	virtual ~CBaseComponent()
	{};

protected:
	const std::shared_ptr< CEntity > m_parent;
};

#endif // CBASECOMPONENT_HPP