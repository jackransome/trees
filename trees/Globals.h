#include "Graphics.h"
#include "Input.h"
#include "Polyhedron.h"
#include "Collision_detection.h"

namespace globals
{
	using std::shared_ptr;

	extern Graphics gfx;
	extern Input input;

	extern const float dt;
	extern const float dtSeconds;

	extern std::vector<shared_ptr<Polyhedron>> polyhedrons;

	void globalInit();
}