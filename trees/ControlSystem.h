#pragma once
#include "Input.h"
#include "ColliderComponentManager.h"
class ControlSystem {
public:
	ControlSystem(ColliderComponentManager& colliderComponentManager, Input& input);
	void run();
	void setControlled(int entity);
private:
	Input& input;
	ColliderComponentManager& colliderComponentManager;
	Collider* controlledCollider;
};