#include "Globals.h"
#include "Cylinder.h"
#include "Csegment.h"
#include "Entity1.h"
#include "World_generator.h"
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
			make_shared<Csegment>(glm::vec3(100, 90, 90), glm::vec3(90, 95, 90), 0)
		};
		glm::vec3 temp;
		for (float i = 0; i < 1; i += 0.01) {
			temp = (dynamic_cast<Csegment*>(polyhedrons.back().get()))->convertPlaneToNormal(i* (dynamic_cast<Csegment*>(polyhedrons.back().get()))->getPlaneDims().x);
			std::cout << temp.x << " | " << temp.y << " | " << temp.z << " | \n";
		}
		World_generator();
		polyhedrons.push_back(make_shared<Entity1>(dynamic_cast<Csegment*>(polyhedrons.back().get())));
		


	}
}