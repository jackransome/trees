#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
}

void CollisionSystem::correctCollisions(const ColliderComponentManager& manager) {
    const auto& allColliders = manager.getAllColliders();
    for (size_t i = 0; i < allColliders.size(); ++i) {
        for (size_t j = i + 1; j < allColliders.size(); ++j) {
            Collider* colliderA = &*allColliders[i];
            Collider* colliderB = &*allColliders[j];

            

            //check and correct`
        }
    }
}