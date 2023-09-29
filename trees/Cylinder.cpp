#include "Cylinder.h"
#include "Globals.h"

Cylinder::Cylinder(glm::vec3 position, glm::vec3 dimensions, glm::vec3 rotation) : Polyhedron(position, dimensions, rotation)
{
	vkObjectIndex = globals::gfx.addObject(position, dimensions, 0);
}

void Cylinder::perLoop(){
	rotation.y += 1;
	scale.y += 0.1;
	updateVkObjectState();
}
