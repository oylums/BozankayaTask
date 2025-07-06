#include "UdpReceiver.hpp"

UdpReceiver::UdpReceiver(QObject *parent)
    : QObject{parent}
{
    connect(&socket, &QUdpSocket::readyRead, this, &UdpReceiver::processPendingDatagrams);

}

void UdpReceiver::start(const QString &groupAddress, quint16 port)
{
    stop();
    _port = port;

    _groupAddress = QHostAddress(groupAddress);

    QSettings settings;
    settings.setValue("ipadress", groupAddress);
    settings.setValue("port", _port);

    if (!socket.bind(QHostAddress::AnyIPv4, _port, QUdpSocket::ShareAddress)) {
         qDebug() << "IPv4 bind failed";
        return;
    }
    socket.joinMulticastGroup(_groupAddress);

   emit connectedChanged();    
   qDebug() << QString("Receiver started. Listening on %1:%2").arg(_groupAddress.toString()).arg(_port);
}

void UdpReceiver::stop()
{
    if (socket.state() == QAbstractSocket::BoundState) {
        socket.close();
        qDebug() << "[socket4]-Receiver stopped. ";
    }
    emit connectedChanged();
}

bool UdpReceiver::isConnected() const
{
    qDebug() << "[socket4]-Receiver state. " << socket.state();
    return socket.state() == QAbstractSocket::BoundState;

}

void UdpReceiver::processPendingDatagrams()
{
    while (socket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        qDebug() << QString("Received from %1:%2 → %3").arg(sender.toString()).arg(senderPort).arg(QString(datagram));

    }

}
