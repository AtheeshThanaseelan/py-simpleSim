#pragma once
#include "base_utils.h"
#include "object_utils.h"
class box_obj : public main_obj
{
public:
	world* obj_world;
	btRigidBody* body;
	IMeshSceneNode* irr_body;

	box_obj(world* world, int size[3], int pos[3], int mass_param);
	void forward();
	void stop();
};

class terrain_obj
{
public:
	world* obj_world;
	terrain_obj(world* world);
};
