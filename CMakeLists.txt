cmake_minimum_required(VERSION 3.30)
project(sparseSystems)

set(CMAKE_CXX_STANDARD 20)

# in/out-put data folders include
include_directories(${CMAKE_SOURCE_DIR}/InputData)
include_directories(${CMAKE_SOURCE_DIR}/OutputData)
include_directories(${CMAKE_SOURCE_DIR}/src/mesh)
include_directories(${CMAKE_SOURCE_DIR}/src/sparseMethods)
include_directories(${CMAKE_SOURCE_DIR}/src/include/json)

add_executable(sparseSystems
        main.cpp
        src/sparseMethods/AdjacencyMethods.cpp
        src/sparseMethods/FIleMethods.cpp
        src/include/json/jsoncpp.cpp
        src/sparseMethods/AdjacencyMethods.cpp
        src/sparseMethods/FIleMethods.cpp
        src/sparseMethods/RootLevelMethods.cpp
        src/sparseMethods/InitialNodeMethods.cpp
        src/sparseMethods/MatrixOptimizationMethods.cpp
)

add_executable(createMesh
        src/mesh/meshCreator.cpp
        src/mesh/Functions.cpp
        src/mesh/Create_Web.cpp
        src/include/json/jsoncpp.cpp
)