#include "UdpSender.hpp"
#include <QDateTime>

UdpSender::UdpSender(QObject *parent)
    : QObject{parent}
{
    connect(&timer, &QTimer::timeout, this, &UdpSender::sendDatagram);

}

void UdpSender::start(const QString &groupAddress, quint16 port)
{
    stop();

    groupAddress4 = QHostAddress(groupAddress);
    groupAddress6 = groupAddress4.isNull() ? QHostAddress() : QHostAddress::Null;
    _port = port;
    qDebug()<< _port;

    socket4.bind(QHostAddress::AnyIPv4, 0); // sender da bind gerekmez
    socket6.bind(QHostAddress::AnyIPv6, socket4.localPort());

    messageNo = 0;
    timer.start(1000);

    emit connectedChanged();
}


void UdpSender::stop()
{
    timer.stop();
    if (socket4.state() == QAbstractSocket::BoundState) {
        socket4.close();
    }
    if (socket6.state() == QAbstractSocket::BoundState) {
        socket6.close();
    }
    emit connectedChanged();
}

bool UdpSender::isConnected() const
{
    qDebug() << "[socket4]-Sender state. " << socket4.state();
    return socket4.state() == QAbstractSocket::BoundState;
}

void UdpSender::sendDatagram()
{
    if (_port == 0 || groupAddress4.isNull()) return;

    QByteArray datagram = "Multicast message " + QByteArray::number(messageNo++);
    qDebug() << socket4.state();
    if (socket4.state() == QAbstractSocket::BoundState){
        socket4.writeDatagram(datagram, groupAddress4, _port);
        qDebug() << QString("socket4 send datagram run c: %1 s: %2").arg(socket4.error()).arg(socket4.errorString());
    }
    if (socket6.state() == QAbstractSocket::BoundState){
        socket6.writeDatagram(datagram, groupAddress6, _port);
        qDebug() << QString("socket6 send datagram run c: %1 s: %2").arg(socket6.error()).arg(socket6.errorString());
    }
}

