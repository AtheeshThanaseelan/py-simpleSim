#pragma once
#include "PxPhysicsAPI.h"

class pEngine
{
public:
	PxDefaultAllocator		gAllocator;
	PxDefaultErrorCallback	gErrorCallback;
	PxFoundation* gFoundation = NULL;
	PxPhysics* gPhysics = NULL;
	PxDefaultCpuDispatcher* gDispatcher = NULL;
	PxScene* gScene = NULL;
	PxMaterial* gMaterial = NULL;
	PxPvd* gPvd = NULL;
	PxReal stackZ = 10.0f;


	pEngine()
	{
		gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

		gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

		PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
		sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
		gDispatcher = PxDefaultCpuDispatcherCreate(2);
		sceneDesc.cpuDispatcher = gDispatcher;
		sceneDesc.filterShader = PxDefaultSimulationFilterShader;
		gScene = gPhysics->createScene(sceneDesc);

		PxPvd* pvd = PxCreatePvd(*gFoundation);
		PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("localhost", 5425, 10);
		pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

		PxPhysics* physics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, pvd);

	}

	void stepPhysics()
	{
		gScene->simulate(1.0f / 60.0f);
		gScene->fetchResults(true);
	}


};
