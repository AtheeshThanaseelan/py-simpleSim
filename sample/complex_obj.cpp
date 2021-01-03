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
	std::array<float, 3> size = { 5,1,3 };
	std::array<int, 3> pos = { 0,0,0 };
	frame = new box_obj{ main_world,size,pos,1 };
	frame->bt_body->setFriction(btScalar(10));
	//frame->body->setAngularFactor(btScalar(0));
}


complex_obj::complex_obj(pyWorld* py_world)
{
	isPyWorld = true;
	std::array<float, 3> size = { 5,1,3 };
	std::array<int, 3> pos = { 0,0,0 };
	frame = new box_obj{ py_world->main,size,pos,1 };
	//frame->body->setAngularFactor(btScalar(0));
}


void complex_obj::update_logic()
{
	frame->bt_body->setActivationState(DISABLE_DEACTIVATION);
	//Upwards Thrust
	{
		btVector3 f(0, pow, 0);
		frame->bt_body->applyCentralForce(relativeForce(f, frame->bt_body));
	}
	//Roll
	{
		btVector3 f(0, 0, roll);
		frame->bt_body->applyCentralForce(relativeForce(f, frame->bt_body));
	}
	//Pitch
	{
		btVector3 f(pitch, 0, 0);
		frame->bt_body->applyCentralForce(relativeForce(f, frame->bt_body));
	}
	//Yaw
	{
		btVector3 f(0, yaw, 0);
		//frame->body->applyCentralForce(relativeForce(f, frame->body));
		frame->bt_body->applyTorque(f);
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
	return "Power:"+ std::to_string(pow)+" Pitch:"+ std::to_string(pitch)+" Roll:"+ std::to_string(roll)+" Yaw:"+ std::to_string(yaw);
}

std::array<float,7> complex_obj::getTransform_qat()
{
	std::array<float, 7> ok{};
	ok[0] = frame->bt_body->getWorldTransform().getRotation().getW();
	ok[1] = frame->bt_body->getWorldTransform().getRotation().getX();
	ok[2] = frame->bt_body->getWorldTransform().getRotation().getY();
	ok[3] = frame->bt_body->getWorldTransform().getRotation().getZ();

	ok[4] = frame->bt_body->getWorldTransform().getOrigin().getX();
	ok[5] = frame->bt_body->getWorldTransform().getOrigin().getY();
	ok[6] = frame->bt_body->getWorldTransform().getOrigin().getZ();
	return ok;
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

void complex_obj::setTransform_qat(std::array<float, 7> ok)
{
	btQuaternion quat;
	quat.setW(ok[0]);
	quat.setX(ok[1]);
	quat.setY(ok[2]);
	quat.setZ(ok[3]);

	btVector3 origin;
	origin.setX(ok[4]);
	origin.setY(ok[5]);
	origin.setZ(ok[6]);

	btTransform trans;
	trans.setRotation(quat);
	trans.setOrigin(origin);

	frame->bt_body->setWorldTransform(trans);
}

complex_obj::~complex_obj()
{
	delete frame;
}