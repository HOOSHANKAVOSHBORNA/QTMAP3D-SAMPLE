
cmake_minimum_required(VERSION 3.12)

project(Crystal LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")

set(CMAKE_CXX_EXTENSIONS ON)

find_package(Qt5 COMPONENTS Core Quick Gui Widgets REQUIRED)

add_executable(Crystal
        Main.cpp
        OsgRenderer.cpp
        OsgQuickWindow.cpp
        CrystalWindow.cpp
        CrystalPluginInterface.cpp
        CrystalApplication.cpp
        CrystalMapController.cpp
        CrystalPluginManager.cpp
        Qml.qrc
        Crystal.qrc)


target_include_directories(Crystal PUBLIC "/usr/local/include")
target_link_libraries(Crystal
  PRIVATE Qt5::Core Qt5::Quick Qt5::Gui Qt5::Widgets
  PUBLIC osg osgViewer osgDB osgGA OpenThreads osgManipulator osgSim osgParticle osgText osgUtil
  gdal osgEarth osgEarthFeatures osgEarthUtil osgEarthSymbology osgEarthAnnotation
  GL
  )
