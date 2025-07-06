#ifndef CANINTERFACECONTROLLER_HPP
#define CANINTERFACECONTROLLER_HPP

#include <QObject>
#include <QCanBusDevice>
#include <memory>

class CanInterfaceController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)

public:
    explicit CanInterfaceController(QObject *parent = nullptr);

    Q_INVOKABLE void start(const QString &interface, int bitrate = 500000);
    Q_INVOKABLE void stop();
    Q_INVOKABLE void sendFrame(const QString &idHex, const QString &dataHex);
    bool isConnected() const;

signals:
    void connectedChanged();
    void messageReceived(QVariant frame);

private slots:
    void onFramesReceived();

private:
    std::unique_ptr<QCanBusDevice> m_device;
    QString m_interface;
};

#endif // CANINTERFACECONTROLLER_HPP
