/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2015 Erwin Coumans  http://continuousphysics.com/Bullet/
This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:
1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

/*
* This file is NOT by the Bullet Physics development team
* 
* It is ALTERED
*/


#include "wheel_obj.h"
#include "..\base_utils.h"
#include "..\object_utils.h"

//MCLPSolver ?
#define CUBE_HALF_EXTENTS 1

wheel_obj::wheel_obj(world *world)
{
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0, -3, 0));

	btCollisionShape* chassisShape = new btBoxShape(btVector3(1.f, 0.5f, 2.f));
	world->collisionShapes.push_back(chassisShape);

	btCompoundShape* compound = new btCompoundShape();
	world->collisionShapes.push_back(compound);
	btTransform localTrans;
	localTrans.setIdentity();
	localTrans.setOrigin(btVector3(0, 1, 0));

	compound->addChildShape(localTrans, chassisShape);

	const btScalar FALLHEIGHT = 5;
	tr.setOrigin(btVector3(0, FALLHEIGHT, 0));

	const btScalar chassisMass = 2.0f;
	const btScalar wheelMass = 1.0f;
	m_carChassis = createRigidBody(world, chassisMass, tr, compound); 
	m_carChassis->setDamping(0.2, 0.2);
	m_wheelShape = new btCylinderShapeX(btVector3(wheelWidth, wheelRadius, wheelRadius));

	btVector3 wheelPos[4] = {
		btVector3(btScalar(-10.), btScalar(FALLHEIGHT - 5), btScalar(10.25)),
		btVector3(btScalar(10.), btScalar(FALLHEIGHT - 5), btScalar(10.25)),
		btVector3(btScalar(10.), btScalar(FALLHEIGHT - 5), btScalar(-10.25)),
		btVector3(btScalar(-10.), btScalar(FALLHEIGHT - 5), btScalar(-10.25)) };

	for (int i = 0; i < 4; i++)
	{

		btRigidBody* pBodyA = this->m_carChassis;
		pBodyA->setActivationState(DISABLE_DEACTIVATION);
		// dynamic bodyB (child) below it :
		btTransform tr;
		tr.setIdentity();
		tr.setOrigin(wheelPos[i]);

		btRigidBody* pBodyB = createRigidBody(world, wheelMass, tr, m_wheelShape);
		pBodyB->setFriction(1000);
		//pBodyB->setActivationState(DISABLE_DEACTIVATION);
		// add some data to build constraint frames
		btVector3 parentAxis(0.f, 1.f, 0.f);
		btVector3 childAxis(1.f, 0.f, 0.f);
		btVector3 anchor = tr.getOrigin();
		btHinge2Constraint* pHinge2 = new btHinge2Constraint(*pBodyA, *pBodyB, anchor, parentAxis, childAxis);
		pHingeStore[i] = pHinge2;

		// add constraint to world
		world->dynamicsWorld->addConstraint(pHinge2, true);

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

		//saving the visual node to the physics node  
		pBodyB->setUserPointer(create_node(world));
	}
	//saving the visual node to the physics node  
	m_carChassis->setUserPointer(create_node(world));
}

void wheel_obj::run(key_controller controller)
{
	if (controller.IsKeyDown(KEY_KEY_W))
	{
		for (int i = 0; i < 4; i++)
		{
			pHingeStore[i]->setTargetVelocity(3, 100);
			std::cout << std::endl;
		}
		controller.clear(KEY_KEY_W);
	}
}