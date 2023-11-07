#pragma once
#include "glm/glm.hpp"
#include <vector>

struct TreeNode {
	glm::vec3 pos;
	std::vector<TreeNode> next;
	float radius;
};

class World_generator {
public:
	World_generator();

private:
	void growTree(TreeNode* node, int depth);
	void addObjects(TreeNode node);
	glm::vec3* points;
	float** adjacencyMatrix;
	int nodes;
};