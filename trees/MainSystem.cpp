#include "MainSystem.h"

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

	auto previousTime = std::chrono::steady_clock::now();

	while (!gfx.shouldClose) {
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsedTimeInMicro = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - previousTime);
		previousTime = currentTime;

		// Convert microseconds to milliseconds before adding to the accumulator to prevent truncation to zero.
		std::chrono::milliseconds elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTimeInMicro);

		accumulator += elapsedTime;


		// Update game logic as many times as possible within the fixed time step
		while (accumulator >= FixedTimeStep) {
			// Your game update logic here using FixedTimeStep as the delta time

			//run game logic
			gameLogic();
			
			//run sound system
			soundPlayer.update();

			accumulator -= FixedTimeStep;
		}
		std::cout << "running\n";


		// Render game state here
		// Optionally, you can use the value of accumulator/FixedTimeStep as an interpolation factor for smoother rendering

		//draw
		draw();

		//execute draws with vulkan
		gfx.run();

		// You might want to add a sleep here to prevent the loop from running too fast and consuming too much CPU
		// But remember that the actual sleep time should be adjusted based on how long the update and render took
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

}

void MainSystem::gameLogic()
{
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
	//gfx.clearDrawInstances();

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
