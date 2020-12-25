#include "base_utils.h"
#include "simple_objects.h"
#include "compound_obj.h"
#include "complex_obj.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

/*Controllers

Python Object Controller:
Interface for python to direct and obtain statistics on objects in the world (create object, find position)

Python World Controller:
Interface for python to direct and obtain statistics on objects on the world (create wind, determine "weather")

Logic Controller:
Controls all objects > has them in objects
Move objects
Calculate any logic for world

*/

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

//Visualization tools
void test7()
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
			std::cout << heli->frame->body->getWorldTransform().getRotation().getW() << std::endl;
			std::cout << heli->frame->body->getWorldTransform().getRotation().getX() << std::endl;
			std::cout << heli->frame->body->getWorldTransform().getRotation().getY() << std::endl;
			std::cout << heli->frame->body->getWorldTransform().getRotation().getZ() << std::endl;
			std::cout << heli->frame->body->getWorldTransform().getOrigin().getX() << std::endl;
			std::cout << heli->frame->body->getWorldTransform().getOrigin().getY() << std::endl;
			std::cout << heli->frame->body->getWorldTransform().getOrigin().getZ() << std::endl;
			std::cout << heli->getProperties() << std::endl;
			system("cls");
		}

	}
	delete main_world;
	delete controller;
}

//Python Paramter Import Test

#if defined _DEBUG
	int main()
	{
		int choice;
		do {
			printf("Choose test, 0 to exit: ");
			std::cin >> choice;
			switch (choice)
			{
			case 7:
				test7();
				break;
			/*
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
			case 5:
				test5();
				break;
			case 6:
				test6();
				break;
			*/
			}
		} while (choice != 0);

		return 0;
	}


#else
	PYBIND11_MODULE(sample, m) 
	{

		py::class_<py_obj>(m, "py_obj");

		//Working with complex_obj
		py::class_<complex_obj, py_obj>(m, "complex_obj")
			.def(py::init<pyWorld*>())
			.def("update_logic", &complex_obj::update_logic, R"pbdoc(Update the helicopter logic)pbdoc")
			.def("getProperties", &complex_obj::getProperties, R"pbdoc(Get the helicopter properties)pbdoc");
			//.def("remove_heli", &complex_obj::~complex_obj)
		m.def("create_heli", [](pyWorld* arg) { return std::unique_ptr<py_obj>(new complex_obj(arg)); });

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
