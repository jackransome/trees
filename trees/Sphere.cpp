#include "Sphere.h"
#include "Globals.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>

Sphere::Sphere(glm::vec3 _position, float _radius) : Polyhedron(_position, glm::vec3(_radius * 2), glm::vec3(0, 0, 0))
{
	radius = _radius;
	vkObjectIndex = globals::gfx.addObject(glm::vec3(0, 0, 0), glm::vec3(_radius * 2), 1);

	glm::vec3 initialDirection = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));  // Assuming initial direction is along x-axis

	type = polyType_sphere;

	updateVkObjectState();
}

void Sphere::perLoop()
{
	updateVkObjectState();
}

float Sphere::getRadius() {
	return radius;
}
