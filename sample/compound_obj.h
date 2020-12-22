#pragma once
#include "base_utils.h"
#include "object_utils.h"
class compound_obj : public main_obj
{
public:
	//Properties
	float wheelRadius = 0.5f;
	float wheelWidth = 0.4f;

	//Node pointers
	btRigidBody* main_body;
	ISceneNode* irr_main_body;
	btCollisionShape* m_wheelShape;
	btHinge2Constraint* pHingeStore[2];
	btRigidBody* pBodyB[2];
	ISceneNode* pNode[2];
	btCompoundShape* compound;

	//World
	world* obj_world;

	//Functions
	compound_obj(world* world);
	~compound_obj();
	void forward();
	void stop();
};