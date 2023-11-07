#pragma once
#include "Input.h"
#include "ColliderComponentManager.h"
#include "CameraSystem.h"
class ControlSystem {
public:
	ControlSystem();
	void init(ColliderComponentManager* c, Input* i);
	void run();
	void setControlled(int entity);
	void changeCameraAngle(CameraSystem& cameraSystem);
private:
	Input* input;
	
	ColliderComponentManager* colliderComponentManager;
	int controlledEntity = -1;;
};