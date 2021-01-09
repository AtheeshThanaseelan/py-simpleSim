#pragma once
#include "../external/bPhysics.h"
#include "../external/irrlicht.h"
#include "objectWrapper.h"
#include "../utility/utilities.h"

class compound_obj : public objExport
{
public:

	//Node pointers
	btRigidBody* main_body;
	IMeshSceneNode* irr_main_body;
	btCollisionShape* m_wheelShape;
	btHinge2Constraint* pHingeStore[4];
	btRigidBody* pBodyB[4];
	ISceneNode* pNode[4];
	btCompoundShape* compound;

	//Functions
	compound_obj(worldComposite* world);
	void update();
	void direct(direction dir);
	~compound_obj();

};