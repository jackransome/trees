#pragma once
#include "Graphics.h"
#include <glm/glm.hpp>
#include <vector>
#include <memory>

enum polyType {entity, c_seg, polyType_sphere};

class Polyhedron
{
public:
	glm::vec3 position{ 0, 0, 0 };
	glm::vec3 scale{ 0, 0, 0 };
	glm::vec3 rotation{ 0, 0, 0 };

	polyType type;
	explicit Polyhedron(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);

	glm::vec3* getPositionPointer();
	glm::vec3 getPosition();

	virtual void perLoop() = 0;

	std::string name = "unchanged_string";
	void updateVkObjectState();
protected:

	int vkObjectIndex;

	
};