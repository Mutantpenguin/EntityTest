#pragma once

#include "ecs/CEntityComponentSystem.hpp"

#include "Physics.hpp"
#include "Player.hpp"
#include "DebugName.hpp"

#include "Movement.hpp"

#include "Bomb.hpp"
#include "Explosion.hpp"
#include "Health.hpp"

#include "BoundingBox.hpp"

#include "Transform.hpp"

#include "CBombSystem.hpp"
#include "CHealthSystem.hpp"
#include "CMovementSystem.hpp"
#include "CBVHSystem.hpp"

using TestECS = ecs::CEntityComponentSystem<	100000,
												cmpt::Physics,
												cmpt::Player,
												cmpt::DebugName,
												cmpt::Transform,
												cmpt::Bomb,
												cmpt::BoundingBox,
												cmpt::Explosion,
												cmpt::Health,
												cmpt::Movement >;

using TestBombSystem = CBombSystem< TestECS >;
using TestHealthSystem = CHealthSystem< TestECS >;
using TestMovementSystem = CMovementSystem< TestECS >;
using TestBVHSystem = CBVHSystem< TestECS >;