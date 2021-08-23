#include <iostream>
#include <array>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "debugview.h"

namespace py = pybind11;

PYBIND11_MODULE(debugview, m)
{

	py::class_<debugview>(m,"debugview")
		.def(py::init([]() {
			debugview* exp = new debugview();
			return std::unique_ptr<debugview>(exp);
			}))
		.def("update", &debugview::update, R"pbdoc(Clear the line stack)pbdoc")
		.def("clearlines", &debugview::clear_lines, R"pbdoc()pbdoc")
		.def("setCamPos", &debugview::setCamPos, R"pbdoc()pbdoc")
		.def("setCamAng", &debugview::setCamAng, R"pbdoc()pbdoc")
		.def("addline", &debugview::add_line, R"pbdoc(add_line lines)pbdoc");




#ifdef VERSION_INFO
					m.attr("__version__") = VERSION_INFO;
#else
					m.attr("__version__") = "dev";
#endif

}