#include "Globals.h"

#include <windows.h>
#include <chrono>

//for testing
#include <thread>
#include "Globals.h"
#include "Csegment.h"
#include "Entity1.h"

using std::chrono::time_point_cast;
using std::chrono::duration_cast;

const bool debug = false;

int main()
{
	using std::make_shared;
	glm::vec3 camPos = glm::vec3(0, 0, 0);
	try
	{
		typedef std::chrono::high_resolution_clock Time;
		typedef std::chrono::microseconds us;
		
		globals::globalInit();

		auto currentTime = time_point_cast<us>(Time::now());
		double accumulator = 0.0;

		glm::vec3 cameraOffset{ 0, 2, 0 };

		while (!globals::gfx.shouldClose) {
			auto newTime = time_point_cast<us>(Time::now());
			auto frameTime = duration_cast<us>(newTime - currentTime).count();
			currentTime = newTime;

			accumulator += frameTime;

			while (accumulator >= globals::dt)
			{
				globals::gfx.setCameraAngle(globals::input.cameraAngle);
				globals::input.run();

				for (int i = 0; i < globals::polyhedrons.size(); i++) {
					for (int j = 0; j < globals::polyhedrons.size(); j++) {
						if (globals::polyhedrons[i]->type == entity && globals::polyhedrons[j]->type == c_seg) {
							Entity1* ent = dynamic_cast<Entity1*>(globals::polyhedrons[i].get());
							Csegment* cseg = dynamic_cast<Csegment*>(globals::polyhedrons[j].get());
							Csegment* currcseg = ent->getSegment();
							if (cseg != currcseg) {
								float distance = Collision_detection::getDistanceFromSeg(ent->position, cseg->getStart(), cseg->getEnd(), cseg->getDiameter());
								if (distance < Collision_detection::getDistanceFromSeg(ent->position, currcseg->getStart(), currcseg->getEnd(), currcseg->getDiameter())) {
									ent->setPlanePos(cseg->convertRealCoordsToPlane(ent->position));
									ent->changeSegment(cseg);
									ent->setHeight(0);
									
								}
							}
						}
					}
					globals::polyhedrons[i]->perLoop();
				}

				if (globals::input.keys.keyCounts["leftCtrl"] == 1)
				{
					globals::gfx.setObjectsWireFrame(true);
				}
				else if (globals::input.keys.keyCounts["leftCtrl"] == 0)
				{
					globals::gfx.setObjectsWireFrame(false);
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