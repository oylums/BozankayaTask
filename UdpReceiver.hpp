#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>

#include <QCanBusFrame>
#include <QSettings>

class UdpReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)
    Q_PROPERTY(QString ipAddress READ ipAddress NOTIFY connectedChanged)
    Q_PROPERTY(QString port READ port NOTIFY connectedChanged)

public:
    explicit UdpReceiver(QObject *parent = nullptr);
    void start(const QString &groupAddress, quint16 port);
    void stop();
    bool isConnected() const;

    QString ipAddress() const { return _groupAddress.toString(); }
    QString port() const { return QString::number(socket.localPort()); }

signals:
    void connectedChanged();
    void log(const QString &msg);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket socket;
    QHostAddress _groupAddress;
    quint16 _port = 0;
};



#endif // UDPRECEIVER_H
