#pragma once
#include "Input.h"
#include "ColliderComponentManager.h"
class ControlSystem {
public:
	ControlSystem();
	void init(ColliderComponentManager* c, Input* i);
	void run();
	void setControlled(int entity);
private:
	Input* input;
	ColliderComponentManager* colliderComponentManager;
	Collider* controlledCollider = NULL;;
};