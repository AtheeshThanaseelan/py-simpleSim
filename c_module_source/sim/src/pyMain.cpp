#include <iostream>
#include <array>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "host.h"
#include "interfaces/physics_interface.h"
#include "interfaces/object_interface.h"
#include "drivers/bPhysics/bPhysics.h"
#include "drivers/irrlicht/irr_debug_draw.h"
#include "drivers/export_btDebug.h"


namespace py = pybind11;

PYBIND11_MODULE(physicsEnv, m)
{

	py::class_<object_interface>(m, "p_object")
		.def("getProperties", &object_interface::getProperties, R"pbdoc(Get the object properties)pbdoc")
		.def("setProperties", &object_interface::setProperties, R"pbdoc(Get the object properties)pbdoc")
		.def("setTransform_qat", &object_interface::setTransform_qat, R"pbdoc(Set the object transform as a quaternion)pbdoc")
		.def("getTransform_qat", &object_interface::getTransform_qat, R"pbdoc(Get the object transform as a quaternion)pbdoc");

	py::class_<export_btDebug>(m, "export_btDebug")
		.def(py::init([](){
			export_btDebug* exp = new export_btDebug();
			return std::unique_ptr<export_btDebug>(exp);
		}))
		.def("getLines", &export_btDebug::getLines, R"pbdoc(Get the graphics lines)pbdoc")
		.def("update", &export_btDebug::update, R"pbdoc(Clear the line stack)pbdoc");

	py::class_<host>(m, "host")
		.def(py::init([](export_btDebug* exp){
				std::cout<<"exp gfx\n";
				host* h = new host();
				physics_interface* phys = new bPhysics(exp);
				h->setPhys(phys);
				//h->setGfx(exp);
				return std::unique_ptr<host>(h);
		}))
		.def(py::init([](bool enabl_gfx) {
			host* h = new host();
			if(enabl_gfx == true)
			{
				std::cout<<"dontbehre";
				irr_btDebug* g = new irr_btDebug();
				physics_interface* phys = new bPhysics(g);
				h->setPhys(phys);
				h->setGfx(g);
			}
			else
			{
				physics_interface* phys = new bPhysics(nullptr);
				h->setPhys(phys);
			}

			return std::unique_ptr<host>(h);
		}))
		.def("addObject", &host::addObject)
		.def("getObject", &host::getObject)
		.def("update", &host::update);


	#ifdef VERSION_INFO
						m.attr("__version__") = VERSION_INFO;
	#else
						m.attr("__version__") = "dev";
	#endif

}