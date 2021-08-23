#include "../bPhysics.h"
#include "box.h"
#include <array>
#include <string>

bPhys_box::bPhys_box(bPhysics* bPhys)
{
    float mass_param = 10;
    float pos[3] = {0,0,0};
    float size[3] = {1,1,1};

    btCollisionShape* colShape = new btBoxShape(btVector3(size[0], size[1], size[2]));
	bPhys->collisionShapes.push_back(colShape);
	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();

	btScalar mass(mass_param * 1.f);

	startTransform.setIdentity(); 
	startTransform.setOrigin(btVector3(pos[0], pos[1], pos[2]));

	bt_body = bPhys->createRigidBody(mass, startTransform, colShape);

	//Been causing problems
	bt_body->setActivationState(DISABLE_DEACTIVATION);

	//return bt_body;
}