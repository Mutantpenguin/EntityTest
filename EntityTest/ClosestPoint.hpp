#pragma once

#include "CBoundingBox.hpp"
#include "CSphere.hpp"

glm::vec3 ClosestPoint( const CBoundingBox &box, const glm::vec3 &position );

glm::vec3 ClosestPoint( const CSphere &sphere, const glm::vec3 &position );
