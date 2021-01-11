#pragma once
#include <bullet/btBulletDynamicsCommon.h>
#include <array>

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


	btRigidBody* getBox(std::array<float, 3> size = { 1,1,1 }, std::array<float, 3> pos = { 1,1,1 }, int mass_param = 1);

};
