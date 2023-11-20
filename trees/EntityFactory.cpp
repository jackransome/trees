#include "EntityFactory.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

EntityFactory::EntityFactory(
	ColliderComponentManager& c,
	TransformComponentManager& t,
	RenderComponentManager& r,
	EntityManager& e,
	ControlSystem& cs) :
	colliderComponentManager(c),
	transformComponentManager(t),
	renderComponentManager(r),
	entityManager(e),
	controlSystem(cs) {}

void EntityFactory::addPlayer(glm::vec3 p){
	int entity = entityManager.createEntity();
	colliderComponentManager.addHybrid(entity, p, 0.05);
	//set controls
	controlSystem.setControlled(entity);
}

void EntityFactory::addCylinder(glm::vec3 p1, glm::vec3 p2, float radius){
	int entity = entityManager.createEntity();
	colliderComponentManager.addCylinder(entity, p1, p2, radius);
	
	glm::vec3 initialDirection = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));  // Assuming initial direction is along x-axis
	glm::vec3 directionNormalized = glm::normalize(p2 - p1);
	glm::quat rotationQuat = glm::rotation(initialDirection, directionNormalized);
	glm::mat4 rotationMat = glm::mat4_cast(rotationQuat);
	glm::vec3 eulerAngles = glm::eulerAngles(rotationQuat);

	glm::vec3 rotation = glm::degrees(eulerAngles);
	transformComponentManager.add(entity, (p1 + p2) / 2.0f, rotation);
	renderComponentManager.add(entity, 0, glm::vec3(radius * 2, glm::distance(p1, p2), radius * 2));
}

void EntityFactory::addSphere(glm::vec3 p, float radius){
	int entity = entityManager.createEntity();
	colliderComponentManager.addSphere(entity, p, radius);
	transformComponentManager.add(entity, p, glm::vec3(0));
	renderComponentManager.add(entity, 1, glm::vec3(radius));
}
