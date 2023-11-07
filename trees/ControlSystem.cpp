#include "ControlSystem.h"

ControlSystem::ControlSystem() {

}

void ControlSystem::init(ColliderComponentManager* c, Input* i) {
	colliderComponentManager = c;
	input = i;
}

void ControlSystem::run(){
	if (controlledEntity != -1) {
		//do something to controlledEntity based on input

	}
}

void ControlSystem::setControlled(int entity){
	controlledEntity = entity;
}

void ControlSystem::changeCameraAngle(CameraSystem& cameraSystem){
	cameraSystem.moveWithMouse(input);
}

