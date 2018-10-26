#pragma once

#include "CBoundingBox.hpp"
#include "CSphere.hpp"
#include "CFrustum.hpp"

bool Contains( const glm::vec3 &boxPosition, const CBoundingBox &box, const glm::vec3 &point );

bool Contains( const glm::vec3 &spherePosition, const CSphere &sphere, const glm::vec3 &point );

bool Contains( const CFrustum &frustum, const glm::vec3 &point );
