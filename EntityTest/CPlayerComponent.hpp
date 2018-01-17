#pragma once
#include "CBaseComponent.hpp"
class CPlayerComponent :
	public CBaseComponent
{
public:
	CPlayerComponent(const std::shared_ptr< CEntity > &parent);
	~CPlayerComponent();
};

