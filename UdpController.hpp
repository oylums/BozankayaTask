#ifndef UDPCONTROLLER_HPP
#define UDPCONTROLLER_HPP

#include <QObject>
#include <QString>
#include "UdpReceiver.hpp"
#include "UdpSender.hpp"

class UdpController : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)
public:
    explicit UdpController (QObject *parent = nullptr);
    Q_INVOKABLE void startSender(const QString &ip, int port);
    Q_INVOKABLE void startReceiver(const QString &group, int port);
    Q_INVOKABLE void stopAll();
    Q_INVOKABLE bool isConnected() const;

private:
    UdpSender *_sender =nullptr;
    UdpReceiver *_receiver= nullptr;

signals:
    void connectedChanged();
};

#endif
