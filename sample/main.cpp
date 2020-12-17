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
	key_controller controller;
	world newWorld{ &controller };
	new terrain_obj(&newWorld);

	while (newWorld.device->run() && newWorld.driver)
	{
		newWorld.update();

		newWorld.framerate();

		if (controller.IsKeyDown(KEY_KEY_S))
		{
			int size[3] = { 10, 10,50 };
			int pos[3] = { 10,10,10 };
			int mass = 0;
			new box_obj(&newWorld, size, pos, mass);
			controller.clear(KEY_KEY_S);
		}

	}
}

void test2() {

	key_controller controller;
	world newWorld{ &controller };
	main_obj* hg = new wheel_obj{ &newWorld };
	main_obj* bg = nullptr;
	new terrain_obj(&newWorld);

	int size[3] = { 10, 10,10 };
	int pos[3] = { 10,10,10 };
	int mass = 3;
	hg = new box_obj(&newWorld, size, pos, mass);

	main_obj* current = nullptr;
	while (newWorld.device->run() && newWorld.driver)
	{
		newWorld.update();
		newWorld.framerate();
		if (controller.IsKeyDown(KEY_KEY_Q))
		{
			//ICameraSceneNode* cameraNode{bg.irr_body,};
			//cameraNode->setPosition(vector3df(0, 10, -70));
			current = bg;
			controller.clear(KEY_KEY_Q);
		}
		if (controller.IsKeyDown(KEY_KEY_E))
		{
			current = hg;
			controller.clear(KEY_KEY_E);
		}
		if (controller.IsKeyDown(KEY_KEY_S))
		{
			controller.clear(KEY_KEY_S);
		}
		if (controller.IsKeyDown(KEY_KEY_W))
		{
			if (current != nullptr)
				current->forward();
			
		}
		if (current != nullptr && !controller.IsKeyDown(KEY_KEY_W))
		{
			current->stop();
			controller.clear(KEY_KEY_W);
		}
	}
}

void test3() 
{
	key_controller controller;
	world main_world{ &controller };
	//new terrain_obj(&main_world);

	int size[3] = { 10, 10,10 };
	int pos[3] = { 10,10,10 };
	int mass = 30;
	box_obj *obj = new box_obj(&main_world, size, pos, mass);

	ICameraSceneNode* cameraNode;
	cameraNode = main_world.scenemgr->addCameraSceneNode(obj->irr_body, vector3df(0, 10, 5));
	cameraNode->setFOV(0.78f);
	//cameraNode->setPosition(vector3df(0, 0, 10));
	while (main_world.device->run() && main_world.driver)
	{
		main_world.update();
		obj->irr_body->updateAbsolutePosition();
		cameraNode->setTarget(obj->irr_body->getAbsolutePosition());
		main_world.framerate();

		if (controller.IsKeyDown(KEY_KEY_W))
		{
			obj->forward();
			controller.clear(KEY_KEY_W);
		}
		if (controller.IsKeyDown(KEY_KEY_S))
		{
			obj->stop();
			controller.clear(KEY_KEY_S);
		}
	}
}

int main()
{
	int choice;
	do {
	printf("Choose test, 0 to exit: ");
	std::cin >> choice;
	choice == 3;
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
	}
	} while (choice != 0);

	return 0;
}