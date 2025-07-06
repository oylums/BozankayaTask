#include "Application.hpp"
#include <QQmlContext>
#include "AppMessages.hpp"

Application* Application::_app{nullptr};

Application::Application(int argc, char **argv)
    : QGuiApplication(argc,argv)
    , _engine(new QQmlApplicationEngine(this))
{
    _app = this;
}

Application::~Application()
{
    delete _engine;
}

void Application::initCommon()
{
    qmlRegisterUncreatableType<UdpController>("UDP.CONT",1,0,"UDP","Ref only");
    qmlRegisterUncreatableType<UdpReceiver>("UDP.CONT",1,0,"UDPReceiver","Ref only");
    qmlRegisterUncreatableType<XmlController>("XML.CONT",1,0,"XML","Ref only");
    qmlRegisterUncreatableType<AppLogModel>("LOG.MOD",1,0,"LOG_MODEL","Ref only");
    qmlRegisterUncreatableType<CanInterfaceController>("CAN.COMM",1,0,"CAN_COMM","Ref only");
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
