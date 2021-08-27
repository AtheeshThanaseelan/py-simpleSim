float applied_power = 0;
float roll = 0;
float pitch = 0;
float yaw = 0;
bool isPyWorld = false;

#include "ex_complex.h"
#include <iostream>
#include "../bPhysics.h"

bPhys_ex_complex::bPhys_ex_complex(bPhysics* bPhys)
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

void incr(float* var, float mult = 10, float lim = 0.5)
{

	if ((*var * (mult / abs(mult))) < lim)
		*var += 0.01f * mult;
}

btVector3 relativeForce(btVector3 f, btRigidBody* body)
{
	btTransform boxTrans;
	boxTrans.setIdentity();
	body->getMotionState()->getWorldTransform(boxTrans);
	btVector3 correctedForce = (boxTrans * f) - boxTrans.getOrigin();
	return correctedForce;
}


void bPhys_ex_complex::update()
{
	//objExport::update();
	//Example: temperature is too cold for engine operation
	//if (world->temp < 10)
	//{
	//	applied_power = 0;
	//}
	bt_body->setActivationState(DISABLE_DEACTIVATION);
	//Upwards Thrust
	{
		btVector3 f(0, applied_power, 0);
		bt_body->applyCentralForce(relativeForce(f, bt_body));
	}
	//Roll
	{
		btVector3 f(0, 0, roll);
		bt_body->applyCentralForce(relativeForce(f, bt_body));
	}
	//Pitch
	{
		btVector3 f(pitch, 0, 0);
		bt_body->applyCentralForce(relativeForce(f, bt_body));
	}
	//Yaw
	{
		btVector3 f(0, yaw, 0);
		//frame->body->applyCentralForce(relativeForce(f, frame->body));
		bt_body->applyTorque(f);
	}
}

std::string bPhys_ex_complex::getProperties()
{
	/*
	std::cout << applied_power << std::endl;
	std::cout << roll << std::endl;
	std::cout << pitch << std::endl;
	std::cout << yaw << std::endl;
	*/
	return "Power:" + std::to_string(applied_power) + " Pitch:" + std::to_string(pitch) + " Roll:" + std::to_string(roll) + " Yaw:" + std::to_string(yaw);
}


void bPhys_ex_complex::direct(direction dir)
{
	switch (dir)
	{
	case up: incr(&applied_power, 100.f, 11.f); break;
	case down: incr(&applied_power, -100.f, 11.f); break;
	case front: incr(&pitch, 100.f, 11.f); break;
	case back: incr(&pitch, -100.f, 11.f); break;
	case l_left: incr(&roll, -100.f, 11.f); break;
	case l_right: incr(&roll, 100.f, 11.f); break;
	case y_left: incr(&yaw, -100.f, 11.f); break;
	case y_right: incr(&yaw, 100.f, 11.f); break;

	case neutral:
		yaw = 0;
		pitch = 0;
		roll = 0;
		break;
	}
}


std::array<float, 7> bPhys_ex_complex::getTransform_qat()
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

void bPhys_ex_complex::setTransform_qat(std::array<float, 7> transform_qat)
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
