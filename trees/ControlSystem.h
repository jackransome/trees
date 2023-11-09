#pragma once
#include "Input.h"
#include "ColliderComponentManager.h"
#include "CameraSystem.h"
class ControlSystem {
public:
	ControlSystem();
	void init(ColliderComponentManager* c, Input* i, CameraSystem* cs);
	void run();
	void setControlled(int entity);
	void changeCameraAngle();
private:
	CameraSystem* cameraSystem;
	Input* input;
	ColliderComponentManager* colliderComponentManager;
	int controlledEntity = -1;;
};