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

    // Bind sockets
    socket4.bind(QHostAddress::AnyIPv4, 0);
    socket6.bind(QHostAddress::AnyIPv6, socket4.localPort());

    messageNo = 0;
    timer.start(1000);

    emit log(QString("Sender started. Sending to %1:%2").arg(groupAddress).arg(port));
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
    emit log("Sender stopped.");
}

void UdpSender::sendDatagram()
{
    QByteArray datagram = "Multicast message " + QByteArray::number(messageNo++);
    quint16 port = 45454; // port ve ip yi dinamik yapmayı unutma oylum

    socket4.writeDatagram(datagram, groupAddress4, port);
    if (socket6.state() == QAbstractSocket::BoundState)
        socket6.writeDatagram(datagram, groupAddress6, port);

    emit log(QString("Sent: %1").arg(QString(datagram)));
}
