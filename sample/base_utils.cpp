#include "base_utils.h"

//Key Controller
bool key_controller::OnEvent(const SEvent& event)
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;
}

// This is used to check whether a key is being held down
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

	printf("World Made\n\n");

	///-----initialization_end-----

	device = createDevice(video::EDT_OPENGL,
		dimension2d<u32>(800, 600), 32, false, false, false, controller);
	driver = device->getVideoDriver();
	scenemgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	device->setWindowCaption(L"Sample Program");
	env = device->getGUIEnvironment();

	ICameraSceneNode* cameraNode;
	cameraNode = scenemgr->addCameraSceneNodeFPS(NULL, 20.0f, 0.02f);
	cameraNode->setPosition(vector3df(0, 10, -70));

	then = device->getTimer()->getTime();
	fps = driver->getFPS();
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

	const u32 now = device->getTimer()->getTime();

	const f32 frameDeltaTime = (f32)(now - then) / 1000.f;

	driver->beginScene(true, true, video::SColor(255, 0, 0, 255));
	scenemgr->drawAll();
	guienv->drawAll();
	driver->endScene();

	dynamicsWorld->stepSimulation(frameDeltaTime * 2, 10);

	if ((frameDeltaTime * 1000) < 25)
		device->sleep(25 - (frameDeltaTime * 1000));

	then = now;
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