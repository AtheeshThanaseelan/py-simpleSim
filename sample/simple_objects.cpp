#include "simple_objects.h"

box_obj::box_obj(world* world,float size[3], int pos[3], int mass_param) :obj_world(world)
{
	btCollisionShape* colShape = new btBoxShape(btVector3(size[0], size[1], size[2]));
	obj_world->collisionShapes.push_back(colShape);

	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();

	btScalar mass(mass_param *1.f);

	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(pos[0], pos[1],pos[2]));

	body = createRigidBody(world, mass, startTransform, colShape);

	irr_body = create_node(world, size);
	body->setUserPointer(irr_body);

	delete size;
	delete pos;
}

box_obj::~box_obj()
{
	if (body && body->getMotionState())
	{
		delete body->getMotionState();
	}
	obj_world->dynamicsWorld->removeCollisionObject(body);

	btCollisionShape* shape = body->getCollisionShape();
	obj_world->collisionShapes.remove(shape);
	delete shape;

	obj_world->dynamicsWorld->removeRigidBody(body);
	obj_world->scenemgr->addToDeletionQueue(irr_body);
	delete body;
}

void box_obj::forward()
{
	body->setActivationState(DISABLE_DEACTIVATION);
	btVector3 f(100,0, 0);
	body->applyCentralImpulse(f);
}

void box_obj::stop()
{
		body->setActivationState(DISABLE_DEACTIVATION);
		btVector3 f(-100, 0, 0);
		body->applyCentralImpulse(f);
}

terrain_obj::terrain_obj(world* world) :obj_world(world)
{
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(1000.), btScalar(1.), btScalar(1000.)));

	obj_world->collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, 0, 0));


	btScalar mass(0.);
	
	body = createRigidBody(world, mass, groundTransform, groundShape);
	
	body->setFriction(1);
	body->setUserIndex(5);

	IAnimatedMesh* hillPlaneMesh = obj_world->scenemgr->addHillPlaneMesh("base",
		core::dimension2d<f32>(10, 10),
		core::dimension2d<u32>(100, 100), 0, 0,
		core::dimension2d<f32>(0, 0),
		core::dimension2d<f32>(100, 100));

	irr_planeNode = obj_world->scenemgr->addAnimatedMeshSceneNode(hillPlaneMesh);
	irr_planeNode->setMaterialTexture(0, obj_world->driver->getTexture("../textures/ground.jpg"));
	irr_planeNode->setMaterialFlag(video::EMF_LIGHTING, false);
	irr_planeNode->setPosition(core::vector3df(0, 0, 0));
}

terrain_obj::~terrain_obj()
{
	
	if (body && body->getMotionState())
	{
		delete body->getMotionState();
	}
	obj_world->dynamicsWorld->removeCollisionObject(body);

	btCollisionShape* shape = body->getCollisionShape();
	obj_world->collisionShapes.remove(shape);
	delete shape;


	obj_world->dynamicsWorld->removeRigidBody(body);
	obj_world->scenemgr->addToDeletionQueue(irr_planeNode);

	delete body;
}

