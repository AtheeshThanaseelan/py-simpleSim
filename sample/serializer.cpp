#include "serializer.h"

/*Python can import and export JSON
* 
* Import and export entire world as binary for compatibility between python and c++ executable
* 
* 
* 
*/


//Binary Exporters 
//Write file
void test5()
{
	world* main_world = new world(controller);
	new terrain_obj(main_world);
	box_obj* box;
	{
		std::array<float,3> size = { 1,1,1 };
		std::array<int,3> pos = { 0,0,0 };
		box = new box_obj(main_world, size, pos, 1);
		box->bt_body->setGravity(btVector3(0, 0, 0));

	}
	box->bt_body->applyTorque(btVector3(0, 0, 100));

	while (main_world->device->run())
	{
		main_world->update();
		main_world->framerate();


		//Write Transform
		if (controller->IsKeyDown(KEY_KEY_A))
		{
			std::ofstream myFile("data.bin", std::ios::out | std::ios::binary);
			myFile.write((char*)&box->bt_body->getWorldTransform(), sizeof(box->bt_body->getWorldTransform()));
		}

	}
}

//Read File
void test6()
{
	world* main_world = new world(controller);
	new terrain_obj(main_world);
	box_obj* box;
	{
		std::array<float, 3> size = { 1,1,1 };
		std::array<int, 3> pos = { 0,0,0 };
		box = new box_obj(main_world, size, pos, 1);

	}

	while (main_world->device->run())
	{
		main_world->update();
		main_world->framerate();


		//Read Transform
		if (controller->IsKeyDown(KEY_KEY_A))
		{
			btTransform trabsfirn;
			std::fstream myFile("data.bin", std::ios::in | std::ios::binary);
			myFile.read((char*)&trabsfirn, sizeof(btTransform));
			box->bt_body->setWorldTransform(trabsfirn);
		}
	}
}

//Write World
void test7()
{
	world* main_world = new world(controller);
	std::ofstream myFile("world.bin", std::ios::out | std::ios::binary);
	myFile.write((char*)&main_world, sizeof(world));
}
//Read world
void test8()
{
	world* main_world;
	std::fstream myFile("world.bin", std::ios::in | std::ios::binary);
	myFile.read((char*)&main_world, sizeof(world));
	/*
	while (main_world->device->run())
	{
		main_world->update();
		main_world->framerate();
	}
	*/
}


//JSON Exporters
/*
* Important data
*	- Physical data
*	- Object specific properties
*	- World properties
* Graphical representation, Object collision shape, etc, can be inferred from object type
*
*	Simple Objects
*		Static: Type, Transform
*		Nonstatic: ^, linear velocity, angular velocity, mass
*/


//Try out JSON file reading
//mite jus do this in python xdddd
void test9()
{
	btTransform transform;
	transform.setIdentity();
	std::cout << transform.getRotation().getW() << std::endl;
	std::cout << transform.getRotation().getX() << std::endl;
	std::cout << transform.getRotation().getY() << std::endl;
	std::cout << transform.getRotation().getZ() << std::endl;
}