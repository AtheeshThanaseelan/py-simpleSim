import os, sys

from distutils.core import setup, Extension
from distutils import sysconfig

cpp_args = ['-std=c++11', '-stdlib=libc++', '-mmacosx-version-min=10.7']

sfc_module = Extension(
    'physicsEnv', sources=['src/utility/utilities.cpp','src/main.cpp','src/external/bPhysics.cpp','src/external/irrlicht.cpp','src/objects/objectWrapper.cpp','src/objects/complexObject.cpp'],
    include_dirs=['pybind11/include','E:/Documents/C/Libraries/vcpkg/installed/x64-windows/include'],
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