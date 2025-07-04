#include "Application.hpp"

#include <QQmlContext>

Application* Application::_app{nullptr};

Application::Application(int argc, char **argv)
    : QGuiApplication(argc,argv)
    , _engine(new QQmlApplicationEngine(this))
{
    _app = this;
}

Application::~Application()
{
    qDebug() << "App closed successfully";
}

void Application::initCommon()
{
    // class A;
    // qmlRegisterUncreatableType<A>("QBATask.A",1,0,"A","Ref only");
}

void Application::init()
{
    const QUrl url(QStringLiteral("qrc:/qml/QBATask/MainWindow/main.qml"));

    connect(_engine,&QQmlApplicationEngine::objectCreated,this,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    _engine->rootContext()->setContextProperty("qmlGlobal",&_qmlGlobal);

    _engine->load(url);
}

Application *app()
{
    return Application::_app;
}
