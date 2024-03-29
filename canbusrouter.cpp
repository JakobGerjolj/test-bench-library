#include <QCanBus>
#include <QCanBus>
#include <qdebug.h>
#include "qvariant.h"

#include "canbusrouter.h"


CanBusRouter::CanBusRouter(int canId, const QString &plugin, const QString &interface, QObject *parent)
    :QObject(parent)
{
    m_canId = canId;
    m_device = createDevice(plugin, interface);

    if (m_device == nullptr)
    {
        return;
    }
    connectToDevice();
    connect(m_device, &QCanBusDevice::errorOccurred,
            this, &CanBusRouter::onErrorOccurred);
    connect(m_device, &QCanBusDevice::framesReceived,
            this, &CanBusRouter::onFramesReceived,
            Qt::QueuedConnection);

    connect(m_device, &QCanBusDevice::framesWritten,
            this, &CanBusRouter::framesWritten);

    connect(m_device, &QCanBusDevice::framesReceived,
            this, &CanBusRouter::onFramesReceived,
            Qt::QueuedConnection);
}

CanBusRouter::~CanBusRouter()
{
    disconnectFromDevice();
    delete m_device;
}

QCanBusDevice::CanBusError CanBusRouter::error() const
{
    return m_error;
}

QString CanBusRouter::errorString() const
{
    return m_errorStr;
}

QCanBusDevice::CanBusDeviceState CanBusRouter::state() const
{
    return m_state;
}

QVector<QCanBusFrame> CanBusRouter::takeReceivedFrames(int ecuId)
{
    if (m_device == nullptr)
    {
        return {};
    }
    return m_frameCache.takeIncomingFrames(ecuId);
}

bool CanBusRouter::isReceiveOwnFrameEnabled() const
{
    if (m_device == nullptr)
    {
        return false;
    }
    return m_device->configurationParameter(QCanBusDevice::ReceiveOwnKey).toBool();
}

QCanBusDevice *CanBusRouter::createDevice(const QString &plugin, const QString &interface)
{
    auto device = QCanBus::instance()->createDevice(plugin, interface, &m_errorStr);
    if (!m_errorStr.isEmpty())
    {
        m_error = QCanBusDevice::CanBusError::ConnectionError;
    }
    return device;
}

void CanBusRouter::connectToDevice()
{
    if (m_device == nullptr)
    {
        return;
    }
    if (!m_device->connectDevice())
    {
        m_error = m_device->error();
        m_errorStr = m_device->errorString();
    }
    m_state = m_device->state();
}

void CanBusRouter::disconnectFromDevice()
{
    if (m_device == nullptr)
    {
        return;
    }
    if (m_device->state() == QCanBusDevice::ConnectedState)
    {
        m_device->disconnectDevice();
    }
}

void CanBusRouter::onErrorOccurred(QCanBusDevice::CanBusError error)
{
    m_error = error;
    m_errorStr = m_device->errorString();
    emit errorOccurred();
}

void CanBusRouter::onFramesReceived()
{
    if (m_device == nullptr)
        return;

    auto ecuIdColl = m_frameCache.enqueueIncomingFrames(readAllFrames());
    emit framesReceived(ecuIdColl);

}

void CanBusRouter::writeFrame(const QCanBusFrame &frame)
{
    if (m_device == nullptr)
        return;

    m_device->writeFrame(frame);
}

void CanBusRouter::setReceiveOwnFrameEnabled(bool enabled)
{
    if (m_device == nullptr)
    {
        return;
    }
    m_device->setConfigurationParameter(QCanBusDevice::ReceiveOwnKey, true);
}



QVector<QCanBusFrame> CanBusRouter::readAllFrames()
{
    return m_device->readAllFrames();
}

void CanBusRouter::writeQueuedFrame(const QCanBusFrame &frame)
{
    if (frame.isValid())
    {
        m_device->writeFrame(frame);
    }
}
