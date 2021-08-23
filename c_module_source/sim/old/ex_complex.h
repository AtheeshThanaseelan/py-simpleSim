#pragma once
#include <array>
#include <vector>
#include <string>
#include "../bPhysics.h"
#include "../../../interfaces/object_interface.h"


class bPhys_ex_complex: public object_interface
{
public:

	btRigidBody* bt_body;
	
	bPhys_ex_complex(bPhysics* bPhys);
	void direct(direction dir);
	std::array<float, 7> getTransform_qat();
	std::string getProperties();
	void setTransform_qat(std::array<float, 7> transform_qat);
	void update();

};