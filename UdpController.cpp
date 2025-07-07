#include "UdpController.hpp"
#include <QDebug> // loglamak için

UdpController::UdpController(QObject *parent)
{
    //connect(_receiver, &UdpReceiver::connectedChanged, this, &UdpController::connectedChanged);
}


void UdpController::startSender(const QString &ip, int port)
{
    if (_sender) {
        delete _sender;
    }
    _sender = new UdpSender(this);
    _sender->start(ip, port);
    emit connectedChanged();
    connect(_sender, &UdpSender::connectedChanged, this, &UdpController::connectedChanged);
}



void UdpController::startReceiver(const QString &group, int port)
{
    auto *receiver = new UdpReceiver(this);
    receiver->start(group, port);
    _receivers.append(receiver);

    qDebug() << QString("Added new UDP listener→ %1:%2 | Toplam: %3")
                    .arg(group)
                    .arg(port)
                    .arg(_receivers.size());

    emit receiversChanged();

    emit connectedChanged();
}

void UdpController::stopAll()
{
    if (_sender) {
        _sender->stop();
        delete _sender;
        _sender = nullptr;
    }

    for (auto *r : _receivers) {
        r->stop();
        r->deleteLater();
    }

    _receivers.clear();

    qDebug() << "UDP Stopped";
    emit connectedChanged();
}

bool UdpController::isConnected() const
{
    return (_sender && _sender->isConnected()) || activeReceiverCount() > 0;
}

int UdpController::receiverCount() const
{
    return _receivers.size();
}

int UdpController::activeReceiverCount() const
{
    int count = 0;
    for (const auto* r : _receivers) {
        if (r->isConnected())
            count++;
    }
    return count;
}

QString UdpController::lastipadress() const
{
    QSettings settings;
    return settings.value("ipadress","0.0.0.0").toString();
}

QString UdpController::lastPort() const
{
    QSettings settings;
    return settings.value("port","45454").toString();
}

  // <-- Port burada kaydediliyor

void UdpController::canMessageReceived(QCanBusFrame frame)
{
    QByteArray payload;
    payload.append(static_cast<char>((frame.frameId() >> 24) & 0xFF));
    payload.append(static_cast<char>((frame.frameId() >> 16) & 0xFF));
    payload.append(static_cast<char>((frame.frameId() >> 8) & 0xFF));
    payload.append(static_cast<char>((frame.frameId()) & 0xFF));
    payload.append(frame.payload());

    _sender->sendByteArrayWithDatagram(payload);
}
