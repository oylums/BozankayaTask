#include "UdpController.hpp"
#include <QDebug> // loglamak için

UdpController::UdpController(QObject *parent)
{
    _sender = new UdpSender(this);
    _receiver = new UdpReceiver(this);

    connect(_sender, &UdpSender::connectedChanged, this, &UdpController::connectedChanged);
    connect(_receiver, &UdpReceiver::connectedChanged, this, &UdpController::connectedChanged);


}


void UdpController::startSender(const QString &ip, int port)
{
    //connect(_sender, &UdpSender::connectedChanged, this, &UdpController::connectedChanged);
    qDebug() << "[UdpController] Sender başlatılıyor → IP:" << ip << " Port:" << port;
    _sender->start(ip,port);
}



void UdpController::startReceiver(const QString &group, int port)
{
    //connect(_receiver, &UdpReceiver::connectedChanged, this, &UdpController::connectedChanged);
    qDebug() << "[UdpController] Receiver başlatılıyor → Group:" << group << " Port:" << port;
    _receiver->start(group,port);
}



void UdpController::stopAll()
{
    _sender->stop();
    _receiver->stop();
}

bool UdpController::isConnected() const
{

    return (_sender && _sender->isConnected()) || (_receiver && _receiver->isConnected());

}



