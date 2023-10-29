#include "ControlSystem.h"

ControlSystem::ControlSystem()
{

}

void ControlSystem::init(ColliderComponentManager* c, Input* i)
{
	colliderComponentManager = c;
	input = i;
}

void ControlSystem::run(){
	if (controlledCollider != NULL) {
		//do something to controlledCollider based on input
	}
	
}

void ControlSystem::setControlled(int entity){
	controlledCollider = colliderComponentManager->get(entity);
}

