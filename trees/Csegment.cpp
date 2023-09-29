#include "Csegment.h"
#include "Globals.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


Csegment::Csegment(glm::vec3 _start, glm::vec3 _end, float _width) : Polyhedron(glm::vec3(0,0,0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0))
{
	width = _width;
	end = _end;
	length = glm::distance(start, end);
	start = _start;
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
	glm::vec3 perpVec = glm::normalize(glm::cross(directionNormalized, glm::vec3(0.0f, 1.0f, 0.0f)));

	// Compute the angle in radians from the x coordinate
	float angle = planeCoords.x / (width / 2.0f);  // Assumes x is arc length; for angle in degrees, convert to radians if necessary

	// Compute the coordinates of the point on the circumference
	glm::vec3 pointOnCircumference = start + (width / 2.0f) * (perpVec * glm::cos(angle) + glm::cross(directionNormalized, perpVec) * glm::sin(angle));

	return pointOnCircumference + planeCoords.y* directionNormalized;
}

glm::vec3 Csegment::convertPlaneToNormal(float planeX){
	// Compute the angle in radians from the x coordinate
	float angle = planeX / (width / 2.0f);  // Assumes x is arc length; for angle in degrees, convert to radians if necessary

	// Find a vector perpendicular to the direction vector
	// Assuming that the direction vector is not parallel to the y-axis
	glm::vec3 direction = glm::normalize(end - start);
	glm::vec3 perpVec = glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));

	// Compute the coordinates of the point on the circumference
	glm::vec3 pointOnCircumference = start + (width / 2.0f) * (perpVec * glm::cos(angle) + glm::cross(direction, perpVec) * glm::sin(angle));

	// Compute the vector from the center of the circle to the point on the circumference
	glm::vec3 radialVec = glm::normalize(pointOnCircumference - start);

	// Compute the normal vector by taking the cross product of the radial vector and the direction vector
	glm::vec3 normal = glm::normalize(glm::cross(radialVec, direction));

	return normal;
	return glm::vec3();
}

glm::vec3 Csegment::convertPlaneToDirection(glm::vec2 planeCoords, glm::vec2 planeDirection)
{
	return glm::normalize(convertPlaneToRealCoords(planeCoords + planeDirection) - convertPlaneToRealCoords(planeCoords));
}
