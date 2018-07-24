#pragma once

#include "CEntityComponentSystem.hpp"

#include "CPhysicsComponent.hpp"
#include "CPlayerComponent.hpp"
#include "CDebugNameComponent.hpp"
#include "CTransformComponent.hpp"

#include "CMovementComponent.hpp"

#include "CBombComponent.hpp"
#include "CExplosionComponent.hpp"
#include "CHealthComponent.hpp"

using MyECS = CEntityComponentSystem<	10000,
										CPhysicsComponent,
										CPlayerComponent,
										CDebugNameComponent,
										CTransformComponent,
										CBombComponent,
										CExplosionComponent,
										CHealthComponent,
										CMovementComponent >;