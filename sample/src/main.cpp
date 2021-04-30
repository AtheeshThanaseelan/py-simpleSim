#include <iostream>
#include <array>
#include <Windows.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "external\bPhysics.h"
#include "external\irrlicht.h"

#include "objects/objectWrapper.h"
#include "objects/complexObject.h"
#include "objects/compoundObject.h"

#include "utility/utilities.h"
#include "utility/range_finder.h"
#include "utility/irr_debug_draw.h"
#include "utility/region.h"

namespace py = pybind11;

void test1()
{
	irr_inp* inp = new irr_inp();
	irr_gfx* gfx = new irr_gfx(inp);
	bPhysics* engine = new bPhysics();

	irr_btDebug* drawer = new irr_btDebug(gfx);
	engine->dynamicsWorld->setDebugDrawer(drawer);

	worldComposite* world = new worldComposite(inp, gfx, engine);

	engine->dynamicsWorld->setGravity(btVector3(0, 0, 0));

	objExport* obj2 = new objExport(engine->getBox(), gfx->getBox());
	obj2->bt_body->setFriction(0);
	world->addObject(obj2);

	std::array<float, 3> from_points{ -3,0,0 };
	std::array<float, 3> to_points{ 1,0,0 };
	//range_finder* ok = new range_finder(from_points,to_points,world);

	//region* square = new region(world);

	while(gfx->device->run() && gfx->driver->beginScene(true, true, video::SColor(100, 0, 0, 255)))
	{
		//square->check();
		//square->draw();
		engine->dynamicsWorld->debugDrawWorld();
		world->update();

		if (inp->IsKeyDown(KEY_SPACE))
		{
			//obj3->direct(front);
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

		gfx->scenemgr->drawAll();
		gfx->driver->endScene();
	}
}

void test2()
{
	irr_inp* inp = new irr_inp();
	irr_gfx* gfx = new irr_gfx(inp);
	bPhysics* engine = new bPhysics();
	worldComposite* world = new worldComposite(inp, gfx, engine);

	compound_obj* co = new compound_obj(world);
	objExport* o2 = co;

	while (world->update())
	{
		for(int i=0;i<6;i++)
			std::cout << o2->getProperties();
		if (inp->IsKeyDown(KEY_KEY_S))
			co->direct(front);
		if (inp->IsKeyDown(KEY_KEY_W))
			co->direct(back);
		if (inp->IsKeyDown(KEY_KEY_A))
			co->direct(l_left);
		if (inp->IsKeyDown(KEY_KEY_D))
			co->direct(l_right);
		if (inp->IsKeyDown(KEY_KEY_U))
			co->direct(y_left);
		if (inp->IsKeyDown(KEY_KEY_O))
			co->direct(y_right);
	}
}

void test3()
{
	bPhysics* engine = new bPhysics();
	worldComposite* world = new worldComposite(engine);

	compound_obj* co = new compound_obj(world);
	objExport* o2 = co;

	while (world->update())
	{
		std::cout << o2->getProperties();
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
				test2();
				break;
			case 3:
				test3();
				break;
			}
		} while (choice != 0);

		return 0;
	}

#else
PYBIND11_MODULE(physicsEnv, m)
{
	//Working with objExport
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