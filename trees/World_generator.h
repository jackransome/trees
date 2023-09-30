#pragma once
#include "Csegment.h"
#include "Globals.h"

class World_generator {
public:
	World_generator();

private:
	glm::vec3* points;
	float** adjacencyMatrix;
	int nodes;
};