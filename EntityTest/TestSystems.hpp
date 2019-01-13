#pragma once

#include "CBombSystem.hpp"
#include "CHealthSystem.hpp"
#include "CMovementSystem.hpp"
#include "CBVHSystem.hpp"

#include "TestECS.hpp"

using TestBombSystem = CBombSystem< TestECS >;
using TestHealthSystem = CHealthSystem< TestECS >;
using TestMovementSystem = CMovementSystem< TestECS >;
using TestBVHSystem = CBVHSystem< TestECS >;