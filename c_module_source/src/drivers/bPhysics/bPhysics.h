#pragma once
#include <bullet/btBulletDynamicsCommon.h>
#include "../../interfaces/physics_interface.h"
#include "../irrlicht/irr_debug_draw.h"

class bPhysics: public physics_interface
{
    public:
    btBroadphaseInterface* overlappingPairCache;
    btCollisionDispatcher* dispatcher;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btDiscreteDynamicsWorld* dynamicsWorld;
    btSequentialImpulseConstraintSolver* solver;
    btAlignedObjectArray<btCollisionShape*> collisionShapes;
    irr_btDebug* drawer;

    bPhysics(btIDebugDraw* g);
    ~bPhysics();
    void update();
    btRigidBody* createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape);
    object_interface* addobj(int index);

};