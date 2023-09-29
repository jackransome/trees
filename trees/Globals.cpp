#include "Globals.h"
#include "Cylinder.h"

namespace globals
{
	using std::make_shared;

	Graphics gfx;
	Input input;

	const float dt = 1000000.0f / 60.0f;
	const float dtSeconds = 1.0f / 60.0f;

	std::vector<shared_ptr<Polyhedron>> polyhedrons;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		globals::input.key_callback(key, scancode, action, mods);
	}

	void globalInit()
	{
		gfx.init();
		input.init(globals::gfx.getWindowPointer());
		glfwSetKeyCallback(globals::gfx.getWindowPointer(), key_callback);

		polyhedrons = std::vector<shared_ptr<Polyhedron>>
		{
			make_shared<Cylinder>(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0,0,0)),
			make_shared<Cylinder>(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0,0,0)),
			make_shared<Cylinder>(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0,0,0))
		};


		//polyhedrons.push_back(make_shared<Platform>(glm::vec3(10, 1.5, 10), glm::vec3(-50 + i * 10, -4, -50 + j * 10), 100));

	}
}