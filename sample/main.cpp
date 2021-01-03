#include "base_utils.h"
#include "simple_objects.h"
#include "compound_obj.h"
#include "complex_obj.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "serializer.h"


namespace py = pybind11;
//Controllers

//Classes
/* Classes
* World Object (for graphics and physics)
* Complex World Object (for extras (wind, air density)
* Const Static Controller Object
* 
* Simple Objects
* Compound Object
* Complex(logic) Object
* Camera Object
*/
//Old tests
/*
//Helicopter
void test1()
{
	//Helicopter
//Helicopter is lifted by force on rotor
//Rotor force is relative to collective and engine rpm
//engine rpm depends on environment(air density, load, etc)
//update logic along with world

	key_controller* controller = new key_controller{};
	world* main_world = new world{ controller };
	new terrain_obj(main_world);
	complex_obj* heli = new complex_obj(main_world);
	camera* cam = new camera(main_world,heli->frame->irr_body);

	while (main_world->device->run() && main_world->driver)
	{
		cam->update();
		main_world->update();
		main_world->framerate();
		heli->update_logic();
		if (controller->IsKeyDown(KEY_KEY_P))
		{
			heli->direct(complex_obj::direction::up);
		}
		if (controller->IsKeyDown(KEY_KEY_L))
		{
			heli->direct(complex_obj::direction::down);
		}
		if (controller->IsKeyDown(KEY_KEY_W))
		{
			heli->direct(complex_obj::direction::front);
		}
		if (controller->IsKeyDown(KEY_KEY_S))
		{
			heli->direct(complex_obj::direction::back);
		}
		if (controller->IsKeyDown(KEY_KEY_A))
		{
			heli->direct(complex_obj::direction::l_left);
		}
		if (controller->IsKeyDown(KEY_KEY_D))
		{
			heli->direct(complex_obj::direction::l_right);
		}
		if (controller->IsKeyDown(KEY_KEY_Q))
		{
			heli->direct(complex_obj::direction::y_left);
		}
		if (controller->IsKeyDown(KEY_KEY_E))
		{
			heli->direct(complex_obj::direction::y_right);
		}
		if(controller->IsKeyDown(KEY_SPACE))
		{
			std::cout << "n" << std::endl;
			heli->direct(complex_obj::direction::neutral);
		}
		if (controller->IsKeyDown(KEY_KEY_I))
		{
			std::array<float,7> ok= heli->getTransform_qat();
			for (int i=0; i<7;i++)
			{
				std::cout << ok[i] << std::endl;
			}
			std::cout << heli->getProperties() << std::endl;
			system("cls");
		}
		if (controller->IsKeyDown(KEY_KEY_T))
		{
			std::array<float, 7> set = { {0.5,0.5,0.5,0.5,1,1,1} };
			heli->setTransform_qat(set);
		}


	}
	delete main_world;
	delete controller;
}

//bike
void test2()
{
	key_controller* controller = new key_controller{};
	world* main_world = new world{ controller };
	new terrain_obj(main_world);
	compound_obj* heli = new compound_obj(main_world);
	camera* cam = new camera(main_world, heli->irr_main_body);
	cam = new camera(main_world);

	while (main_world->device->run() && main_world->driver)
	{
		cam->update();
		main_world->update();
		main_world->framerate();
		//heli->update_logic();
		if (controller->IsKeyDown(KEY_KEY_P))
		{
			heli->direct(complex_obj::direction::up);
		}
		if (controller->IsKeyDown(KEY_KEY_L))
		{
			heli->direct(complex_obj::direction::down);
		}
		if (controller->IsKeyDown(KEY_KEY_W))
		{
			heli->direct(complex_obj::direction::front);
		}
		if (controller->IsKeyDown(KEY_KEY_S))
		{
			heli->direct(complex_obj::direction::back);
		}
		if (controller->IsKeyDown(KEY_KEY_A))
		{
			heli->direct(complex_obj::direction::l_left);
		}
		if (controller->IsKeyDown(KEY_KEY_D))
		{
			heli->direct(complex_obj::direction::l_right);
		}
		if (controller->IsKeyDown(KEY_KEY_Q))
		{
			heli->direct(complex_obj::direction::y_left);
		}
		if (controller->IsKeyDown(KEY_KEY_E))
		{
			heli->direct(complex_obj::direction::y_right);
		}
		if (controller->IsKeyDown(KEY_SPACE))
		{
			std::cout << "n" << std::endl;
			heli->direct(complex_obj::direction::neutral);
		}
		if (controller->IsKeyDown(KEY_KEY_I))
		{
			std::array<float, 7> ok = heli->getTransform_qat();
			for (int i = 0; i < 7; i++)
			{
				std::cout << ok[i] << std::endl;
			}
			std::cout << heli->getProperties() << std::endl;
			system("cls");
		}
		if (controller->IsKeyDown(KEY_KEY_T))
		{
			std::array<float, 7> set = { {0.5,0.5,0.5,0.5,1,1,1} };
			heli->setTransform_qat(set);
		}


	}
	delete main_world;
	delete controller;
}

//Visualizations
void test3()
{
	world* main_world = new world(controller);
	//new terrain_obj(main_world);
	box_obj* box;
	{
		float size[] = { 1,1,1 };
		int pos[] = { 0,10,0 };
		box = new box_obj(main_world, new float[] {3, 3, 3}, new int[]{ 0,10,0 }, 12);
	}
	//Arrow
	IAnimatedMesh* cubeNode = main_world->scenemgr->addArrowMesh("OK");//("", video::SColor(0, 255, 0, 255), video::SColor(0, 255, 0, 255),4,8,10.f,20.f,0.5f,5.f);//addCubeSceneNode(1.0f, 0, 0, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(0,0,0));
	IAnimatedMeshSceneNode* arrow = main_world->scenemgr->addAnimatedMeshSceneNode(cubeNode);
	
	while (main_world->device->run())
	{
		main_world->update();
		main_world->framerate();
		

	}
	
}

//Benchmarks
//setGravity is in m/s^2
//position is in meters
//The new timer is accurate compared to the RTC timer
//Fixed timestep leads to reproducable results
void test4()
{
	//Base Utility
	//Count time in the update loop?
	world* main_world = new world(controller);
	//new terrain_obj(main_world);
	box_obj* box;
	{
		float size[] = { 1,1,1 };
		int pos[] = { 0,0,0 };
		box = new box_obj(main_world, new float[] {1, 1, 1}, new int[] { 0, 0, 0 }, 1);
		box->body->setGravity(btVector3(0, -9.8, 0));
	}

	float start = main_world->device->getTimer()->getTime();
	world_timer* ok = new world_timer();
	while (main_world->device->run())
	{
		main_world->update();
		main_world->framerate();
		ok->advance();
		std::cout << box->body->getWorldTransform().getOrigin().getY() << std::endl;
		if (box->body->getWorldTransform().getOrigin().getY() < -10)
		{
			float end = main_world->device->getTimer()->getTime();
			std::cout << std::endl << end-start << std::endl;
			std::cout << std::endl << ok->get_time() << std::endl;
			break;
		}

	}
	delete ok;
	delete box;
	delete main_world;
}

*/
//Naming Scheme
/*
* Private: m_ 
* 
* Objects for use in world: obj_
*	Simple: obj_simple
*	Complex: obj_comp
* 
* Containers
*	?External Driver Containers (etc)
*	Physics Object Containers
*	?Graphics Object Container
*	Complex Object Container
*	
* 
* Interfaces/Controllers like py_obj, etc: control_
*	Object Interface: Apply and Return Basic Information
*	Complex Object Interface: Apply and Return Complex Information
*	Interactive Object Interface
*	?Self Controlling Object Interface
*/


//Test obj_interface
//
void test1()
{
	world* main_world = new world(controller);
	terrain_obj* terr = new terrain_obj(main_world);
	
	std::array<float,3> size = {1,1,1};
	std::array<int, 3> pos = { 0,5,0 };
	py_obj* box = new box_obj(main_world,size, pos, 5);
	
	
	while (main_world->device->run())
	{
		main_world->update();
		if (controller->IsKeyDown(KEY_KEY_A))
			std::cout << box->getProperties() << std::endl;
	}
}

#if defined _DEBUG
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
/*
			case 2:
				test2();
				break;
			
			case 3:
				test3();
				break;
			
			case 4:
				test4();
				break;

			case 5:
				test5();
				break;
			
			case 6:
				test6();
				break;
			case 7:
				test7();
				break;
			case 8:
				test8();
				break;
			case 9:
				test9();
				break;
*/
			}
		} while (choice != 0);

		return 0;
	}


#else
	PYBIND11_MODULE(sample, m) 
	{
		py::class_<py_obj>(m, "py_obj")
			.def("getProperties", &py_obj::getProperties, R"pbdoc(Get the object properties)pbdoc")
			.def("setTransform_qat", &py_obj::setTransform_qat, R"pbdoc(Set the object transform as a quaternion)pbdoc")
			.def("getTransform_qat", &py_obj::getTransform_qat, R"pbdoc(Get the object transform as a quaternion)pbdoc");

		//Working with simple box_obj 
		py::class_<box_obj, py_obj>(m, "box_obj")
			.def(py::init([](pyWorld* world, std::array<float, 3> size, std::array<int, 3> pos) {
				return std::unique_ptr<box_obj>(new box_obj(world->main, size, pos));
			}));
		m.def("create_box_obj", [](pyWorld* world, std::array<float, 3> size, std::array<int, 3> pos) { return std::unique_ptr<py_obj>(new box_obj(world->main,size,pos)); });

		
		//Working with complex_obj
		py::class_<complex_obj, py_obj>(m, "complex_obj");
			//.def(py::init<pyWorld*>())
			//.def("update_logic", &complex_obj::update_logic, R"pbdoc(Update the helicopter logic)pbdoc")
		//m.def("create_complex", [](pyWorld* arg) { return std::unique_ptr<py_obj>(new complex_obj(arg->main)); });
		

		//Working with terrain
		py::class_<terrain_obj>(m, "terrain_obj")
			.def(py::init([](pyWorld* world) {return  std::unique_ptr<terrain_obj>(new terrain_obj(world->main)); }));
		
		//Working with world
		py::class_<pyWorld>(m, "pyWorld")
			.def(py::init<>())
			.def("update", &pyWorld::update);

		#ifdef VERSION_INFO
			m.attr("__version__") = VERSION_INFO;
		#else
			m.attr("__version__") = "dev";
		#endif
	}

#endif
