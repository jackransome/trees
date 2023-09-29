#include "Entity1.h"
#include <glm/gtx/quaternion.hpp>

Entity1::Entity1(Csegment* startingSegment) : Polyhedron(glm::vec3(0,0,0), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0, 0, 0)) {
	vkObjectIndex = globals::gfx.addObject(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 1);
	planePos = glm::vec2(0, 0);
	segmentBounds = startingSegment->getPlaneDims();
	position = startingSegment->convertPlaneToRealCoords(planePos);
	segment = startingSegment;
	planeDirection = glm::vec2(1, 0);
}

void Entity1::perLoop(){
	//planePos.y += 0.1;
	//planePos.x += 0.1;
	if (planePos.y > segmentBounds.y) {
		planePos.y = segmentBounds.y;
	} else if (planePos.y < 0) {
		planePos.y = 0;
	}
	if (planePos.x > segmentBounds.x) {
		planePos.x -= segmentBounds.x;
	}
	else if (planePos.x < 0) {
		planePos.x += segmentBounds.x;
	}
	if (globals::input.keys.keyCounts["w"] >= 1)
	{
		planePos += 0.02f*planeDirection;
	}
	if (globals::input.keys.keyCounts["a"] >= 1)
	{
		directionAngle += 0.05;
	}
	if (globals::input.keys.keyCounts["s"] >= 1)
	{
		planePos -= 0.02f * planeDirection;
	}
	if (globals::input.keys.keyCounts["d"] >= 1)
	{
		directionAngle -= 0.05;
	}
	planeDirection = glm::vec2(std::cos(directionAngle), std::sin(directionAngle));


	glm::vec3 initialDirection = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));  // Assuming initial direction is along x-axis
	glm::quat rotationQuat = glm::rotation(initialDirection, glm::normalize(segment->convertPlaneToNormal(planePos.x)));
	glm::mat4 rotationMat = glm::mat4_cast(rotationQuat);
	glm::vec3 eulerAngles = glm::eulerAngles(rotationQuat);

	//rotation = glm::degrees(eulerAngles);
	//position += segment->convertPlaneToNormal(planePos.x)
	position = segment->convertPlaneToRealCoords(planePos) += segment->convertPlaneToNormal(planePos.x)/3.0f;
	globals::gfx.setCameraPos(position);
	
	updateVkObjectState();
}
