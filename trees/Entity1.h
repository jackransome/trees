#pragma once
#include "Globals.h"
#include "Csegment.h"
class Entity1 : public Polyhedron {
public:
	explicit Entity1(Csegment* startingSegment);
	void perLoop() override;
private:
	glm::vec2 planePos;
	glm::vec2 segmentBounds;
	Csegment* segment;
	float directionAngle = 0;
	glm::vec2 planeDirection;
	glm::vec2 planeDirectionRight;
	glm::vec2 correctPlanePos(glm::vec2 _planePos);
};