#include "Globals.h"

#include <windows.h>
#include <chrono>

//for testing
#include <thread>

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

				for (auto polyhedron : globals::polyhedrons)
				{
					polyhedron->perLoop();
				}

				//globals::gfx.setCameraPos(camPos);
				if (globals::input.keys.keyCounts["w"] >= 1)
				{
					camPos.x+=0.1;
				}
				if (globals::input.keys.keyCounts["a"] >= 1)
				{
					camPos.z += 0.1;
				}
				if (globals::input.keys.keyCounts["s"] >= 1)
				{
					camPos.x -= 0.1;
				}
				if (globals::input.keys.keyCounts["d"] >= 1)
				{
					camPos.z -= 0.1;
				}
				if (globals::input.keys.keyCounts["q"] >= 1)
				{
					camPos.y += 0.1;
				}
				if (globals::input.keys.keyCounts["e"] >= 1)
				{
					camPos.y -= 0.1;
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