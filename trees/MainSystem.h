#pragma once
#include "Graphics.h"
#include "Input.h"
#include "SoundPlayer.h"
#include "EntityManager.h"
#include "EntityFactory.h"
#include "ColliderComponentManager.h"
#include "CollisionSystem.h"
#include "ControlSystem.h"
#include "RenderSystem.h"

class MainSystem {
public:
	MainSystem();
	~MainSystem();
	void run();
	void keyCallback(int key, int scancode, int action, int mods);
	void init();
	Graphics* getGfx() { return &gfx; }
private:
	void gameLogic();
	void draw();
	void loadResources();

	const std::chrono::milliseconds FixedTimeStep = std::chrono::milliseconds(17);
	std::chrono::milliseconds accumulator = std::chrono::milliseconds(0);

	Graphics gfx;
	Input input;
	SoundPlayer soundPlayer;

	EntityManager entityManager;
	EntityFactory entityFactory;
	ColliderComponentManager colliderComponentManager;
	CollisionSystem collisionSystem;
	ControlSystem controlSystem;
	RenderComponentManager renderComponentManager;
	RenderSystem renderSystem;
	TransformComponentManager transformComponentManager;
	CameraSystem cameraSystem;

};