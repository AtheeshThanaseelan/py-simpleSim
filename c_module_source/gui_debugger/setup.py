import os, sys
import glob

from distutils.core import setup, Extension
from distutils import sysconfig

#cpp_args = ['-std=c++11']


sfc_module = Extension(
    'debugview', sources= ['debugview.cpp','pybind.cpp'],
    include_dirs=['/usr/include/pybind11','/usr/include/bullet','pybind11/include','E:/Documents/C/Libraries/vcpkg/installed/x64-windows/include'],
    library_dirs=[f'E:/Documents/C/Libraries/vcpkg/installed/x64-windows/lib'],
    libraries=['Irrlicht'],
    language='c++',
    #extra_compile_args=cpp_args,
    )

setup(
    name='debugview',
    version='1.0',
    description='C++ physics and python (PyBind11)',
    ext_modules=[sfc_module],
)