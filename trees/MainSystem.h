#pragma once
#include "Input.h"
#include "Graphics.h"
#include "SoundPlayer.h"

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
	

	Graphics gfx;
	Input input;
	SoundPlayer soundPlayer;
	
};