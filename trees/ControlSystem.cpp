#include "ControlSystem.h"

ControlSystem::ControlSystem() {

}

void ControlSystem::init(ColliderComponentManager* c, Input* i, CameraSystem* cs) {
	colliderComponentManager = c;
	input = i;
	cameraSystem = cs;
}

void ControlSystem::run(){
	
	if (controlledEntity != -1) {
		float speed = 0.05;
		Collider* collider = colliderComponentManager->get(controlledEntity);
		cameraSystem->setPosition(collider->getPosition());
		//do something to controlledEntity based on input
		if (input->keys.keyCounts["w"] > 0) {
			collider->setPosition(collider->getPosition() + cameraSystem->getforward() * speed);
		}
		if (input->keys.keyCounts["a"] > 0) {
			collider->setPosition(collider->getPosition() - cameraSystem->getRight() * speed);
		}
		if (input->keys.keyCounts["s"] > 0) {
			collider->setPosition(collider->getPosition() - cameraSystem->getforward() * speed);
		}
		if (input->keys.keyCounts["d"] > 0) {
			collider->setPosition(collider->getPosition() + cameraSystem->getRight() * speed);
		}
		if (input->keys.keyCounts["leftShift"] > 0) {
			collider->setPosition(collider->getPosition() - cameraSystem->getUp() * speed);
		}
		if (input->keys.keyCounts["space"] > 0) {
			collider->setPosition(collider->getPosition() + cameraSystem->getUp() * speed);
		}
	}
}

void ControlSystem::setControlled(int entity){
	controlledEntity = entity;
}

void ControlSystem::changeCameraAngle(){
	cameraSystem->moveWithMouse(input);
}

