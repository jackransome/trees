#pragma once

#include <variant>
#include "glm/glm.hpp"
#include <memory>
#include <vector>
#include <unordered_map>

enum class ColliderType {
    Cylinder,
    Sphere,
    Box,
    Hybrid
};

class Collider {
public:
    Collider(glm::vec3 p) : position(p) {}
    glm::vec3 getPosition() { return position; }
    void setPosition(glm::vec3 p) { position = p; }
    virtual ColliderType getType() const = 0;
private:
    glm::vec3 position;
};

class CylinderCollider : public Collider {
public:
    CylinderCollider(glm::vec3 p1, glm::vec3 p2, float r) : Collider(p1), position2(p2), radius(r) {}
    glm::vec3 position2;
    float radius;
    ColliderType getType() const override { return ColliderType::Cylinder; }
};

class SphereCollider : public Collider {
public:
    SphereCollider(glm::vec3 p, float r) : Collider(p), radius(r) {}
    float radius;
    ColliderType getType() const override { return ColliderType::Sphere; }
};

class BoxCollider : public Collider {
public:
    BoxCollider(glm::vec3 p, glm::vec3 d) : Collider(p), dimensions(d) {}
    glm::vec3 dimensions;
    ColliderType getType() const override { return ColliderType::Box; }
};

class HybridCollider : public Collider {
public:
    HybridCollider(glm::vec3 p, float r) : Collider(p), radius(r) {}
    float radius;
    ColliderType getType() const override { return ColliderType::Hybrid; }
};

class ColliderComponentManager {
public:
	ColliderComponentManager();
    void addCylinder(int entity, glm::vec3 position1, glm::vec3 position2, float radius);
    void addSphere(int entity, glm::vec3 position, float radius);
    void addBox(int entity, glm::vec3 position, glm::vec3 dimensions);
    void addHybrid(int entity, glm::vec3 position, float radius);
    Collider* get(int entity);
    void remove(int entity);
    const std::vector<std::unique_ptr<Collider>>& getAllColliders() const { return colliders; }
private:
    void add(int entity, std::unique_ptr<Collider> collider);
    std::vector<std::unique_ptr<Collider>> colliders;  // Dense array
    std::unordered_map<int, size_t> entityToIndex;  // Maps entity to its index in the dense array
};