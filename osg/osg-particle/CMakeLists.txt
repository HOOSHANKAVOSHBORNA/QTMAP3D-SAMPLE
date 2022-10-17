
cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

project(sogParticle VERSION 1.0)

add_executable(osgParticle main.cpp)

target_link_libraries(osgParticle PUBLIC osg osgViewer osgGA osgDB osgParticle)

