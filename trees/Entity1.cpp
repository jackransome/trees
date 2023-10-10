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
	/*directionAngle = globals::input.cameraAngle.x + 3.14159265359 / 2;
	planeDirection = glm::vec2(std::cos(directionAngle), std::sin(directionAngle));
	planeDirectionRight = glm::vec2(std::cos(directionAngle + 3.14159265359 / 2), std::sin(directionAngle + 3.14159265359 / 2));

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
		planePos.y = segmentBounds.y -0.001;
	}
	else if (planePos.y < 0) {
		planePos.y = 0.001;
	}
	if (planePos.x > segmentBounds.x) {
		planePos.x -= segmentBounds.x;
	}
	else if (planePos.x < 0) {
		planePos.x += segmentBounds.x;
	}


	rotation.x += 30;
	rotation.y += 60;
	rotation.z += 90;*/

	

	//camera

	// reset camera delta

	cameraAngleDelta = glm::vec3(0, 0, 0);

	// get camera angle delta from mouse input
	cameraAngleDelta.y = cameraSensitivity * float(globals::input.windowHeight / 2 - globals::input.mouseYpos);
	cameraAngleDelta.x = cameraSensitivity * float(globals::input.windowWidth / 2 - globals::input.mouseXpos);
	/*if (globals::input.keys.keyCounts["leftAlt"] >= 1)
	{
		cameraAngleDelta.z = cameraSensitivity * float(globals::input.windowWidth / 2 - globals::input.mouseXpos);
	}
	else {
		cameraAngleDelta.x = cameraSensitivity * float(globals::input.windowWidth / 2 - globals::input.mouseXpos);
	}*/

	if (globals::input.keys.keyCounts["q"] >= 1)
	{
		cameraAngleDelta.z -= 0.05;
	}
	if (globals::input.keys.keyCounts["e"] >= 1)
	{
		cameraAngleDelta.z += 0.05;
	}

	//first rotate the up vector by the camera delta z around the old forward

	rotationMatrix = glm::rotate(glm::mat4(1.0f), cameraAngleDelta.z, forward);
	up  = glm::vec3(rotationMatrix * glm::vec4(up, 1.0f));

	//calculate new right axis
	right = glm::normalize(glm::cross(forward, up));

	//now rotate the forward vector by the y delta around the "right" axis
	rotationMatrix = glm::rotate(glm::mat4(1.0f), cameraAngleDelta.y, right);
	forward = glm::vec3(rotationMatrix * glm::vec4(forward, 1.0f));

	//now rotate the forward vector by the x delta around the "up" axis
	rotationMatrix = glm::rotate(glm::mat4(1.0f), cameraAngleDelta.x, up);
	forward = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(forward, 1.0f)));
	
	//now rotate the up vector by the y delta around the "right" axis
	rotationMatrix = glm::rotate(glm::mat4(1.0f), cameraAngleDelta.y, right);
	up = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(up, 1.0f)));

	//controls
	speed = 0.01f;
	if (globals::input.keys.keyCounts["leftCtrl"] >= 1)
	{
		speed = 0.02f;
	}
	if (globals::input.keys.keyCounts["w"] >= 1)
	{
		position += speed * forward;
	}
	if (globals::input.keys.keyCounts["a"] >= 1)
	{
		position -= speed * right;
	}
	if (globals::input.keys.keyCounts["s"] >= 1)
	{
		position -= speed * forward;
	}
	if (globals::input.keys.keyCounts["d"] >= 1)
	{
		position += speed * right;
	}
	if (globals::input.keys.keyCounts["space"] >= 1)
	{
		position += speed * up;
	}
	if (globals::input.keys.keyCounts["leftShift"] >= 1)
	{
		position -= speed * up;
	}

	
	cameraFrom = position + up * 0.2f;
	cameraTo = position + up * 0.2f + forward;
	globals::gfx.setCameraManually(cameraFrom, cameraTo, up);
	/*if (!switched) {
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
	}*/
	
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
	//globals::input.cameraAngle = segment->getNewCameraAngle(cameraTo - cameraFrom, cameraUp, planePos.x);
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
