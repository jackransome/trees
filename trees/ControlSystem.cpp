#include "ControlSystem.h"

ControlSystem::ControlSystem(ColliderComponentManager& c, Input& i) : colliderComponentManager(c), input(i)
{

}

void ControlSystem::run(){
	//do something to controlledCollider based on input
}

void ControlSystem::setControlled(int entity){
	controlledCollider = colliderComponentManager.get(entity);
}

