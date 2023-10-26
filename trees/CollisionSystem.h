#pragma once
#include "ColliderComponentManager.h"

class CollisionSystem {
public:
    CollisionSystem();
    void correctCollisions(const ColliderComponentManager& manager);
};