#include "World_generator.h"
#include <cstdlib>  // For rand() and RAND_MAX

World_generator::World_generator() {
    using std::make_shared;
    nodes = 3;
    // Allocate memory for points array
    points = (glm::vec3*)malloc(nodes * sizeof(glm::vec3));
    // Allocate memory for adjacency matrix
    adjacencyMatrix = (float**)malloc(nodes * sizeof(float*));
    for (int i = 0; i < nodes; ++i) {
        adjacencyMatrix[i] = (float*)malloc(nodes * sizeof(float));
    }
    TreeNode root;
    root.pos = glm::vec3(0);
    growTree(&root, 5);
    root.radius = 0;

    addObjects(root);

    return;
    points[0] = glm::vec3(0, 0, 0);
    points[1] = glm::vec3(3, 0, 3);
    points[2] = glm::vec3(-2, 0, 4);

    adjacencyMatrix[0][0] = 0;
    adjacencyMatrix[0][1] = 1;
    adjacencyMatrix[0][2] = 0;
    adjacencyMatrix[1][0] = 0;
    adjacencyMatrix[1][1] = 0;
    adjacencyMatrix[1][2] = 2;
    adjacencyMatrix[2][0] = 0.5;
    adjacencyMatrix[2][1] = 0;
    adjacencyMatrix[2][2] = 0;

    float largest;
    for (int i = 0; i < nodes; i++) {
        largest = 0;
        for (int j = 0; j < nodes; j++) {
            if (adjacencyMatrix[i][j] > 0.1){
                if (adjacencyMatrix[i][j] > largest) {
                    largest = adjacencyMatrix[i][j];
                }
                float temp = adjacencyMatrix[i][j];
                glm::vec3 temp2 = points[i];
                globals::polyhedrons.push_back(make_shared<Csegment>(points[i], points[j], adjacencyMatrix[i][j]));
            }
        }
        if (largest > 0.1) {
            globals::polyhedrons.push_back(make_shared<Sphere>(points[i], largest/1.99));
        }
    }
    
    
}

void World_generator::growTree(TreeNode* node, int depth) {
    node->radius = ((float)rand() / (float)RAND_MAX) * 1.5 + 0.3;
    if (depth == 0)
    {
        return;
    }
    int branched = rand() % 3 + 1;
    for (int i = 0; i < branched; i++) {
        node->next.push_back(TreeNode());
        node->next.back().pos = node->pos + glm::vec3(((float)rand() / (float)RAND_MAX) * 5 + 2, ((float)rand() / (float)RAND_MAX) * 5 + 2, ((float)rand() / (float)RAND_MAX) * 5 + 2);
        growTree(&node->next.back(), depth - 1);
    }
}

void World_generator::addObjects(TreeNode node){
    using std::make_shared;
    float largest = node.radius;
    for (int i = 0; i < node.next.size(); i++) {
        if (node.next[i].radius > largest) {
            largest = node.next[i].radius;
        }
        globals::polyhedrons.push_back(make_shared<Csegment>(node.pos, node.next[i].pos, node.next[i].radius));
        addObjects(node.next[i]);
    }
    globals::polyhedrons.push_back(make_shared<Sphere>(node.pos, largest/1.99));
}
