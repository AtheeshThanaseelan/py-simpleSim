#include "simple_objects.h"

box_obj::box_obj(world* world) :obj_world(world)
{
	btCollisionShape* colShape = new btBoxShape(btVector3(5, 5, 5));
	obj_world->collisionShapes.push_back(colShape);

	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();

	btScalar mass(3.f);

	startTransform.setOrigin(btVector3(0, 40, 0));
	//btQuaternion quat(btVector3(0.4, .02, .1), 67);
	btQuaternion quat(btVector3(1, 1, 1), 67); //rotat
	startTransform.setRotation(quat);

	btRigidBody* body = createRigidBody(world, mass, startTransform, colShape);
	body->setUserPointer(create_node(world));
}

terrain_obj::terrain_obj(world* world) :obj_world(world)
{
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(150.), btScalar(1.), btScalar(150.)));

	obj_world->collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -56, 0));


	btScalar mass(0.);
	
	btRigidBody* body = createRigidBody(world, mass, groundTransform, groundShape);
	
	body->setFriction(1);
	body->setUserIndex(5);

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
