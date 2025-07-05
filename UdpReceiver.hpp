#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>

class UdpReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)

public:
    explicit UdpReceiver(QObject *parent = nullptr);
    void start(const QString &groupAddress, quint16 port);
    void stop();
    bool isConnected() const;

signals:
    void connectedChanged();
    void log(const QString &msg);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket socket4;
    QUdpSocket socket6;
    QHostAddress groupAddress4;
    QHostAddress groupAddress6;
    quint16 _port = 0;
};

#endif // UDPRECEIVER_H
