#pragma once
#include <array>
#include <vector>
#include <string>
#include "../bPhysics.h"
#include "../../../interfaces/object_interface.h"



//class worldComposite;

//enum direction { up, down, front, back, l_left, l_right, y_left, y_right, neutral };

class bPhys_compound: public object_interface
{
public:

	//Node pointers
	btRigidBody* main_body;
	btCollisionShape* m_wheelShape;
	btHinge2Constraint* pHingeStore[4];
	btRigidBody* pBodyB[4];
	btCompoundShape* compound;

	
	bPhys_compound(bPhysics* bPhys);
	void direct(direction dir);
	std::array<float, 7> getTransform_qat();
	std::string getProperties();
	void setTransform_qat(std::array<float, 7> transform_qat);
	void update();

};
