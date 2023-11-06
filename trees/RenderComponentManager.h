#pragma once

#include <variant>
#include "glm/glm.hpp"
#include <memory>
#include <vector>
#include <unordered_map>


class RenderComponent {
public:
    RenderComponent(int e, int m, glm::vec3 s) : entity(e), meshIndex(m), scale(s) {}
    int getEntity() { return entity; }
    int getMeshIndex() { return meshIndex; }
    glm::vec3 getScale() { return scale; }
private:
    int entity;
    int meshIndex;
    glm::vec3 scale;
};

class RenderComponentManager {
public:
    RenderComponentManager();
    void remove(int entity);
    void add(int entity, int m, glm::vec3 s);
    RenderComponent* get(int entity);
    const std::vector<std::unique_ptr<RenderComponent>>& getAll() const { return renderComponents; }
private:
    std::vector<std::unique_ptr<RenderComponent>> renderComponents;  // Dense array
    std::unordered_map<int, size_t> entityToIndex;  // Maps entity to its index in the dense array
};