#pragma once
#include "Input.h"
#include "Graphics.h"
#include "SoundPlayer.h"
#include "EntityManager.h"
#include "EntityFactory.h"
#include "ColliderComponentManager.h"
#include "CollisionSystem.h"


class MainSystem {
public:
	MainSystem();
	~MainSystem();
	void run();
	void keyCallback(int key, int scancode, int action, int mods);
	void init();
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

};