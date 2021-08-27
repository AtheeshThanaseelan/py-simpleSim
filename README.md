# Python Simulation module

Simulation interface for python written in C++.
Can be ran as a standalone C++ executable, or exported as a Python module.

Pybind11 and C++11 is required to compile the python module

Supports
	Bullet3 for Physics
	Irrlicht for Graphics
	
## Installing
Download the wheel file from the releases page

Then, run "pip install physicsEnv*.whl" in the folder where the wheel was downloaded


## Compiling
C++: Use "make" in the c_module_source/src folder to make the executable with graphics support.

Use "make nogfx" in the c_module_source/src folder to make the executable without graphics support.

Python: Use "pip install ." in the c_module_source/src folder to make the python module without graphics support.


