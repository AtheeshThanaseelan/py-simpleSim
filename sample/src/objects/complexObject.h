#pragma once
#include "objectWrapper.h"
class complex_obj : public objExport
{
public:

	complex_obj(btRigidBody* bt_body, IMeshSceneNode* irr_body);

	void update();

	void direct(direction dir);
	std::string getProperties();

	float pow = 0;
	float roll = 0;
	float pitch = 0;
	float yaw = 0;
	bool isPyWorld = false;
};

