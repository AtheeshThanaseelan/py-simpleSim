#pragma once
#include "base_utils.h"
#include "object_utils.h"
class box_obj : public py_obj
{
public:
	world* obj_world;
	btRigidBody* bt_body;
	IMeshSceneNode* irr_body;

	box_obj(world* world, std::array<float, 3> size, std::array<int, 3> pos = { 1,1,1 }, int mass_param = 1);
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
