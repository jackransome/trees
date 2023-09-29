#pragma once
#include "Polyhedron.h"

class Csegment :
	public Polyhedron
{
public:
	explicit Csegment(glm::vec3 start, glm::vec3 end, float width);

	void perLoop() override;
	glm::vec2 getPlaneDims();
	glm::vec3 convertPlaneToRealCoords(glm::vec2 planeCoords);
	glm::vec3 convertPlaneToNormal(float planeX);
	glm::vec3 convertPlaneToDirection(glm::vec2 planeCoords, glm::vec2 planeDirection);
private:
	glm::vec3 start;
	glm::vec3 end;
	glm::vec3 directionNormalized;
	float width;
	float length;
};
