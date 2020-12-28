#include "base_utils.h"

//Key Controller
bool key_controller::OnEvent(const SEvent& event)
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;
}

bool key_controller::IsKeyDown(EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

void key_controller::clear(EKEY_CODE keyCode)
{
	KeyIsDown[keyCode] = false;
}

key_controller::key_controller()
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}



//World
world::world(key_controller* controller) 
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

	///-----initialization_end-----

	device = createDevice(video::EDT_OPENGL,
		dimension2d<u32>(800, 600), 32, false, false, true, controller);
	driver = device->getVideoDriver();
	scenemgr = device->getSceneManager();
	//guienv = device->getGUIEnvironment();
	device->setWindowCaption(L"Sample Program");
	//env = device->getGUIEnvironment();

	ICameraSceneNode* cameraNode;
	cameraNode = scenemgr->addCameraSceneNodeFPS(NULL, 20.0f, 0.02f);
	cameraNode->setPosition(vector3df(0, 10, -70));

	//then = device->getTimer()->getTime();
	fps = driver->getFPS();
}

world::~world()
{
	
	device->closeDevice();
	delete device;
	for (int count = dynamicsWorld->getNumCollisionObjects() - 1; count>=0; count--)
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

void world::update()
{
	int numOfObjects = dynamicsWorld->getNumCollisionObjects();
	for (int j = numOfObjects - 1; j >= 0; j--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;

		body->getMotionState()->getWorldTransform(trans);
		ISceneNode* cube = reinterpret_cast<ISceneNode*>(body->getUserPointer());
		if (cube != NULL) {//update cubes only
			btVector3 origin = trans.getOrigin();
			//update rotation
			btQuaternion rot = trans.getRotation();
			quaternion q(rot.getX(), rot.getY(), rot.getZ(), rot.getW());
			vector3df Euler;
			q.toEuler(Euler);
			Euler *= RADTODEG;

			cube->setPosition(vector3df(origin.getX(), origin.getY(), origin.getZ()));
			cube->setRotation(Euler);
			cube->setVisible(true);
		}
	}

	driver->beginScene(true, true, video::SColor(180,0, 0, 255));
	scenemgr->drawAll();
	driver->endScene();

	const f32 frameDeltaTime = (f32)(1.f / 60.f);
	dynamicsWorld->stepSimulation(frameDeltaTime, 2);
}

void world::framerate()
{
	if (fps != driver->getFPS())
	{
		fps = driver->getFPS();
		stringw titlebar;
		titlebar += "] FPS:";
		titlebar += fps;
		device->setWindowCaption(titlebar.c_str());
	}
}



//Camera
camera::camera(world* main_world):main_world{main_world}
{

	cameraNode = main_world->scenemgr->addCameraSceneNodeFPS();

}

camera::camera(world* main_world, IMeshSceneNode* body) : body{ body }, main_world{ main_world }
{
	cameraNode = main_world->scenemgr->addCameraSceneNode();
	body->addChild(cameraNode);
	cameraNode->setFOV(0.78f);
	cameraNode->setPosition(vector3df(-10, 5, 0));
}

void camera::update()
{	
	if(body!=nullptr)
	cameraNode->setTarget(body->getAbsolutePosition());
}



//Clock
world_timer::world_timer(float time) :time{ time }, real_time{time} {}

void world_timer::advance()
{
	steps++;
	if (sub_times >= 3)
	{
		sub_times = 1;
		time += 0.05;
	}
	else
	{
		sub_times++;
	}
	real_time += 1.f / 60.f;
}
float world_timer::get_time()
{
	return real_time;
}