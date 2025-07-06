#include "CanController.hpp"
#include <QCanBus>
#include <QCanBusFrame>
#include <QProcess>
#include <QVariant>
#include <QDebug>

CanInterfaceController::CanInterfaceController(QObject *parent)
    : QObject(parent)
{
}

void CanInterfaceController::start(const QString &interface, int bitrate)
{
    //stop();

    m_interface = interface;

    if (interface == "can1") {
        QProcess::execute("ip", {"link", "set", "can1", "down"});
        QProcess::execute("ip", {"link", "set", "can1", "type", "can", "bitrate", QString::number(bitrate)});
        QProcess::execute("ip", {"link", "set", "can1", "up"});
    }


    QString error;
    m_device.reset(QCanBus::instance()->createDevice("socketcan", interface, &error));
    if (!m_device) {
        qWarning() << "CAN device create error:" << error;
        return;
    }

    if (interface == "vcan0") {
        m_device->setConfigurationParameter(QCanBusDevice::BitRateKey, QVariant()); // bitrate i default ayarma engellensin diye ekledin.
    }
    if (!m_device->connectDevice()) {
        qWarning() << "CAN connect error:" << m_device->errorString();
        m_device.reset();
        return;
    }


   connect(m_device.get(), &QCanBusDevice::framesReceived, this, &CanInterfaceController::onFramesReceived);
    emit connectedChanged();
 }

void CanInterfaceController::stop()
{
    if (m_device) {
        m_device->disconnectDevice();
        m_device.reset();
        emit connectedChanged();
    }

    if (!m_interface.isEmpty()) {
        QProcess::execute("İP", {"link", "set", m_interface, "down"});
        m_interface.clear();
    }
}

void CanInterfaceController::sendFrame(quint32 id, const QByteArray &data)
{
    if (!m_device) return;

    QCanBusFrame frame(id, data);
    m_device->writeFrame(frame);
}

bool CanInterfaceController::isConnected() const
{
    return m_device && m_device->state() == QCanBusDevice::ConnectedState;
}

void CanInterfaceController::onFramesReceived()
{
    while (m_device->framesAvailable()) {
        QCanBusFrame frame = m_device->readFrame();
        emit messageReceived(QVariant::fromValue(frame));

        qDebug() << "Frame received:";
        qDebug() << "  ID:" << QString("0x%1").arg(frame.frameId(), 0, 16).toUpper();
        qDebug() << "  Data:" << frame.payload().toHex(' ').toUpper();
    }
}
