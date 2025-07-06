#ifndef UDPCONTROLLER_HPP
#define UDPCONTROLLER_HPP

#include <QObject>
#include <QString>
#include "UdpReceiver.hpp"
#include "UdpSender.hpp"

class UdpController : public QObject {
    Q_OBJECT

    using UdpReceivers_t = QList<UdpReceiver*>;

    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)
    Q_PROPERTY(int receiverCount READ receiverCount NOTIFY connectedChanged)

    Q_PROPERTY(UdpReceivers_t receivers READ receivers NOTIFY receiversChanged)

    Q_PROPERTY(QString lastipadress READ lastipadress CONSTANT)
    Q_PROPERTY(QString lastPort READ lastPort CONSTANT)


public:    
    explicit UdpController (QObject *parent = nullptr);
    Q_INVOKABLE void startSender(const QString &ip, int port);
    Q_INVOKABLE void startReceiver(const QString &group, int port);
    Q_INVOKABLE void stopAll();
    Q_INVOKABLE bool isConnected() const;
    Q_INVOKABLE int receiverCount() const;
    Q_INVOKABLE int activeReceiverCount() const;

    UdpReceivers_t receivers()const { return _receivers; }

    QString lastipadress() const;
    QString lastPort() const;

public slots:
    void canMessageReceived(QCanBusFrame);

private:
    UdpSender *_sender =nullptr;
    UdpReceivers_t _receivers;

signals:
    void connectedChanged();

    void receiversChanged();
};

#endif
