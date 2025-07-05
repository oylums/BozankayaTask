#include "QmlGlobal.hpp"


QmlGlobal::QmlGlobal(QObject *parent)
    : QObject(parent)
{
     _udpController = new UdpController(this);
     _xmlController=new XmlController(this);
}

UdpController* QmlGlobal::udpController() const
{
    return _udpController;
}

XmlController* QmlGlobal::xmlController() const
{
    return _xmlController;
}

AppLogModel *QmlGlobal::logModel() const
{
    return AppMessages::getModel();
}
