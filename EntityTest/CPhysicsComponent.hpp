#pragma once

#include "CComponent.hpp"

struct CPhysicsComponent final : public CComponent<CPhysicsComponent>
{

	int a;

	int b;
};

