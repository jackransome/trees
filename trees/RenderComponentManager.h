#pragma once

#include <variant>
#include "glm/glm.hpp"
#include <memory>
#include <vector>
#include <unordered_map>


class RenderComponent {
public:
    RenderComponent(int o, glm::vec3 p, glm::vec3 s, glm::vec3 r) : objectIndex(o), position(p), scale(s), rotation(r) {}
    int objectIndex;
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
    void draw () {}
};

class RenderComponentManager {
public:
    RenderComponentManager();
    void remove(int entity);
    void drawAll();
    void add(int entity, int o, glm::vec3 p, glm::vec3 s, glm::vec3 r)
private:
    std::vector<std::unique_ptr<RenderComponent>> renderComponents;  // Dense array
    std::unordered_map<int, size_t> entityToIndex;  // Maps entity to its index in the dense array
};