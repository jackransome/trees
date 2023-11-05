#include "TransformComponentManager.h"

TransformComponentManager::TransformComponentManager()
{
}

void TransformComponentManager::add(int entity, glm::vec3 position, glm::vec3 rotation)
{
	transformComponents.push_back(std::move(std::make_unique<TransformComponent>(position, rotation)));
	entityToIndex[entity] = transformComponents.size() - 1;
}

TransformComponent* TransformComponentManager::get(int entity)
{
	return transformComponents[entityToIndex.at(entity)].get();
}

