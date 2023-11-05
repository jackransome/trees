#pragma once
#include "glm/glm.hpp"
#include <memory>
#include <vector>
#include <unordered_map>

class TransformComponent {
public:
	TransformComponent(glm::vec3 p, glm::vec3 r) { position = p; rotation = r; }
	glm::vec3 getPosition() { return position; }
	glm::vec3 getRotation() { return rotation; }
private:
	glm::vec3 position;
	glm::vec3 rotation;
};

class TransformComponentManager {
public:
	TransformComponentManager();
	void add(int entity, glm::vec3 position, glm::vec3 rotation);
	TransformComponent* get(int entity);
private:
	std::vector<std::unique_ptr<TransformComponent>> transformComponents;  // Dense array
	std::unordered_map<int, size_t> entityToIndex;  // Maps entity to its index in the dense array
};
