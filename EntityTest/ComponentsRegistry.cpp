#include "ecs/ComponentTraits.hpp"

#include "Bomb.hpp"
#include "BoundingBox.hpp"
#include "DebugName.hpp"
#include "Explosion.hpp"
#include "Health.hpp"
#include "Movement.hpp"
#include "Physics.hpp"
#include "Player.hpp"
#include "Transform.hpp"

REGISTER_COMPONENT( cmpt::Bomb )
REGISTER_COMPONENT( cmpt::BoundingBox )
REGISTER_COMPONENT( cmpt::DebugName )
REGISTER_COMPONENT( cmpt::Explosion )
REGISTER_COMPONENT( cmpt::Health )
REGISTER_COMPONENT( cmpt::Movement )
REGISTER_COMPONENT( cmpt::Physics )
REGISTER_COMPONENT( cmpt::Player )
REGISTER_COMPONENT( cmpt::Transform )