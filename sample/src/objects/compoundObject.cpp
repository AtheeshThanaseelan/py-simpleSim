#include "compoundObject.h"
#include <iostream>
#include <math.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

btRigidBody* m_carChassis;

compound_obj::compound_obj(worldComposite* world):objExport(main_body)
{
	
	float wheelRadius = 0.5f;
	float wheelWidth = 0.15f;

	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0, -3, 0));

	btCollisionShape* chassisShape = new btBoxShape(btVector3(1.f, 0.5f, 2.f));
	world->m_engine->collisionShapes.push_back(chassisShape);

	compound = new btCompoundShape();
	world->m_engine->collisionShapes.push_back(compound);
	btTransform localTrans;
	localTrans.setIdentity();
	localTrans.setOrigin(btVector3(0, 1, 0));

	compound->addChildShape(localTrans, chassisShape);
	const btScalar FALLHEIGHT = 5;
	tr.setOrigin(btVector3(0, FALLHEIGHT, 0));

	const btScalar chassisMass = 2.0f;
	const btScalar wheelMass = 1.0f;
	m_carChassis = world->m_engine->createRigidBody(chassisMass, tr, compound);
	m_carChassis->setDamping(0.2, 0.2);
	m_wheelShape = new btCylinderShapeX(btVector3(wheelWidth, wheelRadius, wheelRadius));

	btVector3 wheelPos[4] = {
		btVector3(btScalar(-1.), btScalar(FALLHEIGHT - 0.5), btScalar(2)),
		btVector3(btScalar(1.), btScalar(FALLHEIGHT - 0.5), btScalar(2)),
		btVector3(btScalar(1.), btScalar(FALLHEIGHT - 0.5), btScalar(-2)),
		btVector3(btScalar(-1.), btScalar(FALLHEIGHT - 0.5), btScalar(-2)) };
	std::array <float,3>size = { 3,3,3 };
	for (int i = 0; i < 4; i++)
	{

		btRigidBody* pBodyA = m_carChassis;
		pBodyA->setActivationState(DISABLE_DEACTIVATION);
		// dynamic bodyB (child) below it :
		btTransform tr;
		btQuaternion rot(atan(1), 0, 0);
		tr.setRotation(rot);
		tr.setOrigin(wheelPos[i]);

		pBodyB[i] = world->m_engine->createRigidBody(wheelMass, tr, m_wheelShape);
		pBodyB[i]->setFriction(1000);
		//pBodyB->setActivationState(DISABLE_DEACTIVATION);
		// add some data to build constraint frames
		btVector3 parentAxis(0.f, 1.f, 0.f);
		btVector3 childAxis(1.f, 0.f, -1.f);
		btVector3 anchor = tr.getOrigin();
		btHinge2Constraint* pHinge2 = new btHinge2Constraint(*pBodyA, *pBodyB[i], anchor, parentAxis, childAxis);
		pHingeStore[i] = pHinge2;

		// add constraint to world
		world->m_engine->dynamicsWorld->addConstraint(pHinge2, true);

		// Drive engine.
		pHinge2->enableMotor(3, true);
		pHinge2->setMaxMotorForce(3, 100);
		pHinge2->setTargetVelocity(3, 0);

		// Steering engine.
		pHinge2->enableMotor(5, true);
		pHinge2->setMaxMotorForce(5, 100);
		pHinge2->setTargetVelocity(5, 100);

		pHinge2->setParam(BT_CONSTRAINT_CFM, 0.15f, 2);
		pHinge2->setParam(BT_CONSTRAINT_ERP, 0.35f, 2);

		pHinge2->setDamping(2, 2.0);
		pHinge2->setStiffness(2, 40.0);

		pHinge2->setDbgDrawSize(btScalar(5.f));

	}
}



void compound_obj::update()
{
	/*
	btVector3 origin = m_carChassis->getWorldTransform().getOrigin();
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
		pNode[i]->setVisible(false);
	}
	*/
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
			pHingeStore[i]->setMaxMotorForce(3, 1000);
			pHingeStore[i]->setTargetVelocity(3, 1);
			pBodyB[i]->setFriction(1000);
		}
		break;
	case back:
		for (int i = 0; i < 4; i++)
		{
			pHingeStore[i]->enableMotor(3, true);
			pHingeStore[i]->setMaxMotorForce(3, 100);
			pHingeStore[i]->setTargetVelocity(3, -10);
			pBodyB[i]->setFriction(1000);
		}

		break;
		
	case l_left:
		for (int i = 0; i < 2; i++)
		{
			pHingeStore[i]->enableMotor(5, true);
			//right left
			pHingeStore[i]->setLimit(5, 0.5, 1.5);
			pHingeStore[i]->setMaxMotorForce(5, 1000);
			pHingeStore[i]->setTargetVelocity(5, 10);
		}

		break;
	case l_right:
		for (int i = 0; i < 2; i++)
		{
			pHingeStore[i]->enableMotor(5, true);
			pHingeStore[i]->setLimit(5, 0.5, 1.5);
			pHingeStore[i]->setMaxMotorForce(5, 1000);
			pHingeStore[i]->setTargetVelocity(5, -10);
		}

		break;
		
	case y_left:		
		for (int i = 1; i < 3; i++)
		{
			pHingeStore[i]->enableMotor(2, true);
			//pHingeStore[i]->setLimit(5, 0.5, 1.5);
			pHingeStore[i]->setMaxMotorForce(2, 1000);
			pHingeStore[i]->setTargetVelocity(2, 10);
		}
		break;
	case y_right:
		for (int i = 1; i < 3; i++)
		{
			pHingeStore[i]->enableMotor(2, true);
			//pHingeStore[i]->setLimit(5, 0.5, 1.5);
			pHingeStore[i]->setMaxMotorForce(2, 1000);
			pHingeStore[i]->setTargetVelocity(2, -10);
		}

		break;

	case neutral:
		pHingeStore[0]->setMaxMotorForce(3, 0);
		pHingeStore[1]->setLimit(5, 0, 0);
		break;
	}
}

compound_obj::~compound_obj() {
	for (int i = 0; i < 4; i++) {
		delete pHingeStore[i];
	}
}
