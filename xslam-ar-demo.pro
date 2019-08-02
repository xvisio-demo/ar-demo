!versionAtLeast(QT_VERSION, 5.12.0):error("Use at least Qt version 5.12.0")

CONFIG += c++11
CONFIG += resources_big

QT += quick 3dcore 3drender 3dinput 3dquick 3dextras qml quick 3dquickextras 3danimation

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        controller.cpp \
        cameramesh.cpp \
        gridmesh.cpp \
        linemesh.cpp \
        pathmesh.cpp \
        pointmesh.cpp \
        tools.cpp \
        cloudmesh.cpp \
        imagepainter.cpp \
    surfacemesh.cpp \
    customtype.cpp

RESOURCES += \
            qml.qrc \
            shaders.qrc \
            objects.qrc \
            robot.qrc \
	    cedar-bridge.qrc


HEADERS += \
    controller.h \
    cameramesh.h \
    gridmesh.h \
    linemesh.h \
    pathmesh.h \
    pointmesh.h \
    tools.h \
    cloudmesh.h \
    imagepainter.h \
    surfacemesh.h \
    customtype.h

CONFIG += link_pkgconfig
PKGCONFIG += eigen3 xslam-sdk

target.path = $$PREFIX/usr/bin
!isEmpty(target.path): INSTALLS += target
