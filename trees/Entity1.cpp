#include "Entity1.h"
#include <glm/gtx/quaternion.hpp>

Entity1::Entity1(glm::vec3 _position) : Polyhedron(position, glm::vec3(0.04, 0.04, 0.04), glm::vec3(0, 0, 0)) {
	vkObjectIndex = globals::gfx.addObject(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 1);
	position = _position;
	type = entity;
	oldPosition = position;
}

void Entity1::perLoop(){
	oldPosition = position;

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

	//calculate new right axis


	rotationMatrix = glm::rotate(glm::mat4(1.0f), cameraAngleDelta.z, forward);
	up = glm::vec3(rotationMatrix * glm::vec4(up, 1.0f));

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
		speed = 0.05f;
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

	
	cameraFrom = position;
	cameraTo = position + forward;
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

glm::vec3 Entity1::getOldPosition()
{
	return oldPosition;
}

void Entity1::updateCamera()
{
	cameraFrom = position;
	cameraTo = position + forward;
	globals::gfx.setCameraManually(cameraFrom, cameraTo, up);
	if (globals::input.keys.keyCounts["z"] > 0) {
		std::cout << "update camera\n";
	}
	
}
