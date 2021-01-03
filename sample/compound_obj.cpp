#include "compound_obj.h"
//MCLPSolver ?
#define CUBE_HALF_EXTENTS 1

compound_obj::compound_obj(world* world) :obj_world(world)
{
	//Setup object properties
	float wheelRadius = 0.5f;
	float wheelWidth = 7.f;
	std::array<float,3> size = { wheelRadius,wheelRadius,wheelWidth };
	std::array<float, 3> chassis_size = { 10,3,5 };
	const btScalar FALLHEIGHT = 50;
	btVector3 positions[2] = {
		btVector3(btScalar(5), btScalar(FALLHEIGHT - 5), btScalar(0)),
		btVector3(btScalar(-5), btScalar(FALLHEIGHT - 5), btScalar(0))
	};

	const btScalar chassisMass = 2.0f;
	const btScalar wheelMass = 1.0f;

	btVector3 parentAxis(0.f, 1.f, 0.f);
	btVector3 childAxis(0.f, 0.f, 1.f);


	//Create Objects
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3(0, 0, 0));

	btCollisionShape* chassisShape = new btBoxShape(btVector3(10.f, 3.f, 5.f));
	world->collisionShapes.push_back(chassisShape);

	compound = new btCompoundShape();
	world->collisionShapes.push_back(compound);
	btTransform localTrans;
	localTrans.setIdentity();
	localTrans.setOrigin(btVector3(0, 0, 0));
	compound->addChildShape(localTrans, chassisShape);
	

	tr.setOrigin(btVector3(0, FALLHEIGHT, 0));


	main_body = createRigidBody(world, chassisMass, tr, compound);
	//main_body->setDamping(0.2, 0.2);
	m_wheelShape = new btCylinderShapeX(btVector3(wheelRadius, 0,wheelWidth * 2));

	
	for (int i = 0; i < 2; i++)
	{
		btRigidBody* pBodyA = this->main_body;
		pBodyA->setActivationState(DISABLE_DEACTIVATION);

		btTransform tr2;
		tr2.setIdentity();
		tr2.setOrigin(positions[i]);
		pBodyB[i] = createRigidBody(world, wheelMass, tr2, m_wheelShape);
		pBodyB[i]->setActivationState(DISABLE_DEACTIVATION);


		btVector3 anchor = tr2.getOrigin();

		pHingeStore[i] = new btHinge2Constraint(*pBodyA, *pBodyB[i], anchor, parentAxis, childAxis);
		world->dynamicsWorld->addConstraint(pHingeStore[i], true);

		//Limit Axis
		pHingeStore[i]->setLimit(0,0,0);
		pHingeStore[i]->setLimit(1,0,0);
		//pHingeStore[i]->setLimit(2,0,0); //up down
		//pHingeStore[i]->setLimit(3, 0, 0); //spin forward
		pHingeStore[i]->setLimit(4,0,0);
		//pHingeStore[i]->setLimit(5,0,0); //Spin left right

		// Set Spring Properties
		pHingeStore[i]->setDamping(2, 2.0);
		pHingeStore[i]->setStiffness(2, 4.0);

		//Save Nodes  
		pNode[i] = create_node(world, size);
		pBodyB[i]->setUserPointer(pNode[i]);
	}
	pHingeStore[0]->setLimit(5, 0, 0); //Spin left right
	pHingeStore[1]->enableMotor(5, true);

	//saving the visual node to the physics node  
	irr_main_body = create_node(world, chassis_size);
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


void compound_obj::direct(direction dir)
{
	switch (dir)
	{
	case up: 
		break;
	case down: 
		break;
	case front: 
		pHingeStore[0]->enableMotor(3, true);
		pHingeStore[0]->setMaxMotorForce(3, 100);
		pHingeStore[0]->setTargetVelocity(3, 1);
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

std::array<float, 7> compound_obj::getTransform_qat()
{
	std::array<float, 7> ok = { {0} };
	return ok;
}

void compound_obj::setTransform_qat(std::array<float, 7> ok)
{
	1 + 1;
}

std::string compound_obj::getProperties()
{
	return "";
}