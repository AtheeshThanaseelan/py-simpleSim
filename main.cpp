#include<stdio.h>
#include<vector>
#include <bullet/btBulletDynamicsCommon.h>
#include <irrlicht/irrlicht.h>
#include <string>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;



class key_controller : public IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	virtual void clear(EKEY_CODE keyCode)
	{
		KeyIsDown[keyCode] = false;
	}

	key_controller()
	{
		for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

class world 
{
public:
	btBroadphaseInterface* overlappingPairCache;
	btCollisionDispatcher* dispatcher;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btSequentialImpulseConstraintSolver* solver;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	IrrlichtDevice* device;
	IVideoDriver* driver;
	ISceneManager* scenemgr;
	IGUIEnvironment* guienv;
	IGUIEnvironment* env;

	u32 then;
	int fps;

	world(key_controller* controller)
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

	void updateObjs()
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
	}

	void createTerrain()
	{
		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(150.), btScalar(1.), btScalar(150.)));

		collisionShapes.push_back(groundShape);

		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, -56, 0));

		btScalar mass(0.);

		btVector3 localInertia(0, 0, 0);

		btAssert((!groundShape || groundShape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		if (isDynamic)
			groundShape->calculateLocalInertia(mass, localInertia);

		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);

		btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, groundShape, localInertia);

		btRigidBody* body = new btRigidBody(cInfo);
		//body->setContactProcessingThreshold(m_defaultContactProcessingThreshold);

		body->setUserIndex(-1);
		dynamicsWorld->addRigidBody(body);

		body->setUserIndex(5);
		body->setFriction(1);

		//add the body to the dynamics world
		dynamicsWorld->addRigidBody(body);

		IAnimatedMesh* hillPlaneMesh = scenemgr->addHillPlaneMesh("myHill",
			core::dimension2d<f32>(30, 30),
			core::dimension2d<u32>(10, 10), 0, 0,
			core::dimension2d<f32>(0, 0),
			core::dimension2d<f32>(10, 10));
		ISceneNode* planeNode = scenemgr->addAnimatedMeshSceneNode(hillPlaneMesh);
		planeNode->setMaterialTexture(0, driver->getTexture("../textures/ground.jpg"));
		planeNode->setMaterialFlag(video::EMF_LIGHTING, false);
		planeNode->setPosition(core::vector3df(0, -55, 0));

	}
	
	void update()
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

		if((frameDeltaTime * 1000)<25)
			device->sleep(25-(frameDeltaTime*1000));

		then = now;
	}

	void framerate()
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

};

key_controller controller;
world newWorld{ &controller };

class obj
{
public:
	obj(world* world)
	{
		btCollisionShape* colShape = new btBoxShape(btVector3(5, 5, 5));
		world->collisionShapes.push_back(colShape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar mass(3.f);

		startTransform.setOrigin(btVector3(10, 40, 20));
		btQuaternion quat(btVector3(0.4, .02, .1), 67);
		startTransform.setRotation(quat);


		btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		colShape->calculateLocalInertia(mass, localInertia);

		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

		btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, colShape, localInertia);

		btRigidBody* body = new btRigidBody(cInfo);
		body->setFriction(1);
		body->setUserIndex(10);
		world->dynamicsWorld->addRigidBody(body);

		IMeshSceneNode* cubeNode = world->scenemgr->addCubeSceneNode(10.0f, NULL, -1, vector3df(0, 3, 10));
		cubeNode->setMaterialType(EMT_SOLID);
		cubeNode->setMaterialTexture(0, world->driver->getTexture("../textures/box.jpg"));
		cubeNode->setMaterialFlag(video::EMF_LIGHTING, false);
		cubeNode->setVisible(true);
		//saving the visual node to the physics node  
		body->setUserPointer(cubeNode);
	}
};
/*
class boxObj 
{
public:
	int obj_num;
	static world* in_world;
	//static std::vector<*boxObj> boxes;

	boxObj(world* world)
	{
		in_world = world;
		btCollisionShape* colShape = new btBoxShape(btVector3(5, 5, 5));
		world -> collisionShapes.push_back(colShape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar mass(3.f);

		startTransform.setOrigin(btVector3(10, 40, 20));
		btQuaternion quat(btVector3(0.4, .02, .1), 67);
		startTransform.setRotation(quat);


		btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		colShape->calculateLocalInertia(mass, localInertia);

		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

		btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, colShape, localInertia);

		btRigidBody* body = new btRigidBody(cInfo);
		body->setFriction(1);
		body->setUserIndex(10);
		world->dynamicsWorld->addRigidBody(body);

		IMeshSceneNode* cubeNode = world->scenemgr->addCubeSceneNode(10.0f, NULL, -1, vector3df(0, 3, 10));
		cubeNode->setMaterialType(EMT_SOLID);
		cubeNode->setMaterialTexture(0, world->driver->getTexture("../textures/box.jpg"));
		cubeNode->setMaterialFlag(video::EMF_LIGHTING, false);
		cubeNode->setVisible(true);
		//saving the visual node to the physics node  
		body->setUserPointer(cubeNode);
	}
	
	~boxObj()
	{
		btCollisionObject* obj = in_world->dynamicsWorld->getCollisionObjectArray()[obj_num];
		btRigidBody* body = btRigidBody::upcast(obj);
		ISceneNode* cube = reinterpret_cast<ISceneNode*>(body->getUserPointer());
		cube->setVisible(false);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		in_world->dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}
};
world* boxObj::in_world = &newWorld;
*/


int main() 
{
	newWorld.createTerrain();

	printf("\n<--im my own shoe-->\n ");

	while (newWorld.device->run() && newWorld.driver)
	{
		newWorld.update();
		newWorld.framerate();
		if (controller.IsKeyDown(KEY_KEY_Q))
		{
			controller.clear(KEY_KEY_Q);
		}
		if (controller.IsKeyDown(KEY_KEY_E))
		{
			//new boxObj(&newWorld);
			controller.clear(KEY_KEY_E);
		}
		if (controller.IsKeyDown(KEY_KEY_A))
		{
			controller.clear(KEY_KEY_A);
		}
		if (controller.IsKeyDown(KEY_KEY_D))
		{
			controller.clear(KEY_KEY_D);
		}

	}
	return 0;
}
