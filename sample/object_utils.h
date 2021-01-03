#pragma once
#include "base_utils.h"
/*
Adding Graphic Nodes
Bullet functions

Keep Library specific functions seperate
*/

//Return scene node
IMeshSceneNode* create_node(world* world, std::array<float, 3> size);

//Load OBJ file
ISceneNode* load_obj(world* world,std::string file = "../textures/city/city.dae");

//Return btRigidBody
btRigidBody* createRigidBody(world* world, float mass, const btTransform& startTransform, btCollisionShape* shape);

//Interface for all objs
//Do not make virtual
//If not specified, override with basic stuff
//Objects will override if they need to ikr
//All objs are py objs

static enum direction { up, down, front, back, l_left, l_right, y_left, y_right, neutral };

class py_obj
{
public:

	btRigidBody* bt_body;

	static enum direction { up, down, front, back, l_left, l_right, y_left, y_right, neutral};

	void direct(direction dir);
	std::array<float, 7> getTransform_qat();
	std::string getProperties();
	void setTransform_qat(std::array<float, 7> ok);

	~py_obj() {};

	//Expose information and controls to python
	//Basic Controls(Up down left right)
	//Position get & sets
	//Data structure for python to interpret
	//Misc. Information (object specific)
};
