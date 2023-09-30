#pragma once
#include "glm/glm.hpp"

class Collision_detection {
public:
	static float getDistanceFromSeg(glm::vec3 point, glm::vec3 start, glm::vec3 end, float diameter);
	static glm::vec3 projectOnto(glm::vec3 A, glm::vec3 B);
	static float getAngle(glm::vec3 A, glm::vec3 B, glm::vec3 C);
};