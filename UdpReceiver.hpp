#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>

class UdpReceiver : public QObject
{
    Q_OBJECT
public:
    explicit UdpReceiver(QObject *parent = nullptr);
    void start(const QString &groupAddress, quint16 port);
    void stop();

signals:
    void log(const QString &msg);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket socket4;
    QUdpSocket socket6;
    QHostAddress groupAddress4;
    QHostAddress groupAddress6;
signals:
};

#endif // UDPRECEIVER_H
