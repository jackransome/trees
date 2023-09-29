#pragma once
#include "Graphics.h"
#include <glm/glm.hpp>
#include <vector>
#include <memory>


class Polyhedron
{
public:
	glm::vec3 position{ 0, 0, 0 };
	glm::vec3 scale{ 0, 0, 0 };
	glm::vec3 rotation{ 0, 0, 0 };


	explicit Polyhedron(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);

	virtual void perLoop() = 0;

	std::string name = "unchanged_string";

protected:

	int vkObjectIndex;

	void updateVkObjectState();
};