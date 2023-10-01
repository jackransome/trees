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
	glm::vec2 convertRealCoordsToPlane(glm::vec3 realCoords);
	glm::vec3 convertPlaneToNormal(float planeX);
	glm::vec3 convertPlaneToDirection(glm::vec2 planeCoords, glm::vec2 planeDirection);
	glm::vec3 getDirectionNormalized();
	glm::vec3 getStart();
	glm::vec3 getEnd();
	glm::vec3 getNewCameraAngle(glm::vec3 direction, glm::vec3 up, float planeX);
	float getDiameter();
private:
	glm::vec3 start;
	glm::vec3 end;
	glm::vec3 directionNormalized;
	float width;
	float length;
};
