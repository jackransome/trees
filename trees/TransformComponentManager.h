#pragma once
#include "glm/glm.hpp"
#include <memory>
#include <vector>
#include <unordered_map>

class TransformComponent {
public:
	TransformComponent(glm::vec3 p, glm::vec3 r, glm::vec3 f) { position = p; rotation = r; forward = f; }
	glm::vec3 getPosition() { return position; }
	glm::vec3 getRotation() { return rotation; }
	glm::vec3 getForward() { return forward; }
	void setPosition(glm::vec3 p);
	void setRotation(glm::vec3 r);
	void setForward(glm::vec3 f);
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 forward;
};

class TransformComponentManager {
public:
	TransformComponentManager();
	void add(int entity, glm::vec3 position, glm::vec3 rotation, glm::vec3 forward = glm::vec3(1));
	TransformComponent* get(int entity);
private:
	std::vector<std::unique_ptr<TransformComponent>> transformComponents;  // Dense array
	std::unordered_map<int, size_t> entityToIndex;  // Maps entity to its index in the dense array
};
