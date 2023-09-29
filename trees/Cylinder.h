#pragma once
#include "Polyhedron.h"
class Cylinder :
	public Polyhedron
{
public:
	explicit Cylinder(glm::vec3 position, glm::vec3 dimensions, glm::vec3 rotation);

	void perLoop() override;
};
