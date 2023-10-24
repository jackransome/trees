#include "MainSystem.h"

MainSystem::MainSystem()
{

}

MainSystem::~MainSystem()
{
}

void MainSystem::init()
{
	//setting up graphics and window
	gfx.init();
	
	//setting up input
	input.init(gfx.getWindowPointer());
	
	
	//setting up sound
	soundPlayer.setGlobalVolume(1);

	//loading all sound
	loadResources();
}

void MainSystem::loadResources()
{

}

void MainSystem::keyCallback(int key, int scancode, int action, int mods){
	input.key_callback(key, scancode, action, mods);
}
