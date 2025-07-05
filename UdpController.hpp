#ifndef UDPCONTROLLER_HPP
#define UDPCONTROLLER_HPP

#include <QObject>
#include <QString>
#include "UdpReceiver.hpp"
#include "UdpSender.hpp"

class UdpController : public QObject {
    Q_OBJECT
public:
    explicit UdpController (QObject *parent = nullptr);
    Q_INVOKABLE void startSender(const QString &ip, int port);
    Q_INVOKABLE void startReceiver(const QString &group, int port);
    Q_INVOKABLE void stopAll();

private:
    UdpSender *_sender =nullptr;
    UdpReceiver *_receiver= nullptr;
};

#endif
