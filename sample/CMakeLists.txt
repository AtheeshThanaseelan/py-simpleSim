cmake_minimum_required(VERSION 3.0)

project (Foo)

if(CMAKE_TOOLCHAIN_FILE)
    include(${CMAKE_TOOLCHAIN_FILE})
endif(CMAKE_TOOLCHAIN_FILE)

file(GLOB_RECURSE Foo_SOURCES "src/*.cpp" "src/*.h")
file(GLOB_RECURSE Foo_HEADERS "src/*.h")

set (Foo_INCLUDE_DIRS "")
foreach (_headerFile ${Foo_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Foo_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Foo_INCLUDE_DIRS)

find_package(bullet CONFIG REQUIRED)

add_executable (FooExe ${Foo_SOURCES})

target_include_directories(FooExe PUBLIC ${Foo_INCLUDE_DIRS})
target_include_directories(FooExe PUBLIC "src/external")

target_link_libraries(FooExe PRIVATE bullet)