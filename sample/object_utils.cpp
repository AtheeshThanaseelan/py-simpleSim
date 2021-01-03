#include "object_utils.h"

IMeshSceneNode* create_node(world* world, std::array<float, 3> size)
{
	IMeshSceneNode* cubeNode = world->scenemgr->addCubeSceneNode(1.0f,0,0,vector3df(0,0,0), vector3df(0, 0, 0), vector3df(size[0]*2, size[1]*2, size[2]*2));
	cubeNode->setMaterialType(EMT_SOLID);
	cubeNode->setMaterialTexture(0, world->driver->getTexture("../textures/box.jpg"));
	cubeNode->setMaterialFlag(video::EMF_LIGHTING, false);
	cubeNode->setVisible(true);
	return cubeNode;
}

ISceneNode* load_obj(world* world, std::string file)
{
	std::string* fileptr = &file;
	irr:io:path path = fileptr->c_str();
	IAnimatedMesh* obj = world->scenemgr->getMesh(path);
	IAnimatedMeshSceneNode* obj_node = world->scenemgr->addAnimatedMeshSceneNode(obj);
	obj_node->setMaterialFlag(video::EMF_LIGHTING, false);
	obj_node->setPosition(vector3df(0, 0, 0));
	obj_node->setRotation(vector3df(0, 90, 90));
	return obj_node;
}

btRigidBody* createRigidBody(world* world, float mass, const btTransform& startTransform, btCollisionShape* shape)
{
	btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		shape->calculateLocalInertia(mass, localInertia);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

#define USE_MOTIONSTATE 1
#ifdef USE_MOTIONSTATE
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);

	btRigidBody* body = new btRigidBody(cInfo);
	//body->setContactProcessingThreshold(m_defaultContactProcessingThreshold);

#else
	btRigidBody* body = new btRigidBody(mass, 0, shape, localInertia);
	body->setWorldTransform(startTransform);
#endif  //

	body->setUserIndex(-1);
	world->dynamicsWorld->addRigidBody(body);
	return body;
}


void py_obj::direct(direction dir)
{
	std::cout << "Object is static" << std::endl;
}
std::array<float, 7> py_obj::getTransform_qat()
{
	std::array<float, 7> transform_qat{};
	transform_qat[0] = bt_body->getWorldTransform().getRotation().getW();
	transform_qat[1] = bt_body->getWorldTransform().getRotation().getX();
	transform_qat[2] = bt_body->getWorldTransform().getRotation().getY();
	transform_qat[3] = bt_body->getWorldTransform().getRotation().getZ();

	transform_qat[4] = bt_body->getWorldTransform().getOrigin().getX();
	transform_qat[5] = bt_body->getWorldTransform().getOrigin().getY();
	transform_qat[6] = bt_body->getWorldTransform().getOrigin().getZ();
	return transform_qat;
}
std::string py_obj::getProperties()
{
	std::string empty = "Not Complex";
	return empty;
}
void py_obj::setTransform_qat(std::array<float, 7> transform_qat)
{
	btQuaternion quat;
	quat.setW(transform_qat[0]);
	quat.setX(transform_qat[1]);
	quat.setY(transform_qat[2]);
	quat.setZ(transform_qat[3]);

	btVector3 origin;
	origin.setX(transform_qat[4]);
	origin.setY(transform_qat[5]);
	origin.setZ(transform_qat[6]);

	btTransform trans;
	trans.setRotation(quat);
	trans.setOrigin(origin);

	bt_body->setWorldTransform(trans);
}