#pragma once
#include <array>
#include <vector>
#include <string>
#include "../bPhysics.h"
#include "../../../interfaces/object_interface.h"



//class worldComposite;

//enum direction { up, down, front, back, l_left, l_right, y_left, y_right, neutral };

class bPhys_ground: public object_interface
{
public:

	btRigidBody* bt_body;
	
	bPhys_ground(bPhysics* bPhys);
	void direct(direction dir);
	std::array<float, 7> getTransform_qat();
	std::string getProperties();
	void setTransform_qat(std::array<float, 7> transform_qat);
	void update();

};
