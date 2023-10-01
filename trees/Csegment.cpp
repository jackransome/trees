#include "Csegment.h"
#include "Globals.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>

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
	float projectionLength = glm::dot(startToPoint, directionNormalized);

	// If the projection falls outside the segment, return max float
	if (projectionLength < 0 || projectionLength > glm::length(segVector)) {
		std::cout << "BUG";
	}

	// Find the projected point
	glm::vec3 projectedPoint = start + glm::normalize(segVector) * projectionLength;

	float yCoord = glm::length(projectedPoint - start);

	//finding the x coord

	glm::vec3 A = directionNormalized;
	glm::vec3 B = glm::normalize(convertPlaneToNormal(0));
	glm::vec3 C = realCoords - start;

	glm::vec3 projection = C - Collision_detection::projectOnto(C, A);
	float angle = Collision_detection::getAngle(projection, glm::vec3(0, 0, 0), B);
	glm::vec3 cross = glm::cross(A, B);
	if (glm::dot(cross, projection) < 0) {
		angle *= -1;
	}
	
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

glm::vec3 Csegment::getNewCameraAngle(glm::vec3 direction, glm::vec3 up, float planeX){
	//== do checks on the up's and correct
	//get normal and startend

	// directionNormalized
	glm::vec3 normal = convertPlaneToNormal(planeX);

	//get cross startend normal

	glm::vec3 cross = glm::cross(normal, directionNormalized);

	//project up onto the startend normal plane

	glm::vec3 upProjection = up - Collision_detection::projectOnto(up, cross);

	//get angle between startend and up with the rotational axis being cross startend and normal
	float angle = glm::orientedAngle(directionNormalized, upProjection, cross);
	//std::cout << "angle: " << angle << "\n";
	if (angle > 0) { //too down
		//rotate up by angle + 0.1
		cross = glm::cross(direction, up);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle + 0.1f, cross);
		direction = glm::vec3(rotationMatrix * glm::vec4(direction, 1.0f));

	}
	else if (angle < -3.1415) {
		//rotate down by -angle + 3.1415 + 0.1
		cross = glm::cross(direction, up);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -float( - angle + 3.1415 + 0.1f), cross);
		direction = glm::vec3(rotationMatrix * glm::vec4(direction, 1.0f));
	}

	//get result with correct vectors
	glm::vec3 result = glm::vec3(Collision_detection::getRotationAngles(end - start, convertPlaneToNormal(planeX), direction), 0);
	if (result.y < -3.14f / 2.0f) {
		result.x += 3.1415;
		result.y = -(3.1415 + result.y);
		//std::cout << "<<<\n\n";
	}
	if (result.y > 3.14f / 2.0f) {
		result.x += 3.1415;
		result.y = 3.1415 - result.y;
		//std::cout << ">>>\n\n";
	}
	return result;
}

float Csegment::getDiameter()
{
	return width;
}

