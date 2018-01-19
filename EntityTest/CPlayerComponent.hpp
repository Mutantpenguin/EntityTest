#pragma once

#include "EComponentIndex.hpp"
#include "CBaseComponent.hpp"

class CPlayerComponent :
	public CBaseComponent
{
public:
	CPlayerComponent(const std::shared_ptr< CEntity > &parent);
	virtual ~CPlayerComponent();

	static const std::uint16_t Index = static_cast<std::uint16_t>(EComponentIndex::PLAYER);
};

