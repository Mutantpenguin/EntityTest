#pragma once

#include "ecs/ECS.hpp"

#include "components/Physics.hpp"
#include "components/Player.hpp"
#include "components/DebugName.hpp"

#include "components/Movement.hpp"

#include "components/Bomb.hpp"
#include "components/Explosion.hpp"
#include "components/Health.hpp"

#include "components/BoundingBox.hpp"

#include "components/Transform.hpp"

#include "CBombSystem.hpp"
#include "CHealthSystem.hpp"
#include "CMovementSystem.hpp"
#include "CBVHSystem.hpp"

using TestECS = ecs::ECS<	100000,
							Physics,
							Player,
							DebugName,
							Transform,
							Bomb,
							BoundingBox,
							Explosion,
							Health,
							Movement >;

using TestBombSystem = CBombSystem< TestECS >;
using TestHealthSystem = CHealthSystem< TestECS >;
using TestMovementSystem = CMovementSystem< TestECS >;
using TestBVHSystem = CBVHSystem< TestECS >;