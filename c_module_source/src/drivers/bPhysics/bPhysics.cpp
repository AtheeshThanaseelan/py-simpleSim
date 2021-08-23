#include "bPhysics.h"
#include "objects/box.h"
#include "objects/compound.h"
#include "objects/ground.h"
#include "bP_obj.h"
#include <array>
#include <iostream>


btRigidBody* bPhysics::createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape)
{
	btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		shape->calculateLocalInertia(mass, localInertia);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);

	btRigidBody* body = new btRigidBody(cInfo);
	//body->setContactProcessingThreshold(m_defaultContactProcessingThreshold);


	body->setUserIndex(-1);
	dynamicsWorld->addRigidBody(body);


	return body;
}
/*
btRigidBody* getBox(std::array<float, 3> size , std::array<float, 3> pos , int mass_param )
{

}
*/

bPhysics::bPhysics(btIDebugDraw* g)
{
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -10, 0));


	#ifdef gfx
		if(g != nullptr)
		{
			//drawer = new irr_btDebug();
			std::cout<<"gfx\n";
			dynamicsWorld->setDebugDrawer(g);
		}
	#endif
}

bPhysics::~bPhysics()
{
	for (int count = dynamicsWorld->getNumCollisionObjects() - 1; count >= 0; count--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[count];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}
	for (int count = 0; count < collisionShapes.size(); count++)
	{
		btCollisionShape* shape = collisionShapes[count];
		collisionShapes[count] = 0;
		delete shape;
	}
	delete dynamicsWorld;
	delete solver;
	delete overlappingPairCache;
	delete dispatcher;
	delete collisionConfiguration;
}

void bPhysics::update()
{
	#ifdef gfx
		//drawer->refresh();
	#endif
	dynamicsWorld->stepSimulation(1.f / 60.f, 2);
	dynamicsWorld->debugDrawWorld();
}

object_interface* bPhysics::addobj(int index)
{
	object_interface* obj = nullptr;
	switch(index){
		case -1:
			//obj = new bPhys_ground(this);
			break;
		case 1:
			obj = new bPhys_box(this);
			break;
		case 3:
			//obj = new bPhys_compound(this);
			break;
	}

    return obj;
}


