#include "complexObject.h"

#include <iostream>
#include "../utility/utilities.h"
#include "../external/bPhysics.h"

complex_obj::complex_obj(btRigidBody* bt_body, IMeshSceneNode* irr_body) : objExport(bt_body,irr_body)
{

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


void complex_obj::update()
{
	objExport::update();
	//Example: temperature is too cold for engine operation
	if (world->temp < 10)
	{
		pow = 0;
	}
	bt_body->setActivationState(DISABLE_DEACTIVATION);
	//Upwards Thrust
	{
		btVector3 f(0, pow, 0);
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

std::string complex_obj::getProperties()
{
	/*
	std::cout << pow << std::endl;
	std::cout << roll << std::endl;
	std::cout << pitch << std::endl;
	std::cout << yaw << std::endl;
	*/
	return "Power:" + std::to_string(pow) + " Pitch:" + std::to_string(pitch) + " Roll:" + std::to_string(roll) + " Yaw:" + std::to_string(yaw);
}


void complex_obj::direct(direction dir)
{
	switch (dir)
	{
	case up: incr(&pow, 100.f, 11.f); break;
	case down: incr(&pow, -100.f, 11.f); break;
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