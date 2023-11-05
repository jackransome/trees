#include "RenderComponentManager.h"

RenderComponentManager::RenderComponentManager()
{
}

void RenderComponentManager::remove(int entity) {
    size_t indexToRemove = entityToIndex[entity];
    size_t lastIndex = renderComponents.size() - 1;

    // Swap component to remove with the last component
    std::swap(renderComponents[indexToRemove], renderComponents[lastIndex]);

    // Update the entityToIndex map for the swapped entity
    int swappedEntity = std::find_if(
        entityToIndex.begin(), entityToIndex.end(),
        [lastIndex](const auto& pair) { return pair.second == lastIndex; }
    )->first;
    entityToIndex[swappedEntity] = indexToRemove;

    // Remove the last component and the entity's entry from the map
    renderComponents.pop_back();
    entityToIndex.erase(entity);
}

void RenderComponentManager::add(int entity, int m){
    renderComponents.push_back(std::move(std::make_unique<RenderComponent>(entity, m)));
    entityToIndex[entity] = renderComponents.size() - 1;
}

RenderComponent* RenderComponentManager::get(int entity)
{
    return renderComponents[entityToIndex.at(entity)].get();
}
