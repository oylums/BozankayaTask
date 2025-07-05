#ifndef UDPSENDER_H
#define UDPSENDER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>

class UdpSender : public QObject
{
    Q_OBJECT
public:
    explicit UdpSender(QObject *parent = nullptr);
    void start(const QString &groupAddress, quint16 port);
    void stop();

signals:
    void log(const QString &msg);

private slots:
    void sendDatagram();

private:
    QUdpSocket socket4;
    QUdpSocket socket6;
    QTimer timer;
    QHostAddress groupAddress4;
    QHostAddress groupAddress6;
    int messageNo = 0;
    quint16 _port = 0;
};

#endif // UDPSENDER_H
