#pragma once
#include <vector>
#include <deque>
#include "Sound.h"
#include <glm/glm.hpp>

class SoundInstance {
public:
	SoundInstance(int _id, const ALuint ALBuffer, float _volume, float _pitch, bool _loop) {

		alGenSources(1, &source);
		alSourcei(source, AL_BUFFER, ALBuffer); // `buffer` is the ALuint returned by loadSound

		alSourcef(source, AL_GAIN, _volume); // Volume level: 0.0f (mute) to 1.0f (full volume)
		
		alSourcef(source, AL_PITCH, _pitch); //setting pitch

		alSourcei(source, AL_LOOPING, _loop); //looping options

		id = _id;
		volume = _volume;
		pitch = _pitch;

		alSourcePlay(source);

	}
	~SoundInstance() {
		stop();
		end();
	}
	bool getStopped() {
		ALint sourceState;
		alGetSourcei(source, AL_SOURCE_STATE, &sourceState);

		if (sourceState == AL_STOPPED) {
			return true;
		}
		return false;
	}
	void loop() {
		loops = true;
		alSourcei(source, AL_LOOPING, true); //looping options
	}
	void loopBetween(float _start, float _end) {
		loopsBetween = true;
		loopStart = _start;
		loopEnd = _end;
	}
	void stop() {
		alSourceStop(source);
	}
	float getPlayingOffset() {
		ALfloat playbackPosition;
		alGetSourcef(source, AL_SEC_OFFSET, &playbackPosition);
		return playbackPosition;
	}
	void setVolume(float _volume) {
		alSourcef(source, AL_GAIN, _volume);
	}
	void end() {
		alDeleteSources(1, &source);
	}
	bool getLoopsBetween() {
		return loopsBetween;
	}
	float getLoopEnd() {
		return loopEnd;
	}
	float getLoopStart() {
		return loopStart;
	}
	void setPlayingOffset(float offset) {
		alSourcef(source, AL_SEC_OFFSET, offset);
	}
	int getID() {
		return id;
	}
private:
	ALuint source;
	bool loops = false;
	bool loopsBetween = false;
	float loopStart = 0;
	float loopEnd = 0;
	float volume;
	float pitch;
	std::string soundName;
	int id;

};

class SoundPlayer {
public:
	SoundPlayer();
	~SoundPlayer();
	void loadSound(std::string name, std::string path);
	int playSoundByName(std::string name);
	int playSoundByName(std::string name, float volume);
	int playSoundByName(std::string name, float volume, float pitch);
	void loopSound(int id);
	void loopSoundBetween(int id, float start, float end);
	void stopSound(int id);
	float getPlayingOffset(int id);
	void setVolume(int id, float volume);
	float getSpatialVolume(glm::vec2 pos1, glm::vec2 pos2);
	void update();
	void finish();
	void setGlobalVolume(float volume);
	float getGlobalVolume();
private:
	ALCcontext* context;
	ALCdevice* device;
	float globalVolume = 1;
	std::vector<Sound*> sounds;
	std::vector<SoundInstance*> soundInstances;
	int nextID = 0;
};