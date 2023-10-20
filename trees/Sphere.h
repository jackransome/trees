#pragma once
#include "Polyhedron.h"

class Sphere :
	public Polyhedron
{
public:
	explicit Sphere(glm::vec3 _position, float _radius);

	void perLoop() override;
	float getRadius();
private:
	float radius;
};
