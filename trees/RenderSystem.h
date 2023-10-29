#pragma once
#include "Graphics.h"
#include "ColliderComponentManager.h"
#include "RenderComponentManager.h"

class RenderSystem {
public:
	RenderSystem();
	void init(Graphics* gfx, ColliderComponentManager* colliderManager, RenderComponentManager* renderComponentManager);
	void drawAll();
private:
	Graphics* gfx;
	ColliderComponentManager* colliderManager;
	RenderComponentManager* renderComponentManager;
};