#include "Csegment.h"
#include "Globals.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


Csegment::Csegment(glm::vec3 _start, glm::vec3 _end, float _width) : Polyhedron(glm::vec3(0,0,0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0))
{
	width = _width;
	end = _end;
	
	start = _start;
	length = glm::distance(start, end);
	vkObjectIndex = globals::gfx.addObject(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0);
	position = (start + end) / 2.0f;

	glm::vec3 initialDirection = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));  // Assuming initial direction is along x-axis
	directionNormalized = glm::normalize(end - start);
	glm::quat rotationQuat = glm::rotation(initialDirection, directionNormalized);
	glm::mat4 rotationMat = glm::mat4_cast(rotationQuat);
	glm::vec3 eulerAngles = glm::eulerAngles(rotationQuat);

	rotation = glm::degrees(eulerAngles);

	scale.y = length;
	scale.x = width;
	scale.z = width;
	
	type = c_seg;

	updateVkObjectState();
}

void Csegment::perLoop() {
	//rotation.x = 
	//rotation.z += 1;// = glm::vec3(0, 0, 0);
	//position = glm::vec3(0, 0, 0);
	updateVkObjectState();
}

glm::vec2 Csegment::getPlaneDims() {
	return glm::vec2(3.14159265359 * width, length);
}

glm::vec3 Csegment::convertPlaneToRealCoords(glm::vec2 planeCoords) {

	// Find a vector perpendicular to the direction vector
	// Assuming that the direction vector is not parallel to the y-axis
	glm::vec3 perpVec = glm::normalize(glm::cross(directionNormalized, directionNormalized+glm::vec3(1,2,3)));

	// Compute the angle in radians from the x coordinate
	float angle = planeCoords.x / (width / 2.0f);  // Assumes x is arc length; for angle in degrees, convert to radians if necessary

	// Compute the coordinates of the point on the circumference
	glm::vec3 pointOnCircumference = start + (width / 2.0f) * (perpVec * glm::cos(angle) + glm::cross(directionNormalized, perpVec) * glm::sin(angle));

	return pointOnCircumference + planeCoords.y* directionNormalized;
}

glm::vec2 Csegment::convertRealCoordsToPlane(glm::vec3 realCoords)
{
	//find projected point on center line of cseg:
	
	// Calculate the vector from the start to the end of the segment
	glm::vec3 segVector = end - start;

	// Calculate the vector from the start to the point
	glm::vec3 startToPoint = realCoords - start;

	// Project startToPoint onto segVector
	float projectionLength = glm::dot(startToPoint, glm::normalize(segVector));

	// If the projection falls outside the segment, return max float
	if (projectionLength < 0 || projectionLength > glm::length(segVector)) {
		std::cout << "BUG";
	}

	// Find the projected point
	glm::vec3 projectedPoint = start + glm::normalize(segVector) * projectionLength;

	float yCoord = glm::length(projectedPoint - start);

	//finding the x coord

	glm::vec3 vecAB = glm::normalize(end - start);
	glm::vec3 vecAC = glm::normalize(convertPlaneToRealCoords(glm::vec2(0,0)) - start);
	glm::vec3 vecAD = glm::normalize(realCoords - start);

	glm::vec3 crossProduct = glm::cross(vecAC, vecAD);
	float dotProduct = glm::dot(vecAC, vecAD);

	float angle = glm::degrees(glm::acos(glm::clamp(dotProduct, -1.0f, 1.0f)));  // Clamp to handle potential floating-point errors

	// Determine the sign of the angle based on the direction of the cross product
	float angleSign = glm::dot(crossProduct, vecAB) >= 0.0f ? 1.0f : -1.0f;
	

	angle = (angle * angleSign)*(2* 3.14159265359) / 360;

	

	float xCoord = 3.14159265359 * width * (angle / (2 * 3.14159265359));
	return glm::vec2(xCoord, yCoord);
}

glm::vec3 Csegment::convertPlaneToNormal(float planeX){
	// Compute the angle in radians from the x coordinate
	glm::vec3 perpVec = glm::normalize(glm::cross(directionNormalized, directionNormalized + glm::vec3(1, 2, 3)));

	// Compute the angle in radians from the x coordinate
	float angle = (planeX / (3.14159265359 * width)) * 3.14159265359 * 2;  // Assumes x is arc length; for angle in degrees, convert to radians if necessary

	// Compute the coordinates of the point on the circumference
	glm::vec3 pointOnCircumference = start + (width / 2.0f) * (perpVec * glm::cos(angle) + glm::cross(directionNormalized, perpVec) * glm::sin(angle));

	// Compute the vector from the center of the circle to the point on the circumference
	glm::vec3 radialVec = glm::normalize(pointOnCircumference - start);

	// Compute the normal vector by taking the cross product of the radial vector and the direction vector
	glm::vec3 normal = glm::normalize(glm::cross(radialVec, directionNormalized));
	glm::vec3 temp = perpVec * glm::cos(angle) + glm::cross(directionNormalized, perpVec) * glm::sin(angle);
	//std::cout <<temp.x << "," << temp.y << "," << temp.z << "\n";
	//std::cout << glm::cos(angle) << " | " << glm::sin(angle) << "|" << glm::dot(perpVec, temp) <<  "\n";
	return perpVec * glm::cos(angle) + glm::cross(directionNormalized, perpVec) * glm::sin(angle);
}
 
glm::vec3 Csegment::convertPlaneToDirection(glm::vec2 planeCoords, glm::vec2 planeDirection)
{
	return glm::normalize(convertPlaneToRealCoords(planeCoords + planeDirection) - convertPlaneToRealCoords(planeCoords));
}

glm::vec3 Csegment::getDirectionNormalized() {
	return directionNormalized;
}

glm::vec3 Csegment::getStart()
{
	return start;
}

glm::vec3 Csegment::getEnd()
{
	return end;
}

glm::vec3 Csegment::getNewCameraAngle(glm::vec3 from, glm::vec3 to, float planeX){

	//finding the x angle first
	glm::vec3 AD = to - from;
	glm::vec3 AC = convertPlaneToNormal(planeX);
	glm::vec3 AB = end - start;
	glm::vec3 E = glm::cross(AB, AC);
	glm::vec3 F = AD - Collision_detection::projectOnto(AD, E);
	float alpha = Collision_detection::getAngle(AB, glm::vec3(0, 0, 0), F);
	//std::cout << AB.x << "," << AB.y << "," << AB.z << "|" << F.x << "," << F.y << "," << F.z << "\n";
	//std::cout << alpha << "|" << 3.141592 / 4 << "\n";
	//std::cout << Collision_detection::getAngle(glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	//now finding the y angle
	glm::vec3 G = AD - Collision_detection::projectOnto(AD, AC);
	float beta = Collision_detection::getAngle(AB, glm::vec3(0, 0, 0), G);
	std::cout << beta << "|" << alpha << "\n";
	return glm::vec3(beta, alpha, 0);
}

float Csegment::getDiameter()
{
	return width;
}

