#include "ColliderComponentManager.h"

ColliderComponentManager::ColliderComponentManager(){

}

void ColliderComponentManager::addCylinder(int entity, glm::vec3 position1, glm::vec3 position2, float radius){
    std::unique_ptr<Collider> cylinder = std::make_unique<CylinderCollider>(position1, position2, radius);
    add(entity, std::move(cylinder));
}

void ColliderComponentManager::addSphere(int entity, glm::vec3 position, float radius){
    std::unique_ptr<Collider> sphere = std::make_unique<SphereCollider>(position, radius);
    add(entity, std::move(sphere));
}

void ColliderComponentManager::addBox(int entity, glm::vec3 position, glm::vec3 dimensions){
    std::unique_ptr<Collider> box = std::make_unique<BoxCollider>(position, dimensions);
    add(entity, std::move(box));
}

void ColliderComponentManager::add(int entity, std::unique_ptr<Collider> collider) {
    colliders.push_back(std::move(collider));
    entityToIndex[entity] = colliders.size() - 1;
}

void ColliderComponentManager::remove(int entity) {
    size_t indexToRemove = entityToIndex[entity];
    size_t lastIndex = colliders.size() - 1;

    // Swap component to remove with the last component
    std::swap(colliders[indexToRemove], colliders[lastIndex]);

    // Update the entityToIndex map for the swapped entity
    int swappedEntity = std::find_if(
        entityToIndex.begin(), entityToIndex.end(),
        [lastIndex](const auto& pair) { return pair.second == lastIndex; }
    )->first;
    entityToIndex[swappedEntity] = indexToRemove;

    // Remove the last component and the entity's entry from the map
    colliders.pop_back();
    entityToIndex.erase(entity);
}

Collider* ColliderComponentManager::get(int entity) {
    return colliders[entityToIndex.at(entity)].get();
}