#pragma once
#include <array>
#include <vector>
#include <string>
#include "../bPhysics.h"
#include "../../../interfaces/object_interface.h"
#include "../bP_obj.h"


//class worldComposite;

//enum direction { up, down, front, back, l_left, l_right, y_left, y_right, neutral };

class bPhys_box: public bP_obj
{
public:

	//btRigidBody* bt_body;
	
	bPhys_box(bPhysics* bPhys);
	//void direct(direction dir);
	//std::array<float, 7> getTransform_qat();
	//std::string getProperties();
	///void setTransform_qat(std::array<float, 7> transform_qat);
	//void update();

};
