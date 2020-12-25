#pragma once
#include "base_utils.h"
/*
Adding Graphic Nodes
Bullet functions

Keep Library specific functions seperate
*/

//Return scene node
IMeshSceneNode* create_node(world* world, int size[3]);

//Load OBJ file
ISceneNode* load_obj(world* world,std::string file = "../textures/city/city.dae");

//Return btRigidBody
btRigidBody* createRigidBody(world* world, float mass, const btTransform& startTransform, btCollisionShape* shape);


class py_obj
{
public:
	static enum direction { up, down, front, back, l_left, l_right, y_left, y_right, neutral};
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
