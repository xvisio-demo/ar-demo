# Copyright 2018, XVisio
cmake_minimum_required(VERSION 3.0)


PROJECT(xslam-ar-demo)
SET(LIB_NAME ${PROJECT_NAME} )

SET(PROJECT_DESCRIPTION "XSlam AR demo")
SET(PROJECT_URL "http://developer.xvisio.org/")
SET(PROJECT_REQUIREMENTS "")
SET(PROJECT_VERSION_MAJOR 2)
SET(PROJECT_VERSION_MINOR 0)
SET(PROJECT_VERSION_PATCH 3)
SET(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
SET(PROJECT_STATE "1")
if( NOT "${PROJECT_STATE}" STREQUAL "" )
    SET(FULL_PROJECT_VERSION ${PROJECT_VERSION}-${PROJECT_STATE})
endif()
add_definitions("-DPROJECT_VERSION=\"${FULL_PROJECT_VERSION}\"")



include_directories( ${CMAKE_CURRENT_SOURCE_DIR})

find_package( XSlamSDK REQUIRED)
include_directories( ${XSlamSDK_INCLUDE_DIRS} )
link_directories( ${XSlamSDK_LIBRARY_DIRS} )

#find_package( xslam-drivers REQUIRED)
#include_directories( ${xslam-drivers_INCLUDE_DIRS} )
#link_directories( ${xslam-drivers_LIBRARY_DIRS} )

find_package(Eigen3 REQUIRED)
include_directories( ${EIGEN3_INCLUDE_DIR} )

find_package(Qt5 REQUIRED COMPONENTS Core Quick 3DCore 3DExtras 3DRender 3DInput )

set(CMAKE_AUTOMOC ON)

FILE( GLOB SRC_LIST *.cpp )

qt5_add_resources(RESOURCES qml.qrc objects.qrc cedar-bridge.qrc robot.qrc shaders.qrc )
add_executable(xslam-ar-demo.bin ${SRC_LIST} ${RESOURCES} ${QM})
#qt5_use_modules(xslam-ar-demo.bin Widgets)

set( viewer_libs Qt5::Core Qt5::Quick Qt5::3DCore Qt5::3DExtras Qt5::3DRender Qt5::3DInput ${XSlamSDK_LIBRARIES} )

target_link_libraries(xslam-ar-demo.bin ${viewer_libs} )

INSTALL(TARGETS xslam-ar-demo.bin
    DESTINATION bin
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE OWNER_EXECUTE)

INSTALL(FILES xslam-ar-demo
    DESTINATION bin
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE OWNER_EXECUTE)

