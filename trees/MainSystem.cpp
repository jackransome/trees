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

void MainSystem::run()
{


	auto currentTime = time_point_cast<us>(Time::now());
	double accumulator = 0.0;
	const float dt = 1000000.0f / 60.0f;

	glm::vec3 cameraOffset{ 0, 2, 0 };

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

		//draw
		draw();

		//execute draws with vulkan
		gfx.run();
		std::cout << "running\n";
	}

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
	controlSystem.init(&colliderComponentManager, &input);

	//setting up render system
	renderSystem.init(&gfx, &transformComponentManager, &renderComponentManager);

	entityFactory.addCylinder(glm::vec3(3), glm::vec3(3, 1, 1), 1);

}

void MainSystem::gameLogic()
{
	input.run();
	//handle controls
	controlSystem.run();
	controlSystem.changeCameraAngle(cameraSystem);
	
	//move things

	//correct colliders
	collisionSystem.correctCollisions(colliderComponentManager);

	
}

void MainSystem::draw()
{
	cameraSystem.updateGfx();
	gfx.clearDrawInstances();

	renderSystem.drawAll();
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
