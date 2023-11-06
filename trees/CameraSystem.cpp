#include "CameraSystem.h"

CameraSystem::CameraSystem(Graphics& g) : gfx(g)
{
}

void CameraSystem::moveWithMouse(Input& input)
{
	glm::vec3 cameraAngleDelta = glm::vec3(0, 0, 0);

	// get camera angle delta from mouse input
	cameraAngleDelta.y = mouseSensitivity * float(input.windowHeight / 2 - input.mouseYpos);
	cameraAngleDelta.x = mouseSensitivity * float(input.windowWidth / 2 - input.mouseXpos);

	//calculate new right axis

	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), cameraAngleDelta.z, forward);
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

	from = position;
	to = position + forward;
}

void CameraSystem::setPosition(glm::vec3 pos)
{
	position = pos;
}

void CameraSystem::updateGfx()
{
	gfx.setCameraManually(from, to, up);
}
