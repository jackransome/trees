#pragma once
#include <al.h>
#include <alc.h>
#include <sndfile.h>
#include <vector>
#include <iostream>

class Sound {
public:
	Sound();
    ~Sound();
	Sound(std::string name, std::string path);
	ALuint getALBuffer();
	std::string getName();

	void loadSound(const std::string& fileName);
private:
	
	std::string name;
    ALuint ALBuffer;
};