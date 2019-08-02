#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QCommandLineParser>
#include <QCommandLineOption>

#include "pointmesh.h"
#include "linemesh.h"
#include "pathmesh.h"
#include "gridmesh.h"
#include "cameramesh.h"
#include "cloudmesh.h"
#include "surfacemesh.h"

#include "imagepainter.h"

#include "controller.h"
#include "tools.h"


#include <xslam/xslam_sdk.hpp>


#include <iostream>

void xslam_smooth_motion(bool);

int main(int argc, char *argv[])
{
    xslam_disp_version();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setApplicationName("AR Demo");
    app.setOrganizationName("XVisio");

    qmlRegisterType<PointMesh>("PointMesh",1,0,"PointMesh");
    qmlRegisterType<LineMesh>("LineMesh",1,0,"LineMesh");
    qmlRegisterType<PathMesh>("PathMesh",1,0,"PathMesh");
    qmlRegisterType<GridMesh>("GridMesh",1,0,"GridMesh");
    qmlRegisterType<CameraMesh>("CameraMesh",1,0,"CameraMesh");
    qmlRegisterType<CloudMesh>("CloudMesh",1,0,"CloudMesh");
    qmlRegisterType<SurfaceMesh>("SurfaceMesh",1,0,"SurfaceMesh");
    qmlRegisterType<ImagePainter>("ImagePainter", 1, 0, "ImagePainter");

    Controller c;
    Tools t;

    QCommandLineParser parser;
    parser.setApplicationDescription("XVisio AR Demo");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption forceOption(QStringList() << "f" << "forceOpenGL", QCoreApplication::translate("main", "Force use OpenGL 4.3"));
    parser.addOption(forceOption);

    parser.process(app);

    if( parser.isSet(forceOption) ){
        QSurfaceFormat format = QSurfaceFormat::defaultFormat();
        //format.setSwapInterval(2); //render 50% of frames
        if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
            format.setVersion(4, 3);
            format.setProfile(QSurfaceFormat::CoreProfile);
        }
        format.setDepthBufferSize(24);
        format.setSamples(4);
        format.setStencilBufferSize(8);
        QSurfaceFormat::setDefaultFormat(format);
    }


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("control", &c);
    engine.rootContext()->setContextProperty("tools", &t);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    xslam_smooth_motion(false);
    xslam_disp_version();

    int out = app.exec();

    qDebug() << "Stopping";

    xslam_stop();

    qDebug() << "Stopped";

    return out;
}

