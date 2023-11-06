#pragma once
#include "Graphics.h"
#include "Input.h"
class CameraSystem {
public:
	CameraSystem(Graphics& gfx);
	void moveWithMouse(Input& input);
	void setPosition(glm::vec3 pos);
	void updateGfx();
private:
	Graphics& gfx;
	glm::vec3 from;
	glm::vec3 to;
	glm::vec3 up = glm::vec3(0, 1, 0);;
	glm::vec3 forward = glm::vec3(0, 0, 1);
	glm::vec3 right = glm::vec3(1, 0, 0);
	glm::vec3 position;
	float mouseSensitivity;
};