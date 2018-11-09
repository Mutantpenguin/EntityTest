#pragma once

#include "CEntityComponentSystem.hpp"

#include "CPhysicsComponent.hpp"
#include "CPlayerComponent.hpp"
#include "CDebugNameComponent.hpp"

#include "CMovementComponent.hpp"

#include "CBombComponent.hpp"
#include "CExplosionComponent.hpp"
#include "CHealthComponent.hpp"

#include "CBoundingBoxComponent.hpp"

#include "CTransformComponent.hpp"

#include "CBombSystem.hpp"
#include "CHealthSystem.hpp"
#include "CMovementSystem.hpp"
#include "CBVHSystem.hpp"

using TestECS = CEntityComponentSystem<	100000,
										CPhysicsComponent,
										CPlayerComponent,
										CDebugNameComponent,
										CTransformComponent,
										CBombComponent,
										CBoundingBoxComponent,
										CExplosionComponent,
										CHealthComponent,
										CMovementComponent >;

using TestBombSystem = CBombSystem< TestECS >;
using TestHealthSystem = CHealthSystem< TestECS >;
using TestMovementSystem = CMovementSystem< TestECS >;
using TestBVHSystem = CBVHSystem< TestECS >;