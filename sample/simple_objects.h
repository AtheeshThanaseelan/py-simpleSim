#pragma once
#include "base_utils.h"
#include "object_utils.h"
class box_obj //: public py_obj
{
public:
	world* obj_world;
	btRigidBody* body;
	IMeshSceneNode* irr_body;

	box_obj(world* world, float size[3], int pos[3], int mass_param);
	~box_obj();
	void forward();
	void stop();
};

class terrain_obj
{
public:
	world* obj_world;
	btRigidBody* body;
	ISceneNode* irr_planeNode;
	terrain_obj(world* world);
	~terrain_obj();
};
