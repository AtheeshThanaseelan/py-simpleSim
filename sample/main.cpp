#include "base_utils.h"
#include "simple_objects.h"
#include "bullet_example_files/wheel_obj.h"

/*
Object Controller:
Controls all objects > has them in objects
Move objects
Controls input using key_controller
	Has variable holding currently controlled object
*/

int main()
{
	key_controller controller;
	world newWorld{ &controller };
	wheel_obj* hg = new wheel_obj{ &newWorld };
	wheel_obj* bg = nullptr;
	new terrain_obj(&newWorld);
	wheel_obj* current = nullptr;

	while (newWorld.device->run() && newWorld.driver)
	{
		newWorld.update();
		newWorld.framerate();
		
		if (controller.IsKeyDown(KEY_KEY_Q))
		{
			current = bg;
			std::cout << current->m_carChassis<<std::endl;
			controller.clear(KEY_KEY_Q);
		}
		if (controller.IsKeyDown(KEY_KEY_E))
		{
			current = hg;
			std::cout << current ->m_carChassis << std::endl;
			controller.clear(KEY_KEY_E);
		}
		if (controller.IsKeyDown(KEY_KEY_S))
		{
			bg = new wheel_obj{ &newWorld };
			//new box_obj(&newWorld);
			controller.clear(KEY_KEY_S);
		}
		if (current != nullptr)
		{
			//std::cout<<current;
			current->run(controller);
		}
	}
	return 0;
}
