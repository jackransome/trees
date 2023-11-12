#include "MainSystem.h"
#include <chrono>
using std::chrono::time_point_cast;
using std::chrono::duration_cast;
using us = std::chrono::microseconds;
using Time = std::chrono::steady_clock; // Or std::chrono::system_clock, depending on the need


MainSystem::MainSystem() :
	entityFactory(colliderComponentManager, transformComponentManager, renderComponentManager, entityManager, controlSystem),
	cameraSystem(gfx)
{
	
}

MainSystem::~MainSystem()
{
}

void MainSystem::init()
{
	// setting up graphics and window
	gfx.init();
	
	// setting up input
	input.init(gfx.getWindowPointer());
	
	
	// setting up sound
	soundPlayer.setGlobalVolume(1);

	// loading all sound
	loadResources();

	//setting up input
	controlSystem.init(&colliderComponentManager, &input, &cameraSystem);

	//setting up render system
	renderSystem.init(&gfx, &transformComponentManager, &renderComponentManager);
	entityFactory.addCylinder(glm::vec3(3), glm::vec3(3, 1, 1), 1);
	for (int i = 0; i < 990; i++) {
		entityFactory.addCylinder(glm::vec3(-2), glm::vec3(-4, 2, -2), 0.5);
	}
	
	entityFactory.addPlayer(glm::vec3(0));

}

void MainSystem::run()
{


	auto currentTime = time_point_cast<us>(Time::now());
	double accumulator = 0.0;
	const float dt = 1000000.0f / 60.0f;

	glm::vec3 cameraOffset{ 0, 2, 0 };
	int frames = 0;
	auto FPSTimer = time_point_cast<us>(Time::now());


	while (!gfx.shouldClose) {

		auto newTime = time_point_cast<us>(Time::now());
		auto frameTime = duration_cast<us>(newTime - currentTime).count();
		currentTime = newTime;

		accumulator += frameTime;

		while (accumulator >= dt)
		{
			//run
			//run game logic
			gameLogic();

			//run sound system
			soundPlayer.update();


			accumulator -= dt;
		}

		frames++;
		if (frames == 50) {
			auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(time_point_cast<us>(Time::now()) - FPSTimer).count();
			//auto now = std::chrono::steady_clock::now();

			float fps = 1000.0f * frames / elapsed; // Calculate FPS
			std::cout << "FPS: " << fps << "\n";

			FPSTimer = time_point_cast<us>(Time::now()); // Reset the timer
			frames = 0; // Reset frame count
		}

		//draw
		draw();

		//execute draws with vulkan
		gfx.run();
		//std::cout << "running\n";
	}

}

void MainSystem::gameLogic()
{
	input.run();
	//handle controls
	controlSystem.run();
	controlSystem.changeCameraAngle();
	
	//move things

	//correct colliders
	collisionSystem.correctCollisions(colliderComponentManager);

	
}

void MainSystem::draw()
{
	cameraSystem.updateGfx();
	if (!x) {
		x = true;
		
		renderSystem.drawAll();
	}
	
	//gfx.clearDrawInstances();

	
}

void MainSystem::loadResources()
{
	// load sounds
	soundPlayer.loadSound("distant_1", "sounds/distant_1.wav");
	soundPlayer.loadSound("distant_2", "sounds/distant_2.wav");
	soundPlayer.loadSound("distant_3", "sounds/distant_3.wav");
	soundPlayer.loadSound("distant_4", "sounds/distant_4.wav");
	soundPlayer.loadSound("Wind1", "sounds/Wind1.wav");
}

void MainSystem::keyCallback(int key, int scancode, int action, int mods){
	input.key_callback(key, scancode, action, mods);
}
