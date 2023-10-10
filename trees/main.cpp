#include "Globals.h"

#include <windows.h>
#include <chrono>

//for testing
#include <thread>
#include "Globals.h"
#include "Csegment.h"
#include "Entity1.h"
#include "SoundPlayer.h"
#include <cstdlib>  // For rand() and RAND_MAX


using std::chrono::time_point_cast;
using std::chrono::duration_cast;

const bool debug = false;

int main()
{
	using std::make_shared;
	glm::vec3 camPos = glm::vec3(0, 0, 0);
	std::cout << glm::dot(glm::vec3(1, 1, 1), glm::vec3(1, 1, 1)) << "\n";
	try
	{
		typedef std::chrono::high_resolution_clock Time;
		typedef std::chrono::microseconds us;
		
		globals::globalInit();

		auto currentTime = time_point_cast<us>(Time::now());
		double accumulator = 0.0;

		glm::vec3 cameraOffset{ 0, 2, 0 };

		SoundPlayer soundPlayer;
		soundPlayer.setGlobalVolume(1);
		soundPlayer.loadSound("distant_1", "sounds/distant_1.wav");
		soundPlayer.loadSound("distant_2", "sounds/distant_2.wav");
		soundPlayer.loadSound("distant_3", "sounds/distant_3.wav");
		soundPlayer.loadSound("distant_4", "sounds/distant_4.wav");
		soundPlayer.loadSound("Wind1", "sounds/Wind1.wav");
		int music_id = soundPlayer.playSoundByName("Wind1", 0.3);
		soundPlayer.loopSound(music_id);
		int counter = 0;
		int countermax = 10000;
		int selector = rand() % 3;
		while (!globals::gfx.shouldClose) {
			counter++;
			if (counter == countermax) {
				counter = 0;
				countermax = 10000 + rand() % 30000;
				if (selector == 0) {
					soundPlayer.playSoundByName("distant_1", 0.02);
				}
				else if (selector == 1) {
					soundPlayer.playSoundByName("distant_2", 0.35);
				} 
				else if (selector == 2) {
					soundPlayer.playSoundByName("distant_3", 0.35);
				}
				else {
					soundPlayer.playSoundByName("distant_4", 0.3);
				}
				selector += rand() % 3 + 1;
				if (selector > 3) {
					selector -= 4;
				}
				
			}
			auto newTime = time_point_cast<us>(Time::now());
			auto frameTime = duration_cast<us>(newTime - currentTime).count();
			currentTime = newTime;

			accumulator += frameTime;

			while (accumulator >= globals::dt)
			{
				globals::gfx.setCameraAngle(globals::input.cameraAngle);
				globals::input.run();
				bool switched = false;
				for (int i = 0; i < globals::polyhedrons.size(); i++) {
					for (int j = 0; j < globals::polyhedrons.size(); j++) {
						if (!switched) {
							if (globals::polyhedrons[i]->type == entity && globals::polyhedrons[j]->type == c_seg) {
								Entity1* ent = dynamic_cast<Entity1*>(globals::polyhedrons[i].get());
								Csegment* cseg = dynamic_cast<Csegment*>(globals::polyhedrons[j].get());
								Csegment* currcseg = ent->getSegment();
								if (cseg != currcseg) {
									float distance = Collision_detection::getDistanceFromSeg(ent->position, cseg->getStart(), cseg->getEnd(), cseg->getDiameter());
									if (distance < Collision_detection::getDistanceFromSeg(ent->position, currcseg->getStart(), currcseg->getEnd(), currcseg->getDiameter())) {
										ent->setPlanePos(cseg->convertRealCoordsToPlane(ent->position));
										ent->changeSegment(cseg);
										ent->setHeight(distance);
										switched = true;
									}
								}
							}
						}
					}
					globals::polyhedrons[i]->perLoop();
				}

				if (globals::input.keys.keyCounts["leftCtrl"] == 1)
				{
					//globals::gfx.setObjectsWireFrame(true);
				}
				else if (globals::input.keys.keyCounts["leftCtrl"] == 0)
				{
					//globals::gfx.setObjectsWireFrame(false);
				}

				accumulator -= globals::dt;
			}

			globals::gfx.run();
		}
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		for (int i = 0; i < 100000000; i++) {}
		return EXIT_FAILURE;
	}

	globals::gfx.cleanup();

	return EXIT_SUCCESS;
}