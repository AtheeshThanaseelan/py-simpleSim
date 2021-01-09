#include "compoundObject.h"
#include <iostream>
compound_obj::compound_obj(worldComposite* world):objExport(main_body, irr_main_body)
{
	//Setup object properties
	float wheelRadius = 0.5f;
	float wheelWidth = 7.f;
	std::array<float, 3> size = { wheelRadius,wheelRadius,wheelWidth };
	std::array<float, 3> chassis_size = { 10,3,5 };
	const btScalar FALLHEIGHT = 50;
	btVector3 positions[4] = {
			btVector3(btScalar(-1.), btScalar(FALLHEIGHT - 0.25), btScalar(1.25)),
			btVector3(btScalar(1.), btScalar(FALLHEIGHT - 0.25), btScalar(1.25)),
			btVector3(btScalar(1.), btScalar(FALLHEIGHT - 0.25), btScalar(-1.25)),
			btVector3(btScalar(-1.), btScalar(FALLHEIGHT - 0.25), btScalar(-1.25)) };


	const btScalar chassisMass = 2.0f;
	const btScalar wheelMass = 1.0f;

	btVector3 parentAxis(0.f, 1.f, 0.f);
	btVector3 childAxis(0.f, 0.f, 1.f);


	//Create Objects
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0, 0, 0));

	btCollisionShape* chassisShape = new btBoxShape(btVector3(10.f, 3.f, 5.f));
	world->m_engine->collisionShapes.push_back(chassisShape);

	compound = new btCompoundShape();
	world->m_engine->collisionShapes.push_back(compound);
	btTransform localTrans;
	localTrans.setIdentity();
	localTrans.setOrigin(btVector3(0, 0, 0));
	compound->addChildShape(localTrans, chassisShape);


	tr.setOrigin(btVector3(0, FALLHEIGHT, 0));


	main_body = world->m_engine->createRigidBody(chassisMass, tr, compound);
	//main_body->setDamping(0.2, 0.2);
	m_wheelShape = new btCylinderShapeX(btVector3(wheelRadius, 0, wheelWidth * 2));


	for (int i = 0; i < 4; i++)
	{
		btRigidBody* pBodyA = this->main_body;
		pBodyA->setActivationState(DISABLE_DEACTIVATION);

		btTransform tr2;
		tr2.setIdentity();
		tr2.setOrigin(positions[i]);
		pBodyB[i] = world->m_engine->createRigidBody(wheelMass, tr2, m_wheelShape);
		
		pBodyB[i]->setActivationState(DISABLE_DEACTIVATION);


		btVector3 anchor = tr2.getOrigin();

		pHingeStore[i] = new btHinge2Constraint(*pBodyA, *pBodyB[i], anchor, parentAxis, childAxis);
		world->m_engine->dynamicsWorld->addConstraint(pHingeStore[i], true);

		//Limit Axis
		pHingeStore[i]->setLimit(0, 0, 0);
		pHingeStore[i]->setLimit(1, 0, 0);
		//pHingeStore[i]->setLimit(2,0,0); //up down
		//pHingeStore[i]->setLimit(3, 0, 0); //spin forward
		pHingeStore[i]->setLimit(4, 0, 0);
		//pHingeStore[i]->setLimit(5,0,0); //Spin left right

		// Set Spring Properties
		pHingeStore[i]->setDamping(2, 2.0);
		pHingeStore[i]->setStiffness(2, 4.0);

		//Save Nodes  
		pNode[i] = world->m_gfx->getBox();
		pBodyB[i]->setUserPointer(pNode[i]);
	}
	pHingeStore[0]->setLimit(5, 0, 0); //Spin left right
	pHingeStore[1]->enableMotor(5, true);

	//saving the visual node to the physics node  
	irr_main_body = world->m_gfx->getBox();
	main_body->setUserPointer(irr_main_body);
}

void compound_obj::update()
{
	btVector3 origin = main_body->getWorldTransform().getOrigin();
	//update rotation
	btQuaternion rot = main_body->getWorldTransform().getRotation();
	quaternion q(rot.getX(), rot.getY(), rot.getZ(), rot.getW());
	vector3df Euler;
	q.toEuler(Euler);
	Euler *= RADTODEG;

	irr_main_body->setPosition(vector3df(origin.getX(), origin.getY(), origin.getZ()));
	irr_main_body->setRotation(Euler);
	irr_main_body->setVisible(true);

	for (int i = 0; i < 4; i++)
	{
		btVector3 origin = pBodyB[i]->getWorldTransform().getOrigin();
		//update rotation
		btQuaternion rot = pBodyB[i]->getWorldTransform().getRotation();
		quaternion q(rot.getX(), rot.getY(), rot.getZ(), rot.getW());
		vector3df Euler;
		q.toEuler(Euler);
		Euler *= RADTODEG;

		pNode[i]->setPosition(vector3df(origin.getX(), origin.getY(), origin.getZ()));
		pNode[i]->setRotation(Euler);
		pNode[i]->setVisible(true);
	}
}

void compound_obj::direct(direction dir)
{
	switch (dir)
	{
	case up:
		break;
	case down:
		break;
	case front:
		for (int i = 0; i < 4; i++)
		{
			pHingeStore[i]->enableMotor(3, true);
			pHingeStore[i]->setMaxMotorForce(3, 100);
			pHingeStore[i]->setTargetVelocity(3, 1000);
			pBodyB[i]->setFriction(1000);
		}
		break;
	case back:
		pHingeStore[0]->enableMotor(3, true);
		pHingeStore[0]->setMaxMotorForce(3, 100);
		pHingeStore[0]->setTargetVelocity(3, -10);
		break;
		/*
	case l_left:
		pHingeStore[1]->enableMotor(5, true);
		pHingeStore[1]->setLimit(5, -1, 1);
		pHingeStore[1]->setMaxMotorForce(5, 1000);
		pHingeStore[1]->setTargetVelocity(5, 10);
		break;
	case l_right:
		pHingeStore[1]->enableMotor(5, true);
		pHingeStore[1]->setLimit(5, -1, 1);
		pHingeStore[1]->setMaxMotorForce(5, 1000);
		pHingeStore[1]->setTargetVelocity(5, -10);
		break;
		*/
	case y_left:
		break;
	case y_right:
		break;

	case neutral:
		pHingeStore[0]->setMaxMotorForce(3, 0);
		pHingeStore[1]->setLimit(5, 0, 0);
		break;
	}
}