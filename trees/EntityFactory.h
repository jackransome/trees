#pragma once
#include "ColliderComponentManager.h"
#include "TransformComponentManager.h"
#include "RenderComponentManager.h"
#include "EntityManager.h"
#include "ControlSystem.h"

class EntityFactory {
public:
	EntityFactory( ColliderComponentManager& c, TransformComponentManager& t, RenderComponentManager& r, EntityManager& entityManager, ControlSystem& controlSystem);
	void addPlayer(glm::vec3 p);
	void addCylinder(glm::vec3 p1, glm::vec3 p2, float radius);
	void addSphere(glm::vec3 p, float radius);
private:
	ColliderComponentManager& colliderComponentManager;
	TransformComponentManager& transformComponentManager;
	RenderComponentManager& renderComponentManager;
	EntityManager& entityManager;
	ControlSystem& controlSystem;
};