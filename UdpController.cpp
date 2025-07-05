#include "UdpController.hpp"
#include <QDebug> // loglamak için

UdpController::UdpController(QObject *parent)
{
    _sender = new UdpSender(this);
    _receiver = new UdpReceiver(this);

    // connect(_sender, &UdpSender::log, this, &UdpController::log);
    // connect(_receiver, &UdpReceiver::log, this, &UdpController::log);

}


void UdpController::startSender(const QString &ip, int port)
{
    qDebug() << "[UdpController] Sender başlatılıyor → IP:" << ip << " Port:" << port;
    _sender->start("192.168.1.12",45454);
}



void UdpController::startReceiver(const QString &group, int port)
{
    qDebug() << "[UdpController] Sender başlatılıyor → Group:" << group << " Port:" << port;
    _receiver->start(group,port);

}



void UdpController::stopAll()
{
    _sender->stop();
    _receiver->stop();
}



