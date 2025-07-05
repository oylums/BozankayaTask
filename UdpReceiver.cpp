#include "UdpReceiver.hpp"

UdpReceiver::UdpReceiver(QObject *parent)
    : QObject{parent}
{
    connect(&socket4, &QUdpSocket::readyRead, this, &UdpReceiver::processPendingDatagrams);
    connect(&socket6, &QUdpSocket::readyRead, this, &UdpReceiver::processPendingDatagrams);
}

void UdpReceiver::start(const QString &groupAddress, quint16 port)
{
    stop();

    groupAddress4 = QHostAddress(groupAddress);
    groupAddress6 = groupAddress4.isNull() ? QHostAddress() : QHostAddress::Null;

    if (!socket4.bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress)) {
        emit log("IPv4 bind failed");
         qDebug() << "IPv4 bind failed";
        return;
    }
    socket4.joinMulticastGroup(groupAddress4);

    if (!socket6.bind(QHostAddress::AnyIPv6, port, QUdpSocket::ShareAddress) ||
        !socket6.joinMulticastGroup(groupAddress6)) {
        emit log("IPv6 bind or join multicast group failed");
         qDebug() << "IPv6 bind or join multicast group failed";
    }

    emit log(QString("Receiver started. Listening on %1:%2").arg(groupAddress).arg(port));
    qDebug() << "Receiver started. Listening on %1:%2";
}

void UdpReceiver::stop()
{
    if (socket4.state() == QAbstractSocket::BoundState) {
        socket4.close();
    }
    if (socket6.state() == QAbstractSocket::BoundState) {
        socket6.close();
    }

    emit log("Receiver stopped.");
}

void UdpReceiver::processPendingDatagrams()
{
    while (socket4.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket4.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socket4.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        emit log(QString("IPv4 Received from %1:%2 - %3").arg(sender.toString()).arg(senderPort).arg(QString(datagram)));
    }

    while (socket6.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket6.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socket6.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        emit log(QString("IPv6 Received from %1:%2 - %3").arg(sender.toString()).arg(senderPort).arg(QString(datagram)));
    }
}
