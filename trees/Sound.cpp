#include "Sound.h"
#include <iostream>


Sound::Sound() {}

Sound::~Sound() {
    alDeleteBuffers(1, &ALBuffer);
}

Sound::Sound(std::string _name, std::string path){
	name = _name;
	loadSound(path);
}

ALuint Sound::getALBuffer(){
    return ALBuffer;
}

std::string Sound::getName() {
	return name;
}

void Sound::loadSound(const std::string& fileName) {
    SF_INFO sfinfo;
    SNDFILE* sndfile = sf_open(fileName.c_str(), SFM_READ, &sfinfo);
    if (!sndfile) {
        std::cerr << "Error loading sound file: " << fileName << std::endl;
        ALBuffer = 0;
        return;
    }

    std::vector<short> samples(sfinfo.channels * sfinfo.frames);
    sf_count_t numSamples = sf_read_short(sndfile, samples.data(), samples.size());
    sf_close(sndfile);

    if (numSamples <= 0) {
        std::cerr << "Error reading sound samples from file: " << fileName << std::endl;
        ALBuffer = 0;
        return;
    }

    ALenum format = (sfinfo.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    ALsizei size = static_cast<ALsizei>(samples.size() * sizeof(short));
    ALsizei freq = static_cast<ALsizei>(sfinfo.samplerate);

    ALuint tbuffer;
    alGenBuffers(1, &tbuffer);
    alBufferData(tbuffer, format, samples.data(), size, freq);
    ALBuffer = tbuffer;
}