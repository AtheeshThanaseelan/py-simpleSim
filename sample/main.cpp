#include "base_utils.h"
#include "simple_objects.h"

int main()
{
	key_controller controller;
	world newWorld{ &controller };

	printf("\n<----im my own shoe---->\n ");

	while (newWorld.device->run() && newWorld.driver)
	{
		newWorld.update();
		newWorld.framerate();
		if (controller.IsKeyDown(KEY_KEY_Q))
		{
			new terrain_obj(&newWorld);
			controller.clear(KEY_KEY_Q);
		}
		if (controller.IsKeyDown(KEY_KEY_E))
		{
			new box_obj(&newWorld);
			controller.clear(KEY_KEY_E);
		}
	}
	return 0;
}
