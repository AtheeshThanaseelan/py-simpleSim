#pragma once
#include<stdio.h>
#include<vector>
#include <bullet/btBulletDynamicsCommon.h>
#include <irrlicht/irrlicht.h>
#include <string>
#include <iostream>
#include <array>
#include <fstream>

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

static key_controller* controller = new key_controller{};

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

	int fps;
	int time = 0;

	world(key_controller* controller);
	~world();
	void update();


	void framerate();

};

class camera 
{
public:
	camera(world* main_world);
	camera(world* main_world, IMeshSceneNode* body);
	void update();

	ICameraSceneNode* cameraNode;
	IMeshSceneNode* body = nullptr;
	world* main_world;
};

class pyWorld
{
public:
	world* main;
	pyWorld() : main(new world{ controller })
	{
		//new terrain_obj(main);
	}
	void update()
	{
		main->device->run();
		main->update();
	}
private:
};

class world_timer
{
public:
	float real_time;
	float time;
	int steps=0;
	int sub_times=1;

	//World advanced by 1/60sec, every 3 steps, time advances by 0.05sec. 

	//Advance by regular math & precise steps to account for variable step time

	world_timer(float time=0);
	void advance();
	float get_time();
};

