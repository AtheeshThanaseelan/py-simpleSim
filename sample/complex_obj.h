#pragma once
#include "simple_objects.h"
#include "base_utils.h"

class complex_obj //: public py_obj
{
public:

	box_obj* frame;

	complex_obj(world* main_world);
	complex_obj(pyWorld* py_world);
	void update_logic();
	~complex_obj();

	void direct(direction dir);
	std::array<float, 7> getTransform_qat();
	void setTransform_qat(std::array<float, 7> ok);
	std::string getProperties();

	float pow = 0;
	float roll = 0;
	float pitch = 0;
	float yaw = 0;
	bool isPyWorld = false;
};

