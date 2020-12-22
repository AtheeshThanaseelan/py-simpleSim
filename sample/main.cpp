#include "base_utils.h"
#include "simple_objects.h"
#include "bullet_example_files/wheel_obj.h"
#include "compound_obj.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

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

void incr(key_controller* controller,EKEY_CODE button,float* var,float mult=10,float lim=0.5)
{

	if((*var*(mult /abs(mult)))<lim)
		*var += 0.01f*mult;
	controller->clear(button);
}

btVector3 relativeForce(float force, btRigidBody* body)
{
	btVector3 f(0, 0, force);
	btTransform boxTrans;
	boxTrans.setIdentity();
	body->getMotionState()->getWorldTransform(boxTrans);
	btVector3 correctedForce = (boxTrans * f) - boxTrans.getOrigin();
	return correctedForce;
}

btVector3 relativePos(btVector3 pos, btRigidBody* body)
{
	btTransform boxTrans;
	boxTrans.setIdentity();
	body->getMotionState()->getWorldTransform(boxTrans);
	btVector3 relativePos = pos - boxTrans.getOrigin();
	return relativePos;
}

//Box and Terrain Test
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

//Wheel and Constraint Test
void test2() 
{
	key_controller* controller = new key_controller{};
	world* main_world = new world{ controller };
	main_obj* hg = new compound_obj{ main_world };
	terrain_obj* terr = new terrain_obj{ main_world };

	while (main_world->device->run() && main_world->driver)
	{
		main_world->update();
		main_world->framerate();
		if (controller->IsKeyDown(KEY_KEY_W))
		{
			if (hg != nullptr)
				hg->forward();

		}
		if (hg != nullptr && !controller->IsKeyDown(KEY_KEY_W))
		{
			hg->stop();
			controller->clear(KEY_KEY_W);
		}
	}
	delete terr;
	delete hg;
	delete main_world;
	delete controller;
}

//Camera Test
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

//Memory Leak Test
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

//OBJ load test
void test5()
{
	key_controller* controller = new key_controller{};
	world* main_world = new world{ controller };
	//load_obj(main_world);
	load_obj(main_world, "../textures/city/obj2.dae");
	//create_node(main_world, new int[] { 3,3,3 });



	while (main_world->device->run() && main_world->driver)
	{
		main_world->update();
		main_world->device->run();
		main_world->framerate();
	}
}

//Logical Object Test
void test6()
{
	//Helicopter
	//Helicopter is lifted by force on rotor
	//Rotor force is relative to collective and engine rpm
	//engine rpm depends on environment(air density, load, etc)
	//update logic along with world

	key_controller* controller = new key_controller{};
	world* main_world = new world{ controller };
	box_obj* heli = new box_obj{ main_world,new int[] {3,3,3},new int[] {0,0,10},1 };
	new terrain_obj(main_world);

	float pow = 1;
	float roll = 0;
	float pitch = 0;
	float yaw = 0;
	while (main_world->device->run() && main_world->driver)
	{
		main_world->update();
		main_world->framerate();
		/*
		{
			if (controller->IsKeyDown(KEY_KEY_P))
				incr(controller, KEY_KEY_P, &pow, 100.f,11.f);
			if (controller->IsKeyDown(KEY_KEY_L))
				incr(controller, KEY_KEY_L, &pow, -100.f,0);
			
			if (controller->IsKeyDown(KEY_KEY_W))
				incr(controller, KEY_KEY_W, &pitch);
			if (controller->IsKeyDown(KEY_KEY_S))
				incr(controller, KEY_KEY_S, &pitch, -10,0.5f);

			if (controller->IsKeyDown(KEY_KEY_A))
				incr(controller, KEY_KEY_A, &roll);
			if (controller->IsKeyDown(KEY_KEY_D))
				incr(controller, KEY_KEY_D, &roll, -10, 0.5f);

			if (controller->IsKeyDown(KEY_KEY_Q))
				incr(controller, KEY_KEY_Q, &yaw);
			if (controller->IsKeyDown(KEY_KEY_E))
				incr(controller, KEY_KEY_E, &yaw, -10, 0.5f);
			
		}
		*/
		heli->body->setGravity(btVector3(0,0,0));
		heli->body->setActivationState(DISABLE_DEACTIVATION);
		
		//Upwards Thrust
		{
			//heli->body->setAngularVelocity(btVector3(0, 0, 1));
			//heli->body->applyCentralForce(relativeForce(10,heli->body));
			heli->body->applyForce(relativeForce(10,heli->body),btVector3(0,0,0));
		}
		/*
		//Roll
		{
			btVector3 f = relativeForce(roll, heli->body);
			btVector3 rotor(0, 7, 4);
			btVector3 rotor2(0, 7, -4);
			heli->body->applyForce(f, rotor);
			heli->body->applyForce(-f, rotor2);
		}
		//Yaw
		{
			btVector3 f = relativeForce(yaw, heli->body);
			btVector3 rotor(-8, 0, 0);
			heli->body->applyForce(f, rotor);
		}
		//Pitch
		{
			btVector3 f = relativeForce(pitch, heli->body);
			btVector3 rotor(-7, 7, 0);
			btVector3 rotor2(7, 7, 0);
			heli->body->applyForce(f, rotor);
			heli->body->applyForce(-f, rotor2);
		}
		*/
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

			}
		} while (choice != 0);

		return 0;
	}


#else
	PYBIND11_MODULE(sample, m) {
		m.def("test1", &test1, R"pbdoc(
			Launch the python test
		)pbdoc");

	#ifdef VERSION_INFO
		m.attr("__version__") = VERSION_INFO;
	#else
		m.attr("__version__") = "dev";
	#endif
	}

#endif
