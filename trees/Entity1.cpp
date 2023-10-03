#include "Entity1.h"
#include <glm/gtx/quaternion.hpp>

Entity1::Entity1(Csegment* startingSegment) : Polyhedron(glm::vec3(0,0,0), glm::vec3(0.04, 0.04, 0.04), glm::vec3(0, 0, 0)) {
	vkObjectIndex = globals::gfx.addObject(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 1);
	planePos = glm::vec2(0, 0);
	segmentBounds = startingSegment->getPlaneDims();
	position = startingSegment->convertPlaneToRealCoords(planePos);
	segment = startingSegment;
	planeDirection = glm::vec2(1, 0);
	planeDirectionRight = glm::vec2(0, 1);
	type = entity;
}

void Entity1::perLoop(){
	//planePos.y += 0.1;
	//planePos.x += 0.1;


	
	//setting direction according to mouse
	directionAngle = globals::input.cameraAngle.x + 3.14159265359 / 2;
	planeDirection = glm::vec2(std::cos(directionAngle), std::sin(directionAngle));
	planeDirectionRight = glm::vec2(std::cos(directionAngle + 3.14159265359 / 2), std::sin(directionAngle + 3.14159265359 / 2));
	//controls
	speed = 0.01f;
	if (globals::input.keys.keyCounts["leftShift"] >= 1)
	{
		speed = 0.02f;
	}
	if (globals::input.keys.keyCounts["w"] >= 1)
	{
		planePos += speed *planeDirection;
	}
	if (globals::input.keys.keyCounts["a"] >= 1)
	{
		planePos += speed * planeDirectionRight;
	}
	if (globals::input.keys.keyCounts["s"] >= 1)
	{
		planePos -= speed * planeDirection;
	}
	if (globals::input.keys.keyCounts["d"] >= 1)
	{
		planePos -= speed * planeDirectionRight;
	}
	if (globals::input.keys.keyCounts["space"] == 1 && onGround)
	{
		hVel = 0.015;
	}
	height += hVel;
	hVel -= 0.0005;
	if (height <= 0) {
		height = 0;
		onGround = true;
	}
	else {
		onGround = false;
	}
	if (planePos.y > segmentBounds.y) {
		planePos.y = segmentBounds.y;
	}
	else if (planePos.y < 0) {
		planePos.y = 0;
	}
	if (planePos.x > segmentBounds.x) {
		planePos.x -= segmentBounds.x;
	}
	else if (planePos.x < 0) {
		planePos.x += segmentBounds.x;
	}


	rotation.x += 30;
	rotation.y += 60;
	rotation.z += 90;

	

	//camera

	glm::vec3 forward = segment->getDirectionNormalized();
	glm::vec3 up = segment->convertPlaneToNormal(planePos.x);
	glm::vec3 right = glm::normalize(glm::cross(forward, up));
	glm::vec3 cameraAngle = globals::input.cameraAngle;
	glm::vec3 newUp = up;

	// ------ rotating the forward vector

	// rotating forward with y rotation
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), cameraAngle.y, right);
	glm::vec3 yRotatedForward = glm::vec3(rotationMatrix * glm::vec4(forward, 1.0f));

	// rotating y rotated forward with x rotation
	rotationMatrix = glm::rotate(glm::mat4(1.0f), cameraAngle.x, up);
	glm::vec3 xRotatedForward = glm::vec3(rotationMatrix * glm::vec4(yRotatedForward, 1.0f));

	// ------ rotating the up vector

	// Create a rotation matrix using the axis and the angle
	rotationMatrix = glm::rotate(glm::mat4(1.0f), cameraAngle.y, right);

	// Multiply the vector by the rotation matrix
	glm::vec3 rotatedVec4 = rotationMatrix * glm::vec4(newUp, 1.0f);

	// Convert the result back to a vec3 and return it
	newUp = glm::vec3(rotatedVec4);

	// Create a rotation matrix using the axis and the angle
	rotationMatrix = glm::rotate(glm::mat4(1.0f), cameraAngle.x, up);

	// Multiply the vector by the rotation matrix
	rotatedVec4 = rotationMatrix * glm::vec4(newUp, 1.0f);

	// Convert the result back to a vec3 and return it
	newUp = glm::vec3(rotatedVec4);

	position = segment->convertPlaneToRealCoords(planePos) + up*height;
	cameraFrom = position + up * 0.2f;
	cameraTo = position + up * 0.2f + xRotatedForward;
	cameraUp = newUp;
	if (!switched) {
		globals::gfx.setCameraManually(cameraFrom, cameraTo, cameraUp);
	}
	else {
		glm::vec3 difference = cameraFrom - oldCameraFrom;
		//oldCameraFrom += difference*std::max(switchCounter*2, 1.0f);
		//oldCameraTo += difference * std::max(switchCounter * 2, 1.0f);
		globals::gfx.setCameraManually(cameraFrom*switchCounter + oldCameraFrom*(1.0f-switchCounter), cameraTo * switchCounter + oldCameraTo * (1.0f - switchCounter), cameraUp * switchCounter + oldCameraUp * (1.0f - switchCounter));
		switchCounter += 0.04;
		if (switchCounter >= 1) {
			switched = false;
			switchCounter = 0;
		}
	}
	
	//std::cout << globals::input.cameraAngle.x << " | " << globals::input.cameraAngle.y << "\n";
	updateVkObjectState();
}

void Entity1::changeSegment(Csegment* _segment){
	oldCameraFrom = cameraFrom;
	oldCameraTo = cameraTo;
	oldCameraUp = cameraUp;
	switched = true;
	segment = _segment;
	segmentBounds = segment->getPlaneDims();
	globals::input.cameraAngle = segment->getNewCameraAngle(cameraTo - cameraFrom, cameraUp, planePos.x);
}

Csegment* Entity1::getSegment()
{
	return segment;
}

void Entity1::setHeight(float _height){
	height = _height;
	hVel = 0;
}

void Entity1::setPlanePos(glm::vec2 _planePos){
	planePos = _planePos;
}

glm::vec2 Entity1::correctPlanePos(glm::vec2 _planePos)
{
	if (_planePos.y > segmentBounds.y) {
		_planePos.y = segmentBounds.y;
	}
	else if (_planePos.y < 0) {
		_planePos.y = 0;
	}
	if (_planePos.x > segmentBounds.x) {
		_planePos.x -= segmentBounds.x;
	}
	return _planePos;
}
