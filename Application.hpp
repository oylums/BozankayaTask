#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "QmlGlobal.hpp"

class Application : public QGuiApplication
{
    Q_OBJECT

public:
    Application(int argc,char** argv);
    ~Application();

    static Application* _app;

    void initCommon();
    void init();

private:
    QQmlApplicationEngine* _engine;
    QmlGlobal _qmlGlobal;
};

Application* app();

#endif
