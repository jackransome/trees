#include "MainSystem.h"

MainSystem::MainSystem()
{

}

MainSystem::~MainSystem()
{
}

void MainSystem::run()
{
	while (!gfx.shouldClose) {

		//run game logic
		gameLogic();

		//draw
		draw();

		//execute draws with vulkan
		gfx.run();
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
}

void MainSystem::gameLogic()
{
}

void MainSystem::draw()
{
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
