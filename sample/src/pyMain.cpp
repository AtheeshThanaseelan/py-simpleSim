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

/*
#include "utility/utilities.h"
#include "utility/range_finder.h"
#include "utility/irr_debug_draw.h"
*/
#include "utility/region.h"

namespace py = pybind11;

PYBIND11_MODULE(physicsEnv, m)
{

	#pragma region Compound Obj
	py::class_<compound_obj>(m, "compound_obj")
		.def(py::init([](worldComposite* world) {
			compound_obj* co = new compound_obj(world);
			world->addObject(co);
			return std::unique_ptr<compound_obj>(co);
		}))
		.def("direct",&compound_obj::direct, R"pbdoc(Direct object)pbdoc");
	#pragma endregion

	#pragma region Region
	py::class_<region>(m, "region")
		.def(py::init([](std::array<std::array<int, 2>, 4> vertices) {
			region* reg = new region(vertices);
			return std::unique_ptr<region>(reg);
		}))
		.def("checkRegion",&region::check, R"pbdoc(Check if point in region)pbdoc")
		.def("drawRegion",&region::draw, R"pbdoc(Draw region)pbdoc");
	#pragma endregion
	
	#pragma region generic_obj
	py::class_<objExport>(m, "generic_obj")
		.def(py::init([](worldComposite* world, std::array<float, 3> size = { 1,1,1 }, std::array<float, 3> pos = { 0,0,0 }) {
			objExport* obj = new objExport(world->m_engine->getBox(size, pos));
			world->addObject(obj);
			return std::unique_ptr<objExport>(obj);
		}))
		.def("getProperties", &objExport::getProperties, R"pbdoc(Get the object properties)pbdoc")
		.def("setTransform_qat", &objExport::setTransform_qat, R"pbdoc(Set the object transform as a quaternion)pbdoc")
		.def("getTransform_qat", &objExport::getTransform_qat, R"pbdoc(Get the object transform as a quaternion)pbdoc");
	#pragma endregion

	#pragma region Screen
	py::class_<irr_gfx>(m, "screen")
		.def(py::init([] {
			irr_inp* inp = new irr_inp();
			irr_gfx* gfx = new irr_gfx(inp);
			ICameraSceneNode* cameraNode;
			cameraNode = gfx->scenemgr->addCameraSceneNodeFPS(NULL, 20.0f, 0.02f);
			cameraNode->setPosition(vector3df(-10, 0, -30));
			return std::unique_ptr<irr_gfx>(gfx);
		}))
		.def("addLine", &irr_gfx::add_line, R"pbdoc(Add line)pbdoc");
	#pragma endregion
	
	#pragma region complex_obj
	m.def("create_complex", [](worldComposite* world, std::array<float, 3> size = { 1,1,1 }, std::array<float, 3> pos = { 0,0,0 }) {
		objExport* obj = new complex_obj(world->m_engine->getBox(size, pos), world->m_gfx->getBox(size, pos));
		world->addObject(obj);
		return std::unique_ptr<objExport>(obj);
	});
	#pragma endregion

	#pragma region drawline
	m.def("add_line", [](worldComposite* world, std::array<float, 6> line) {
		world->m_gfx->lines.push_back(line);
	});
	#pragma endregion
	
	#pragma region Worldcomposite
	py::class_<worldComposite>(m, "worldComposite")
		.def(py::init([](irr_gfx* gfx) {
			bPhysics* engine = new bPhysics();
			return std::unique_ptr<worldComposite>(new worldComposite(gfx->m_inp, gfx, engine));
		}))
		.def(py::init([]() {
			bPhysics* engine = new bPhysics();
			return std::unique_ptr<worldComposite>(new worldComposite(engine));
		}))
		.def("update", &worldComposite::update);
	#pragma endregion

	#ifdef VERSION_INFO
						m.attr("__version__") = VERSION_INFO;
	#else
						m.attr("__version__") = "dev";
	#endif
}