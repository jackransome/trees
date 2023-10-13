#pragma once
#include "glm/glm.hpp"

class Collision_detection {
public:
	static float getDistanceFromSeg(glm::vec3 point, glm::vec3 start, glm::vec3 end, float diameter);
	static glm::vec3 projectOnto(glm::vec3 A, glm::vec3 B);
	static float getAngle(glm::vec3 A, glm::vec3 B, glm::vec3 C);
	static glm::vec2 getRotationAngles(glm::vec3 A, glm::vec3 B, glm::vec3 C);
	static bool correctSpherePositionS(glm::vec3 dynamicPosPrev, glm::vec3* dynamicPos, float rd, glm::vec3 staticPos, float rs);
	static bool correctSpherePositionC(glm::vec3 dynamicPosPrev, glm::vec3* dynamicPos, float rd, glm::vec3 staticPos, glm::vec3 staticPos2, float rs);
	static float pointToSegmentDistance(const glm::vec3& point, const glm::vec3& segStart, const glm::vec3& segEnd);
	static float shortestDistanceBetweenSegments(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& q1, const glm::vec3& q2);
};