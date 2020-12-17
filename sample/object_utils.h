#pragma once
#include "base_utils.h"
/*
Adding Graphic Nodes
Bullet functions

Keep Library specific functions seperate
*/

//Return scene node
IMeshSceneNode* create_node(world* world, int size[3]);

//Return btRigidBody
btRigidBody* createRigidBody(world* world, float mass, const btTransform& startTransform, btCollisionShape* shape);