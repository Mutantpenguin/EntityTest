#pragma once

#include "CBoundingBox.hpp"
#include "CSphere.hpp"

bool Contains( const glm::vec3 &boxPosition, const CBoundingBox &box, const glm::vec3 &point );

bool Contains( const CSphere &sphere, const glm::vec3 &point );
