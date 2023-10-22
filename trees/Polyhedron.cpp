#include "Globals.h"
#include <cstdlib>

Polyhedron::Polyhedron(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) : scale(scale), position(position), rotation(rotation)
{
	vkObjectIndex = -1;
}

glm::vec3* Polyhedron::getPositionPointer()
{
	return &position;
}

glm::vec3 Polyhedron::getPosition()
{
	return position;
}


void Polyhedron::updateVkObjectState()
{
	globals::gfx.setObjectState(vkObjectIndex, position, scale, rotation);
}