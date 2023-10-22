#pragma once
#include "glm/glm.hpp"

class Collision_detection {
public:
	static float getDistanceFromSeg(const glm::vec3& point, const glm::vec3& start, const glm::vec3& end, const float& diameter);
	static glm::vec3 projectOnto(glm::vec3 A, glm::vec3 B);
	static float getAngle(glm::vec3 A, glm::vec3 B, glm::vec3 C);
	static glm::vec2 getRotationAngles(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C);
	static bool correctSpherePositionS(const glm::vec3& dynamicPosPrev, glm::vec3* dynamicPos, const float& rd, const glm::vec3& staticPos, const float& r);
	static bool correctSpherePositionC(const glm::vec3& dynamicPosPrev, glm::vec3* dynamicPos, const float& rd, const glm::vec3& staticPos, const glm::vec3& staticPos2, const float& rs);
	static bool correctSpherePositionCNoEnds(const glm::vec3& dynamicPosPrev, glm::vec3* dynamicPos, const float& rd, const glm::vec3& staticPos, const glm::vec3& staticPos2, const float& rs);
	static float pointToSegmentDistance(const glm::vec3& point, const glm::vec3& segStart, const glm::vec3& segEnd);
	static bool pointToLineDistance(const glm::vec3& point, const glm::vec3& segStart, const glm::vec3& segEnd, float& distance);
	static glm::vec3 pointToSegmentVector(const glm::vec3& point, const glm::vec3& segStart, const glm::vec3& segEnd);
	static float shortestDistanceBetweenSegments(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& q1, const glm::vec3& q2);
};