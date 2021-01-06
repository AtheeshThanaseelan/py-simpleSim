
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

	// This is the one method that we have to implement
	bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	// This is used to check whether a key is being held down
	bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	void clear(EKEY_CODE keyCode)
	{
		KeyIsDown[keyCode] = false;
	}

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
	
	std::array<ICameraSceneNode*, 5> cameras;

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
		device->drop();
		delete device;
	}

	void addCamera()
	{
		ICameraSceneNode* cameraNode;
		cameraNode = scenemgr->addCameraSceneNodeFPS(NULL, 20.0f, 0.02f);
		cameraNode->setPosition(vector3df(0, 10, -70));
		cameras[0] = cameraNode;
	}

	void setCamera()
	{
		ICameraSceneNode* cameraNode = cameras[0];
		scenemgr->setActiveCamera(cameraNode);
	}

	void update()
	{
		/*
		fps = driver->getFPS();
		stringw titlebar;
		titlebar += "] FPS:";
		titlebar += fps;
		device->setWindowCaption(titlebar.c_str());
		*/
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

void test1()
{
	IEventReceiver* control = new inp();
	gfx* screen = new gfx(control);
	physics* sim = new physics();
	std::array<float, 3> size = { 1,1,1 };
	std::array<int, 3> pos = { 10,10,10 };
	sim->addBox(size, pos, 0);


	std::ofstream myFile("data.bin", std::ios::out | std::ios::binary);
	myFile.write((char*)&sim, sizeof(sim));

	//Update Object needs gfx, physics and properties
		//Hold all pointers in object, and update all at once
			//More memory use?
			//More shallow object heirachy
			//Loop for all updates
		//User pointer on physics object hold gfx rep
			//Update phys+gfx, then loop again for complex object
		//User pointer can also hold entire object for looping through
			//No need for multiple loops
			//Must use bullet collision object array
			//All objects need physical representation

}

void test2()
{
	physics* sim;
	std::fstream myFile("data.bin", std::ios::in | std::ios::binary);
	myFile.read((char*)&sim, sizeof(sim));

	btCollisionObject* obj = sim->dynamicsWorld->getCollisionObjectArray()[0];
	btRigidBody* body = btRigidBody::upcast(obj);
	std::cout << body->getWorldTransform().getOrigin().getY();
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
