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

void bPhys_box::direct(direction dir)
{

}

std::array<float, 7> bPhys_box::getTransform_qat()
{
    std::array<float, 7> transform_qat{};
	transform_qat[0] = bt_body->getWorldTransform().getRotation().getW();
	transform_qat[1] = bt_body->getWorldTransform().getRotation().getX();
	transform_qat[2] = bt_body->getWorldTransform().getRotation().getY();
	transform_qat[3] = bt_body->getWorldTransform().getRotation().getZ();

	transform_qat[4] = bt_body->getWorldTransform().getOrigin().getX();
	transform_qat[5] = bt_body->getWorldTransform().getOrigin().getY();
	transform_qat[6] = bt_body->getWorldTransform().getOrigin().getZ();
	return transform_qat;
}

std::string bPhys_box::getProperties()
{
    std::string prop = "im box";
    return prop;
}

void bPhys_box::setTransform_qat(std::array<float, 7> transform_qat)
{
    btQuaternion quat;
	quat.setW(transform_qat[0]);
	quat.setX(transform_qat[1]);
	quat.setY(transform_qat[2]);
	quat.setZ(transform_qat[3]);

	btVector3 origin;
	origin.setX(transform_qat[4]);
	origin.setY(transform_qat[5]);
	origin.setZ(transform_qat[6]);

	btTransform trans;
	trans.setRotation(quat);
	trans.setOrigin(origin);

	bt_body->setWorldTransform(trans);
}

void bPhys_box::update()
{

}