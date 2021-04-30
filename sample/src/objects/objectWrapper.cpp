#include "objectWrapper.h"
#include <iostream>
#include <array>
#include <vector>

objExport::objExport(btRigidBody* bt_body, IMeshSceneNode* irr_body) : bt_body{ bt_body }, irr_body{ irr_body }{}

objExport::objExport(btRigidBody* bt_body) : bt_body{ bt_body }
{
	irr_body = nullptr;
}

void objExport::direct(direction dir)
{
	std::cout << "Object is static" << std::endl;
}

std::array<float, 7> objExport::getTransform_qat()
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

std::string objExport::getProperties()
{
	std::string empty = "Not Complex";
	return empty;
}

void objExport::setTransform_qat(std::array<float, 7> transform_qat)
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

void objExport::update()
{
	//btVector3 origin = bt_body->getWorldTransform().getOrigin();
	//update rotation
	//btQuaternion rot = bt_body->getWorldTransform().getRotation();
	//quaternion q(rot.getX(), rot.getY(), rot.getZ(), rot.getW());
	//vector3df Euler;
	//q.toEuler(Euler);
	//Euler *= RADTODEG;

	//irr_body->setPosition(vector3df(origin.getX(), origin.getY(), origin.getZ()));
	//irr_body->setRotation(Euler);
	//irr_body->setVisible(true);
}
