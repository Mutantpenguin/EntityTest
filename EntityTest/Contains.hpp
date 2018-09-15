#pragma once

#include "CBoundingBox.hpp"
#include "CSphere.hpp"

bool Contains( const CBoundingBox &box, const glm::vec3 &position );

bool Contains( const CSphere &sphere, const glm::vec3 &position );
