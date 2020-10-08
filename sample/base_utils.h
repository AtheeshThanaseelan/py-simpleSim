#pragma once
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
	virtual bool OnEvent(const SEvent& event);

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;

	virtual void clear(EKEY_CODE keyCode);


	key_controller();
private:
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

	world(key_controller* controller);

	void update();


	void framerate();


};