#pragma once
#include "base_utils.h"

class box_obj
{
public:
	world* obj_world;
	box_obj(world* world);
};

class terrain_obj
{
public:
	world* obj_world;
	terrain_obj(world* world);
};
