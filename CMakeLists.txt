cmake_minimum_required(VERSION 3.30)
project(sparseSystems)

set(CMAKE_CXX_STANDARD 20)

# in/out-put data folders include
include_directories(${CMAKE_SOURCE_DIR}/InputData)
include_directories(${CMAKE_SOURCE_DIR}/OutputData)
include_directories(${CMAKE_SOURCE_DIR}/src/mesh)

add_executable(sparseSystems main.cpp
        src/mesh/meshCreator.cpp)

add_executable(createMesh
        src/mesh/meshCreator.cpp
        src/mesh/Functions.cpp
        src/mesh/Create_Web.cpp
        src/include/json/jsoncpp.cpp
)