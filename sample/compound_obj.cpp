#include "compound_obj.h"
//MCLPSolver ?
#define CUBE_HALF_EXTENTS 1

compound_obj::compound_obj(world* world) :obj_world(world)
{
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0, 0, 0));

	btCollisionShape* chassisShape = new btBoxShape(btVector3(3.f, 3.f, 3.f));
	world->collisionShapes.push_back(chassisShape);

	compound = new btCompoundShape();
	world->collisionShapes.push_back(compound);
	btTransform localTrans;
	localTrans.setIdentity();
	localTrans.setOrigin(btVector3(0, 0, 0));

	compound->addChildShape(localTrans, chassisShape);
	const btScalar FALLHEIGHT = 50;
	tr.setOrigin(btVector3(0, FALLHEIGHT, 0));

	const btScalar chassisMass = 2.0f;
	const btScalar wheelMass = 1.0f;
	main_body = createRigidBody(world, chassisMass, tr, compound);
	main_body->setDamping(0.2, 0.2);
	m_wheelShape = new btCylinderShapeX(btVector3(wheelWidth, wheelRadius, wheelRadius));//btBoxShape(btVector3(3, 3, 3));

	int size[3] = { 3,3,3 };

	btVector3 positions[2] = {
		btVector3(btScalar(), btScalar(FALLHEIGHT - 5), btScalar(5)),
		btVector3(btScalar(), btScalar(FALLHEIGHT - 5), btScalar(-5))
	};
	for (int i = 0; i < 2; i++)
	{
		btRigidBody* pBodyA = this->main_body;
		pBodyA->setActivationState(DISABLE_DEACTIVATION);

		btTransform tr2;
		tr2.setIdentity();
		tr2.setOrigin(positions[i]);

		pBodyB[i] = createRigidBody(world, wheelMass, tr2, m_wheelShape);
		pBodyB[i]->setFriction(btScalar(10000.f));
		pBodyB[i]->setAngularFactor(btVector3(1.f, 0.f, 0.f));
		btVector3 parentAxis(0.f, 1.f, 0.f);
		btVector3 childAxis(-1.f, 0.f, 0.f);
		btVector3 anchor = tr2.getOrigin();
		btHinge2Constraint* pHinge2 = new btHinge2Constraint(*pBodyA, *pBodyB[i], anchor, parentAxis, childAxis);
		
		world->dynamicsWorld->addConstraint(pHinge2, true);
		
		// Steering engine.
		for (int c = 0; c< 6; c++)
		{
			pHinge2->enableMotor(c, true);
			pHinge2->setMaxMotorForce(c, btScalar(INFINITY));
			pHinge2->setTargetVelocity(c, 0);
			pHinge2->isLimited(c);
		}
		//pHinge2->setParam(BT_CONSTRAINT_CFM, 0.15f, 2);
		//pHinge2->setParam(BT_CONSTRAINT_ERP, 0.35f, 2);
		pHinge2->setDamping(2, 2.0);
		pHinge2->setStiffness(2, 4.0);

		//saving the visual node to the physics node  
		pNode[i] = create_node(world, size);
		pBodyB[i]->setUserPointer(pNode[i]);
		pHingeStore[i] = pHinge2;
	}
	pHingeStore[0]->enableMotor(3, true);
	pHingeStore[0]->setTargetVelocity(3, 300);

	//saving the visual node to the physics node  
	irr_main_body = create_node(world, size);
	main_body->setUserPointer(irr_main_body);
}

compound_obj::~compound_obj()
{
	for (int i = 0; i < 2; i++)
	{
		main_body->removeConstraintRef(pHingeStore[i]);
		obj_world->dynamicsWorld->removeConstraint(pHingeStore[i]);
		delete pHingeStore[i];
	}
	for (int i = 0; i < 2; i++)
	{
		if (pBodyB[i] && pBodyB[i]->getMotionState())
		{
			delete pBodyB[i]->getMotionState();
		}
		obj_world->dynamicsWorld->removeCollisionObject(pBodyB[i]);

		obj_world->dynamicsWorld->removeRigidBody(pBodyB[i]);
		obj_world->scenemgr->addToDeletionQueue(pNode[i]);
		delete pBodyB[i];
	}
	obj_world->collisionShapes.remove(m_wheelShape);
	delete m_wheelShape;

	if (main_body && main_body->getMotionState())
	{
		delete main_body->getMotionState();
	}
	obj_world->dynamicsWorld->removeCollisionObject(main_body);
	btCollisionShape* shape = main_body->getCollisionShape();
	obj_world->collisionShapes.remove(shape);
	obj_world->dynamicsWorld->removeRigidBody(main_body);
	delete main_body;
	obj_world->scenemgr->addToDeletionQueue(irr_main_body);
}

void compound_obj::forward()
{
	pHingeStore[0]->setMaxMotorForce(3, 100);
}

void compound_obj::stop()
{
	pHingeStore[0]->setMaxMotorForce(3, 0);
			//->setTargetVelocity(3, 0);
}