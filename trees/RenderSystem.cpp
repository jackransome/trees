#include "RenderSystem.h"

RenderSystem::RenderSystem()
{

}

void RenderSystem::init(Graphics* g, TransformComponentManager* t, RenderComponentManager* r)
{
    gfx = g;
    transformManager = t;
    renderComponentManager = r;
}

void RenderSystem::drawAll()
{
    const auto& allRenderComponents = renderComponentManager->getAll();
    for (int i = 0; i < allRenderComponents.size(); ++i) {
        int entityId = allRenderComponents[i]->getEntity();
        TransformComponent* transform = transformManager->get(entityId);
        if (transform) {
            glm::vec3 position = transform->getPosition();
            glm::vec3 rotation = transform->getRotation();
            gfx->addDrawInstance(allRenderComponents[i]->getMeshIndex(), position, allRenderComponents[i]->getScale(), rotation);
            // Use the transform position and rotation for rendering...
            // Set model matrix, draw the mesh, etc.
        }
    }
}
