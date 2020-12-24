#pragma once
#include "simple_objects.h"
#include "base_utils.h"

class pyWorld
{
public:
	world* main;
	pyWorld() : main(new world{ controller })
	{
		new terrain_obj(main);
	}
	void update()
	{
		main->device->run();
		main->update();
	}
private:
};

class py_obj
{
public:
	static enum direction { up, down, front, back, left, right };
	virtual void direct(direction dir) = 0;

	//virtual "something" py_getTransform() = 0;
	//virtual void py_setTransform() = 0;

	virtual std::string getProperties() = 0;
	//virtual void setProperties() = 0;

	virtual ~py_obj() {};
	//Expose information and controls to python
	//Basic Controls(Up down left right)
	//Position get & sets
	//Data structure for python to interpret
	//Misc. Information (object specific)
};

class complex_obj : public py_obj
{
public:
	box_obj* frame;

	complex_obj(world* main_world);
	complex_obj(pyWorld* main_world);
	void direct(direction dir);
	void update_logic();
	//void py_setTransform() = 0;
	std::string getProperties();
	//void setProperties() = 0;
	~complex_obj();

private:
	float pow = 0;
	float roll = 0;
	float pitch = 0;
	float yaw = 0;
};

