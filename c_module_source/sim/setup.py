import os, sys
import glob

from distutils.core import setup, Extension
from distutils import sysconfig

#cpp_args = ['-std=c++11', '-stdlib=libc++', '-mmacosx-version-min=10.7']

cpp_args = ['-std=c++11','-g','-Dgfx']

objects_path = 'src/drivers/bPhysics/objects/*.cpp'
path_list = glob.glob(objects_path)

gfx_path = 'src/drivers/irrlicht/*.cpp'
path_list += glob.glob(gfx_path)

utils_path = 'src/utility/region.cpp'
path_list += glob.glob(utils_path)

interface_path = 'src/interfaces/*.cpp'
path_list += glob.glob(interface_path)

path_list.append('src/pyMain.cpp') 
path_list.append('src/host.cpp') 
path_list.append('src/drivers/bPhysics/bPhysics.cpp')
path_list.append('src/drivers/export_btDebug.cpp')

sfc_module = Extension(
    'physicsEnv', sources= path_list, #['src/pyMain.cpp','src/drivers/bPhysics/bPhysics.cpp',objects_list,utils_list,interface_tlis],
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