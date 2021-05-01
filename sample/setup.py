import os, sys

from distutils.core import setup, Extension
from distutils import sysconfig

#cpp_args = ['-std=c++11', '-stdlib=libc++', '-mmacosx-version-min=10.7']

cpp_args = ['-std=c++11']

sfc_module = Extension(
    'physicsEnv', sources=['src/objects/compoundObject.cpp','src/utility/irr_debug_draw.cpp','src/utility/utilities.cpp','src/pyMain.cpp','src/external/bPhysics.cpp','src/external/irrlicht.cpp','src/objects/objectWrapper.cpp','src/objects/complexObject.cpp','src/utility/region.cpp'],
    include_dirs=['/usr/include/pybind11','/usr/include/bullet','pybind11/include','E:/Documents/C/Libraries/vcpkg/installed/x64-windows/include'],
    library_dirs=[f'E:/Documents/C/Libraries/vcpkg/installed/x64-windows/lib'],
    libraries=['LinearMath','Bullet3Common','BulletCollision','BulletDynamics','Irrlicht'],
    language='c++',
    extra_compile_args=cpp_args,
    )

setup(
    name='physicsEnv',
    version='1.0',
    description='C++ physics and python (PyBind11)',
    ext_modules=[sfc_module],
)