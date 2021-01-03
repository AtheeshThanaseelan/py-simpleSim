#pragma once
#include "base_utils.h"
#include "object_utils.h"
class compound_obj //: public py_obj
{
public:

	//Node pointers
	btRigidBody* main_body;
	IMeshSceneNode* irr_main_body;
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

	//py obj
	void direct(direction dir);
	std::array<float, 7> getTransform_qat();
	void setTransform_qat(std::array<float, 7> ok);
	std::string getProperties();
};