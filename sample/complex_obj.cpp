#include "complex_obj.h"


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

complex_obj::complex_obj(world* main_world)
{
	frame = new box_obj{ main_world,new int[] {3,3,3},new int[] {0,0,0},1 };
	frame->body->setAngularFactor(btScalar(0));
}

complex_obj::complex_obj(pyWorld* py_world)
{
	frame = new box_obj{ py_world->main,new int[] {3,3,3},new int[] {0,0,0},1 };
	frame->body->setAngularFactor(btScalar(0));
}

void complex_obj::update_logic()
{
	frame->body->setActivationState(DISABLE_DEACTIVATION);
	

	
	//Upwards Thrust
	{
		btVector3 f(0, 0, pow);
		frame->body->applyCentralForce(relativeForce(f, frame->body));
	}
	//Roll
	{
		btVector3 f(0, roll, 0);
		frame->body->applyCentralForce(relativeForce(f, frame->body));
	}
	//Pitch
	{
		btVector3 f(pitch, 0, 0);
		frame->body->applyCentralForce(relativeForce(f, frame->body));
	}
}

std::string complex_obj::getProperties()
{
	std::cout << pow << std::endl;
	std::cout << roll << std::endl;
	std::cout << pitch << std::endl;
	system("cls");
	return "";
}

void complex_obj::direct(direction dir)
{
	switch (dir)
	{
		case up: incr(&pow, 100.f, 11.f); break;
		case down: incr(&pow, -100.f, 11.f); break;
		case front: incr(&pitch, 100.f, 11.f); break;
		case back: incr(&pitch, -100.f, 11.f); break;
		case left: incr(&roll, -100.f, 11.f); break;
		case right: incr(&roll, 100.f, 11.f); break;

	}
}

complex_obj::~complex_obj()
{
	delete frame;
}