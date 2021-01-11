#include <iostream>
#include <array>
#include <Windows.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "external\bPhysics.h"
#include "external\irrlicht.h"

#include "objects/objectWrapper.h"
#include "objects/complexObject.h"

#include "utility/utilities.h"


namespace py = pybind11;

void proximity_sensor(bPhysics* engine, irr_gfx* gfx)
{
	btVector3 to(0, -2, 0);
	btVector3 from(0, 2, 0);

	std::array<float, 3> size = { 0.1 ,1, 0.1 }; std::array<float, 3> pos = { 0, 0,0 };
	gfx->getBox(size,pos);
	
	//arrow->setVisible(true);
	btCollisionWorld::ClosestRayResultCallback  closestResults(from, to);
	engine->dynamicsWorld->rayTest(from, to, closestResults);
	if (closestResults.hasHit())
	{

		std::cout << "---ok----" << std::endl;
		std::cout << closestResults.m_hitPointWorld.getX() << std::endl;
		std::cout << closestResults.m_hitPointWorld.getY() << std::endl;
		std::cout << closestResults.m_hitPointWorld.getZ() << std::endl;

	}
}



void test1()
{
	irr_inp* inp = new irr_inp();
	irr_gfx* gfx = new irr_gfx(inp);
	bPhysics* engine = new bPhysics();
	worldComposite* world = new worldComposite(inp, gfx, engine);

	engine->dynamicsWorld->setGravity(btVector3(0, 0, 0));

	objExport* obj2 = new objExport(engine->getBox(), gfx->getBox());
	obj2->bt_body->setFriction(0);
	world->addObject(obj2);


	while(gfx->device->run())
	{
		//proximity_sensor(engine,gfx);
		//obj2->bt_body->setLinearVelocity(btVector3(0, 0, 0));

		world->update();
		if (inp->IsKeyDown(KEY_SPACE))
		{
			obj2->bt_body->setLinearVelocity(btVector3(0, 0, 0));
		}
		if (inp->IsKeyDown(KEY_KEY_W))
		{
			obj2->bt_body->setLinearVelocity(btVector3(1, 0, 0));
		}
		if (inp->IsKeyDown(KEY_KEY_S))
		{
			obj2->bt_body->setLinearVelocity(btVector3(-1, 0, 0));
		}
		if (inp->IsKeyDown(KEY_KEY_A))
		{
			obj2->bt_body->setLinearVelocity(btVector3(0, 0, 1));
		}
		if (inp->IsKeyDown(KEY_KEY_D))
		{
			obj2->bt_body->setLinearVelocity(btVector3(0, 0, -1));
		}
		if (inp->IsKeyDown(KEY_KEY_Q))
		{
			obj2->bt_body->setLinearVelocity(btVector3(0, 1, 0));
		}
		if (inp->IsKeyDown(KEY_KEY_Z))
		{
			obj2->bt_body->setLinearVelocity(btVector3(0, -1, 0));
		}
	}

}

#if defined _DEBUG
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
			case 2:
				//test2();
				break;
			}
		} while (choice != 0);

		return 0;
	}

#else
PYBIND11_MODULE(physicsEnv, m)
{
	
	py::class_<objExport>(m, "generic_obj")
		.def(py::init([](worldComposite* world, std::array<float, 3> size = { 1,1,1 }, std::array<float, 3> pos = { 0,0,0 }){
			objExport* obj = new objExport(world->m_engine->getBox(size, pos), world->m_gfx->getBox(size, pos));
			world->addObject(obj);
			return std::unique_ptr<objExport>(obj); 
		}))
		.def("getProperties", &objExport::getProperties, R"pbdoc(Get the object properties)pbdoc")
		.def("setTransform_qat", &objExport::setTransform_qat, R"pbdoc(Set the object transform as a quaternion)pbdoc")
		.def("getTransform_qat", &objExport::getTransform_qat, R"pbdoc(Get the object transform as a quaternion)pbdoc");

	//Working with complex_obj
	m.def("create_complex", [](worldComposite* world, std::array<float, 3> size = { 1,1,1 }, std::array<float, 3> pos = { 0,0,0 }) {
		objExport* obj = new complex_obj(world->m_engine->getBox(size,pos), world->m_gfx->getBox(size, pos));
		world->addObject(obj);
		return std::unique_ptr<objExport>(obj);
	});

	//Working with world
	py::class_<worldComposite>(m, "worldComposite")
		.def(py::init([]{
			irr_inp* inp = new irr_inp();
			irr_gfx* gfx = new irr_gfx(inp);
			bPhysics* engine = new bPhysics();
			return std::unique_ptr<worldComposite>(new worldComposite(inp, gfx, engine));
		}))
		.def("update", &worldComposite::update);

#ifdef VERSION_INFO
	m.attr("__version__") = VERSION_INFO;
#else
	m.attr("__version__") = "dev";
#endif
}

#endif