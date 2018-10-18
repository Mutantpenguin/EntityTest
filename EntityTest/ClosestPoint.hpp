#pragma once

#include "CBoundingBox.hpp"
#include "CSphere.hpp"

glm::vec3 ClosestPoint( const glm::vec3 &boxPosition, const CBoundingBox &box, const glm::vec3 &point );

glm::vec3 ClosestPoint( const CSphere &sphere, const glm::vec3 &position );
