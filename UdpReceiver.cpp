#include "UdpReceiver.hpp"

UdpReceiver::UdpReceiver(QObject *parent)
    : QObject{parent}
{
    connect(&socket4, &QUdpSocket::readyRead, this, &UdpReceiver::processPendingDatagrams);
   // connect(&socket6, &QUdpSocket::readyRead, this, &UdpReceiver::processPendingDatagrams);
}

void UdpReceiver::start(const QString &groupAddress, quint16 port)
{
    stop();
    _port = port;

    groupAddress4 = QHostAddress(groupAddress);
   // groupAddress6 = groupAddress4.isNull() ? QHostAddress() : QHostAddress::Null;

    if (!socket4.bind(QHostAddress::AnyIPv4, _port, QUdpSocket::ShareAddress)) {
         qDebug() << "IPv4 bind failed";
        return;
    }
    socket4.joinMulticastGroup(groupAddress4);

    // if (!socket6.bind(QHostAddress::AnyIPv6, port, QUdpSocket::ShareAddress) ||
    //     !socket6.joinMulticastGroup(groupAddress6)) {
    //      qDebug() << "IPv6 bind or join multicast group failed";
    // }
   emit connectedChanged();
   qDebug() << QString("Receiver started. Listening on %1:%2").arg(groupAddress4.toString()).arg(_port);
}

void UdpReceiver::stop()
{
    if (socket4.state() == QAbstractSocket::BoundState) {
        socket4.close();
        qDebug() << "[socket4]-Receiver stopped. ";
    }
    // if (socket6.state() == QAbstractSocket::BoundState) {
    //     socket6.close();
    //     qDebug() << "[socket6]-Receiver stopped. ";
    // }
    emit connectedChanged();
}

bool UdpReceiver::isConnected() const
{
    qDebug() << "[socket4]-Receiver state. " << socket4.state();
    return socket4.state() == QAbstractSocket::BoundState;

}

void UdpReceiver::processPendingDatagrams()
{
    while (socket4.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket4.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socket4.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        qDebug() << QString("Received from %1:%2 → %3").arg(sender.toString()).arg(senderPort).arg(QString(datagram));

    }

    // while (socket6.hasPendingDatagrams()) {
    //     QByteArray datagram;
    //     datagram.resize(socket6.pendingDatagramSize());
    //     QHostAddress sender;
    //     quint16 senderPort;
    //     socket6.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
    // }
}
