#include <bullet/btBulletDynamicsCommon.h>
#include <iostream>
#include <array>

#include <physx/PxPhysicsAPI.h> 

class bulletEngine 
{
public:
	btBroadphaseInterface* overlappingPairCache;
	btCollisionDispatcher* dispatcher;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btSequentialImpulseConstraintSolver* solver;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	bulletEngine()
	{
		///--- World Creation
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
	}
	~bulletEngine()
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
	void update()
	{
		const f32 frameDeltaTime = (f32)(1.f / 60.f);
		dynamicsWorld->stepSimulation(frameDeltaTime, 2);
	}
	
	btRigidBody* createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape)
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
	
	btRigidBody* addBox()
	{
		std::array<float, 3> size {1,1,1};
		std::array<int, 3> pos{ 1,1,1 };
		int mass_param = 1;
		btCollisionShape* colShape = new btBoxShape(btVector3(size[0], size[1], size[2]));
		collisionShapes.push_back(colShape);
		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar mass(mass_param * 1.f);

		startTransform.setIdentity();
		startTransform.setOrigin(btVector3(pos[0], pos[1], pos[2]));

		return createRigidBody(mass, startTransform, colShape);
	}
};

class box 
{
public:
	btRigidBody* m_pBody;
	box(btRigidBody* pBody): m_pBody{pBody} {}
	std::array<float, 3> getOrigin()
	{

	}
};

void test1()
{
	bulletEngine* pEng = new bulletEngine();
	box* testbox = new box(pEng->addBox());
	//Make bullet engine
	//Bullet engine can export a box
	//Bullet engine can have compound objects
		//o fuc lmaoo
		//compound objects have a array of objects theyre made up of, and functions to manage joints
}

int main()
{
	int choice;
	do {
		printf("Choose test, 0 to exit: ");
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			test1();
			break;
		}
	} while (choice != 0);

	return 0;
}
