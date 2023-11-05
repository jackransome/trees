#pragma once
#include "Graphics.h"
#include "ColliderComponentManager.h"
#include "RenderComponentManager.h"
#include "TransformComponentManager.h"

class RenderSystem {
public:
	RenderSystem();
	void init(Graphics* gfx, TransformComponentManager* transformManager, RenderComponentManager* renderComponentManager);
	void drawAll();
private:
	Graphics* gfx;
	TransformComponentManager* transformManager;
	RenderComponentManager* renderComponentManager;
};