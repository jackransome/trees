#include "EntityManager.h"

EntityManager::EntityManager() {

}

int EntityManager::createEntity()
{
	entities.push_back(nextId);
	nextId++;
	return nextId - 1;
}

void EntityManager::deleteEntity(int _entity) {
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i] == _entity) {
			entities.erase(entities.begin() + i);
		}
	}
}