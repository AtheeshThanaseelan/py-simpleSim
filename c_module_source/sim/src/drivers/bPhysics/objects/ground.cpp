#include "../bPhysics.h"
#include "ground.h"
#include <array>
#include <string>

bPhys_ground::bPhys_ground(bPhysics* bPhys)
{
	//Make plane
	std::array<float, 3> size{ 0,1,0 };
	std::array<int, 3> pos{ 0,-5,0 };
	int mass_param = 0;
	btCollisionShape* colShape = new btStaticPlaneShape(btVector3(size[0], size[1], size[2]), 0);
	bPhys->collisionShapes.push_back(colShape);
	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();

	btScalar mass(mass_param * 1.f);

	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(pos[0], pos[1], pos[2]));

	bt_body = bPhys->createRigidBody(mass, startTransform, colShape);
	bt_body->setFriction(10000);
}

void bPhys_ground::direct(direction dir)
{

}

std::array<float, 7> bPhys_ground::getTransform_qat()
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

std::string bPhys_ground::getProperties()
{
    std::string prop = "im box";
    return prop;
}

void bPhys_ground::setTransform_qat(std::array<float, 7> transform_qat)
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

void bPhys_ground::update()
{

}