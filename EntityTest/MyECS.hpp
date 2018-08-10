#pragma once

#include "CEntityComponentSystem.hpp"

#include "CPhysicsComponent.hpp"
#include "CPlayerComponent.hpp"
#include "CDebugNameComponent.hpp"

#include "CMovementComponent.hpp"

#include "CBombComponent.hpp"
#include "CExplosionComponent.hpp"
#include "CHealthComponent.hpp"

#include "CTransform.hpp"
#include "CBoundingBox.hpp"

using MyECS = CEntityComponentSystem<	10000,
										CPhysicsComponent,
										CPlayerComponent,
										CDebugNameComponent,
										CTransform,
										CBoundingBox,
										CBombComponent,
										CExplosionComponent,
										CHealthComponent,
										CMovementComponent >;