#pragma once
#include "Polyhedron.h"

class Sphere :
	public Polyhedron
{
public:
	explicit Sphere(glm::vec3 position, float radius);

	void perLoop() override;
	float getRadius();
private:
	float radius;
};
