#include "World_generator.h"

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

    points[0] = glm::vec3(0, 0, 0);
    points[1] = glm::vec3(1, 5, 0);
    points[2] = glm::vec3(0, -1, 5);

    adjacencyMatrix[0][0] = 0;
    adjacencyMatrix[0][1] = 1;
    adjacencyMatrix[0][2] = 0;
    adjacencyMatrix[1][0] = 0;
    adjacencyMatrix[1][1] = 0;
    adjacencyMatrix[1][2] = 2;
    adjacencyMatrix[2][0] = 0.5;
    adjacencyMatrix[2][1] = 0;
    adjacencyMatrix[2][2] = 0;

    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            if (adjacencyMatrix[i][j] > 0.1){
                float temp = adjacencyMatrix[i][j];
                glm::vec3 temp2 = points[i];
                globals::polyhedrons.push_back(make_shared<Csegment>(points[i], points[j], adjacencyMatrix[i][j]));
            }
        }
    }
    
}