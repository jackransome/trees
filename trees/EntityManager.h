#pragma once
#include <vector>

class EntityManager {
public:
	EntityManager();
	int createEntity();
	void deleteEntity(int entity);
private:
	int nextId = 0;
	std::vector<int> entities;
};