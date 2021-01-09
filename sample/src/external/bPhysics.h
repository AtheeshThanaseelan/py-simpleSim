#pragma once
#include <bullet/btBulletDynamicsCommon.h>

class bPhysics 
{
public:
	btBroadphaseInterface* overlappingPairCache;
	btCollisionDispatcher* dispatcher;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btSequentialImpulseConstraintSolver* solver;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	bPhysics();

	~bPhysics();

	void stepPhysics();

	
	btRigidBody* createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape);


	btRigidBody* getBox();

};
