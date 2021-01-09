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


void test1()
{
	irr_inp* inp = new irr_inp();
	irr_gfx* gfx = new irr_gfx(inp);
	bPhysics* engine = new bPhysics();

	objExport* obj = new complex_obj(engine->getBox(), gfx->getBox());
	objExport* obj2 = new objExport(engine->getBox(), gfx->getBox());

	worldComposite* world = new worldComposite(inp, gfx, engine);
	world->addObject(obj);
	world->addObject(obj2);

	while(gfx->device->run())
	{
		world->update();
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
		.def(py::init([](worldComposite* world){
			objExport* obj = new objExport(world->m_engine->getBox(), world->m_gfx->getBox());
			world->addObject(obj);
			return std::unique_ptr<objExport>(obj); 
		}))
		.def("getProperties", &objExport::getProperties, R"pbdoc(Get the object properties)pbdoc")
		.def("setTransform_qat", &objExport::setTransform_qat, R"pbdoc(Set the object transform as a quaternion)pbdoc")
		.def("getTransform_qat", &objExport::getTransform_qat, R"pbdoc(Get the object transform as a quaternion)pbdoc");

	//Working with complex_obj
	m.def("create_complex", [](worldComposite* world) { 
		objExport* obj = new complex_obj(world->m_engine->getBox(), world->m_gfx->getBox());
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