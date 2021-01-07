
//#include "base_utils.h"
//#include <vector>
/*
#include "simple_objects.h"
#include "compound_obj.h"
#include "complex_obj.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "serializer.h"


namespace py = pybind11;
*/

#include <bullet/btBulletDynamicsCommon.h>
#include <irrlicht/irrlicht.h>
#include <iostream>
#include <fstream>
#include <array>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//Naming Scheme
/*
* Private: m_ 
* Interfaces/Controllers like py_obj, etc: control_
*/

//Outline
/*
* Modules: expose an common api regardless of library used
*	Input
*	Graphics
*	Physics
*	Timer(in simulation as well as realtime)
* 
* Composites:
*	Simple: Simulate only physics, and have a graphical representation
*	Complex: Simulate "simple", as well as logical variables such as air density, etc.
*	Independant: Allow computer generated input
*	
* Objects:
*	Simple: Exists with only physical properties
*	Complex: Must take complex properties into account each update
* 
*/

class inp : public IEventReceiver
{
public:

	bool KeyIsDown[KEY_KEY_CODES_COUNT];

	bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}
	/*
	void clear(EKEY_CODE keyCode)
	{
		KeyIsDown[keyCode] = false;
	}
	*/

	inp()
	{
		for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}
};

class gfx
{
public:
	IrrlichtDevice* device;
	IVideoDriver* driver;
	ISceneManager* scenemgr;

	gfx(IEventReceiver* ok)
	{
		device = createDevice(video::EDT_OPENGL,
			dimension2d<u32>(800, 600), 32, false, false, true, ok);
		driver = device->getVideoDriver();
		scenemgr = device->getSceneManager();
		//guienv = device->getGUIEnvironment();
		device->setWindowCaption(L"Sample Program");
		//env = device->getGUIEnvironment();
		
		ICameraSceneNode* cameraNode;
		cameraNode = scenemgr->addCameraSceneNodeFPS(NULL, 20.0f, 0.02f);
		cameraNode->setPosition(vector3df(0, 10, -70));
		
	}

	~gfx()
	{
		device->closeDevice();
		device->run();
		device->drop();
		//delete device;
	}

	void update()
	{
		driver->beginScene(true, true, video::SColor(180, 0, 0, 255));
		scenemgr->drawAll();
		driver->endScene();
	}
};



//Motionstate
class physics 
{
public:
	btBroadphaseInterface* overlappingPairCache;
	btCollisionDispatcher* dispatcher;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btSequentialImpulseConstraintSolver* solver;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	physics()
	{
		///--- World Creation
		///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
		collisionConfiguration = new btDefaultCollisionConfiguration();

		///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
		dispatcher = new btCollisionDispatcher(collisionConfiguration);

		///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		overlappingPairCache = new btDbvtBroadphase();

		///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
		solver = new btSequentialImpulseConstraintSolver;

		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

		dynamicsWorld->setGravity(btVector3(0, -10, 0));
	}
	~physics()
	{
		for (int count = dynamicsWorld->getNumCollisionObjects() - 1; count >= 0; count--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[count];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				delete body->getMotionState();
			}
			dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}
		for (int count = 0; count < collisionShapes.size(); count++)
		{
			btCollisionShape* shape = collisionShapes[count];
			collisionShapes[count] = 0;
			delete shape;
		}
		delete dynamicsWorld;
		delete solver;
		delete overlappingPairCache;
		delete dispatcher;
		delete collisionConfiguration;
	}
	void update()
	{
		const f32 frameDeltaTime = (f32)(1.f / 60.f);
		dynamicsWorld->stepSimulation(frameDeltaTime, 2);
	}
	
	btRigidBody* createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape)
	{
		btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			shape->calculateLocalInertia(mass, localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

		btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);

		btRigidBody* body = new btRigidBody(cInfo);
		//body->setContactProcessingThreshold(m_defaultContactProcessingThreshold);

		body->setUserIndex(-1);
		dynamicsWorld->addRigidBody(body);
		return body;
	}
	
	btRigidBody* addBox(std::array<float, 3> size, std::array<int, 3> pos, int mass_param)
	{
		btCollisionShape* colShape = new btBoxShape(btVector3(size[0], size[1], size[2]));
		collisionShapes.push_back(colShape);
		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar mass(mass_param * 1.f);

		startTransform.setIdentity();
		startTransform.setOrigin(btVector3(pos[0], pos[1], pos[2]));

		 return createRigidBody(mass, startTransform, colShape);
	}
};


class irr_box
{
public:
	gfx* m_gEngine;
	ISceneNode* m_box;

	irr_box(gfx* gEngine) :m_gEngine{ gEngine }
	{
		std::array<float, 3> size = { 1,1,1 };
		IMeshSceneNode* cubeNode = gEngine->scenemgr->addCubeSceneNode(1.0f, 0, 0, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(size[0] * 2, size[1] * 2, size[2] * 2));
		cubeNode->setMaterialType(EMT_SOLID);
		cubeNode->setMaterialTexture(0, gEngine->driver->getTexture("../textures/box.jpg"));
		cubeNode->setMaterialFlag(video::EMF_LIGHTING, false);
		cubeNode->setVisible(true);
		m_box = cubeNode;
	}

	void setTrans(std::array<float,7> trans)
	{
		quaternion q(trans[3], trans[4], trans[5], trans[6]);
		vector3df Euler;
		q.toEuler(Euler);
		Euler *= RADTODEG;

		m_box->setPosition(vector3df(trans[0], trans[1], trans[2]));
		m_box->setRotation(Euler);
		m_box->setVisible(true);
	}
};

class b_box 
{
public:
	btRigidBody* m_pBody;
	physics* m_pEngine;
	b_box(physics* pEngine): m_pEngine{pEngine}
	{
		int mass_param = 1;

		btCollisionShape* colShape = new btBoxShape(btVector3(size[0], size[1], size[2]));
		pEngine->collisionShapes.push_back(colShape);
		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar mass(mass_param * 1.f);

		startTransform.setIdentity();
		startTransform.setOrigin(btVector3(pos[0], pos[1], pos[2]));

		bt_body = createRigidBody(world, mass, startTransform, colShape);
	}
};

class box 
{
public:

};

void test1()
{
	inp* controller = new inp();
	IEventReceiver* control = controller;
	gfx* screen = new gfx(control);
	//irr_box* box = new irr_box(screen->addBox());
	irr_box* box = new irr_box(screen);
	while (screen->device->run())
	{
		screen->update();
		if (controller->IsKeyDown(KEY_KEY_A))
		{
			std::array <float, 7> trans{ {1,1,1,1,1,1,1} };
			box->setTrans(trans);
		}

		if (controller->IsKeyDown(KEY_KEY_D))
		{
			std::array <float, 7> trans{ {0,0,0,10,0,0,1} };
			box->setTrans(trans);
		}
	}
	delete screen;
	delete control;

	//Generics vs Library Specifics
		//Generics only work with standard C++ data
		//Library specifics must not interact closely with engine

	//Translators
		//Take in library specifics and export C++ standards
		//Box
			//Irrlicht
				//Input and save graphics engine
				//Export setter
			//Bullet
				//Input and save physics engine
				//Export setters and getters
			//Composite
				//Holds Irrlicht and Bullet boxes
				//Update both together
				//Export setters and getters
	
	//Translator Use
		//Downcast and initialize using engine
		//Upcast back to box and use
		//^this is dumb

		//Downcast and initlize engine
		//Upcase back to engine and use
		//Use template to make boxes
			//Engine provides methods to abstract to standard C++

	//Object Hierarchy
		//GFX object can only be updated 
		//Physics Engine can be set and updated
		//Complex Engine affects how gfx and physics are updated


	//Update Object needs gfx, physics and properties
		//Hold all pointers in object, and update all at once
			//More memory use?
			//More shallow object heirachy
			//Loop for all updates

	//Binary Serialization
		//Useful for serializing all properties of external libraries with low complexity
		//Must manage link between objects somehow
}

void test2()
{
	gfx* test;
	std::fstream myFile("gfx.bin", std::ios::in | std::ios::binary);
	myFile.read((char*)&test, sizeof(test));
	/*
	btCollisionObject* obj = sim->dynamicsWorld->getCollisionObjectArray()[0];
	btRigidBody* body = btRigidBody::upcast(obj);
	std::cout << body->getWorldTransform().getOrigin().getY();
	*/
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
			case 2:
				test2();
				break;
/*
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
