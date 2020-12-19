#include "base_utils.h"
#include "simple_objects.h"
#include "bullet_example_files/wheel_obj.h"

/*
Logic Controller:
Controls all objects > has them in objects
Move objects
Calculate any logic for world

Player controller:
Any controllable object extends
Object defines function of each key
*/

/*
base
	key controller
	world
	main_obj

object utils
	bt rigid body
	cube node

simple obj
	box obj
	terrain obj

wheel obj
	only it
*/


void test1() {
	key_controller* controller = new key_controller{};
	world* main_world = new world{ controller };
	new terrain_obj(main_world);

	while (main_world->device->run() && main_world->driver)
	{
		main_world->update();

		main_world->framerate();

		if (controller->IsKeyDown(KEY_KEY_S))
		{
			new box_obj{ main_world,new int[] {10,10,10},new int[] {1,1,10},1 };
			controller->clear(KEY_KEY_S);
		}
		if (controller->IsKeyDown(KEY_ESCAPE))
		{
			break;
		}

	}
	delete main_world;
	delete controller;
	
}

void test2() {

	key_controller* controller = new key_controller{};
	world* main_world = new world{ controller };
	main_obj* hg = new wheel_obj{ main_world };
	main_obj* bg = new box_obj{ main_world,new int[] {1,1,1},new int[] {1,1,1},1 };
	terrain_obj* terr = new terrain_obj{ main_world }; 
	main_obj* current = nullptr;

	while (main_world->device->run() && main_world->driver)
	{
		main_world->update();
		main_world->framerate();
		if (controller->IsKeyDown(KEY_KEY_Q))
		{
			//ICameraSceneNode* cameraNode{bg.irr_body,};
			//cameraNode->setPosition(vector3df(0, 10, -70));
			current = bg;
			controller->clear(KEY_KEY_Q);
		}
		if (controller->IsKeyDown(KEY_KEY_E))
		{
			current = hg;
			controller->clear(KEY_KEY_E);
		}
		if (controller->IsKeyDown(KEY_KEY_S))
		{
			controller->clear(KEY_KEY_S);
		}
		if (controller->IsKeyDown(KEY_KEY_W))
		{
			if (current != nullptr)
				current->forward();
			
		}
		if (current != nullptr && !controller->IsKeyDown(KEY_KEY_W))
		{
			current->stop();
			controller->clear(KEY_KEY_W);
		}
	}
	delete terr;
	delete current;
	delete hg;
	delete bg;
	delete main_world;
	delete controller;
}

void test3() 
{
	key_controller* controller = new key_controller{};
	world* main_world = new world{ controller };
	terrain_obj* terr = new terrain_obj{main_world};

	box_obj *obj =  new box_obj{ main_world,new int[] {1,1,1},new int[] {1,1,1},1 };

	
	ICameraSceneNode* cameraNode;
	cameraNode = main_world->scenemgr->addCameraSceneNode(obj->irr_body, vector3df(0, 10, 5));
	cameraNode->setFOV(0.78f);
	//cameraNode->setPosition(vector3df(0, 0, 10));
	
	while (main_world->device->run() && main_world->driver)
	{
		obj->irr_body->updateAbsolutePosition();
		cameraNode->setTarget(obj->irr_body->getAbsolutePosition());

		main_world->update();
		main_world->framerate();

		if (controller->IsKeyDown(KEY_KEY_W))
		{
			obj->forward();
			controller->clear(KEY_KEY_W);
		}
		if (controller->IsKeyDown(KEY_KEY_S))
		{
			obj->stop();
			controller->clear(KEY_KEY_S);
		}
	}
	delete main_world;
	delete controller;
	
}

void test4()
{
	key_controller* controller = new key_controller{};
	world *main_world = new world{ controller };

	box_obj* box = nullptr;
	terrain_obj* terr = nullptr;
	main_obj* main = nullptr;

	ICameraSceneNode* cameraNode = main_world->scenemgr->addCameraSceneNode();

	while (main_world->device->run() && main_world->driver)
	{
		main_world->update();
		main_world->device->run(); 
		main_world->framerate();
		/*
		if (controller->IsKeyDown(KEY_KEY_W))
		{
			box = new box_obj{ main_world,new int[] {1,1,1},new int[] {1,1,1},1 };
			controller->clear(KEY_KEY_W);
		}

		if (controller->IsKeyDown(KEY_KEY_S))
		{
			if(box != nullptr)
				delete box;
			controller->clear(KEY_KEY_S);
		}
			
		if (controller->IsKeyDown(KEY_KEY_A))
		{
			terr = new terrain_obj{main_world};
			controller->clear(KEY_KEY_A);
		}

		if (controller->IsKeyDown(KEY_KEY_D))
		{
			if (terr != nullptr)
				delete terr;
			terr = nullptr;
			controller->clear(KEY_KEY_D);
		}
		*/
		if (controller->IsKeyDown(KEY_KEY_Q))
		{
			main = new wheel_obj{ main_world };
			controller->clear(KEY_KEY_Q);
		}

		if (controller->IsKeyDown(KEY_KEY_E))
		{
			if (main != nullptr)
				delete main;
			main = nullptr;
			controller->clear(KEY_KEY_E);
		}
	}
	delete main_world;
	delete controller; 
}

int main()
{
	int choice;
	do {
		printf("Choose test, 0 to exit: ");
		std::cin >> choice;
		switch (choice)
		{
			case 1:
				test1();
				break;
			case 2:
				test2();
				break;
			case 3:
				test3();
				break;
			case 4:
				test4();
				break;
		}
	} while (choice != 0);

	return 0;
}