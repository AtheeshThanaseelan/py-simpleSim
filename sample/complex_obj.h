#pragma once
#include "simple_objects.h"
#include "base_utils.h"

class complex_obj : public py_obj
{
public:
	box_obj* frame;

	complex_obj(world* main_world);
	complex_obj(pyWorld* py_world);
	void direct(direction dir);
	void update_logic();
	//void py_setTransform() = 0;
	float* getTransform_qat();
	std::string getProperties();
	//void setProperties() = 0;
	~complex_obj();

	float pow = 0;
	float roll = 0;
	float pitch = 0;
	float yaw = 0;
	bool isPyWorld = false;
};

