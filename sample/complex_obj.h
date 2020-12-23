#pragma once
#include "simple_objects.h"
#include "base_utils.h"


class complex_obj 

{
public:
	static enum direction { up, down, front, back, left, right };
	void direct(direction dir);
	complex_obj(world* main_world);
	void update_logic();
	box_obj* frame;
private:
	float pow = 0;
	float roll = 0;
	float pitch = 0;
	float yaw = 0;
};

class py_obj
{
public:
	//Expose information and controls to python
};