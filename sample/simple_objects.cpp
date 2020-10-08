#include "simple_objects.h"

box_obj::box_obj(world* world) :obj_world(world)
{
	btCollisionShape* colShape = new btBoxShape(btVector3(5, 5, 5));
	obj_world->collisionShapes.push_back(colShape);

	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();

	btScalar mass(3.f);

	startTransform.setOrigin(btVector3(10, 40, 20));
	//btQuaternion quat(btVector3(0.4, .02, .1), 67);
	btQuaternion quat(btVector3(1, 1, 1), 67); //rotat
	startTransform.setRotation(quat);


	btAssert((!colShape || colShape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	colShape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, colShape, localInertia);

	btRigidBody* body = new btRigidBody(cInfo);
	body->setFriction(1);
	body->setUserIndex(10);
	obj_world->dynamicsWorld->addRigidBody(body);

	IMeshSceneNode* cubeNode = world->scenemgr->addCubeSceneNode(10.0f, NULL, -1, vector3df(0, 3, 10));
	cubeNode->setMaterialType(EMT_SOLID);
	cubeNode->setMaterialTexture(0, world->driver->getTexture("../textures/box.jpg"));
	cubeNode->setMaterialFlag(video::EMF_LIGHTING, false);
	cubeNode->setVisible(true);
	//saving the visual node to the physics node  
	body->setUserPointer(cubeNode);
}

terrain_obj::terrain_obj(world* world) :obj_world(world)
{
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(150.), btScalar(1.), btScalar(150.)));

	obj_world->collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -56, 0));

	btScalar mass(0.);

	btVector3 localInertia(0, 0, 0);

	btAssert((!groundShape || groundShape->getShapeType() != INVALID_SHAPE_PROXYTYPE));


	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);

	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, groundShape, localInertia);

	btRigidBody* body = new btRigidBody(cInfo);
	//body->setContactProcessingThreshold(m_defaultContactProcessingThreshold);

	body->setUserIndex(-1);

	body->setUserIndex(5);
	body->setFriction(1);

	//add the body to the dynamics world
	obj_world->dynamicsWorld->addRigidBody(body);

	IAnimatedMesh* hillPlaneMesh = obj_world->scenemgr->addHillPlaneMesh("myHill",
		core::dimension2d<f32>(30, 30),
		core::dimension2d<u32>(10, 10), 0, 0,
		core::dimension2d<f32>(0, 0),
		core::dimension2d<f32>(10, 10));

	ISceneNode* planeNode = obj_world->scenemgr->addAnimatedMeshSceneNode(hillPlaneMesh);
	planeNode->setMaterialTexture(0, obj_world->driver->getTexture("../textures/ground.jpg"));
	planeNode->setMaterialFlag(video::EMF_LIGHTING, false);
	planeNode->setPosition(core::vector3df(0, -55, 0));
}
