#include "TransformComponentManager.h"

TransformComponentManager::TransformComponentManager()
{
}

void TransformComponentManager::add(int entity, glm::vec3 position, glm::vec3 rotation, glm::vec3 forward)
{
	transformComponents.push_back(std::move(std::make_unique<TransformComponent>(position, rotation, forward)));
	entityToIndex[entity] = transformComponents.size() - 1;
}

TransformComponent* TransformComponentManager::get(int entity)
{
	return transformComponents[entityToIndex.at(entity)].get();
}

void TransformComponent::setPosition(glm::vec3 p){
	position = p;
}

void TransformComponent::setRotation(glm::vec3 r){
	rotation = r;
}

void TransformComponent::setForward(glm::vec3 f){
	forward = f;
}
