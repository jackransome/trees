#include "RenderSystem.h"

RenderSystem::RenderSystem()
{

}

void RenderSystem::init(Graphics* g, ColliderComponentManager* c, RenderComponentManager* r)
{
    gfx = g;
    colliderManager = c;
    renderComponentManager = r;
}

void RenderSystem::drawAll()
{
    const auto& allRenderComponents = renderComponentManager->getAll();
    for (int i = 0; i < allRenderComponents.size(); ++i) {
        int entityId = allRenderComponents[i]->getEntity();
        Collider* collider = colliderManager->get(entityId);
        if (collider) {
            glm::vec3 position = collider->position;
            // Use the position for rendering...
            // Set model matrix, draw the mesh, etc.
        }
    }
}

