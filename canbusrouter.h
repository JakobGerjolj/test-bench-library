#ifndef CANBUSROUTER_H
#define CANBUSROUTER_H

#include <QCanBusDevice>
#include "canframecache.h"

class CanBusRouter : public QObject
{
    Q_OBJECT
public:
    explicit CanBusRouter(int canId, const QString &plugin, const QString &interface, QObject *parent = nullptr);
    virtual ~CanBusRouter();

    QCanBusDevice::CanBusError error() const;

    QString errorString() const;
    QCanBusDevice::CanBusDeviceState state() const;
    QVector<QCanBusFrame> takeReceivedFrames(int sourceEcuId);

    bool isReceiveOwnFrameEnabled() const;
    void setReceiveOwnFrameEnabled(bool enabled);
    void addChargerDCDCid(quint16 id);





signals:
    void errorOccurred();
    void framesReceived(const QSet<int> &ecuIdColl);
    void framesWritten(qint64 framesCount);

public slots:
    void writeFrame(const QCanBusFrame &frame);

protected:
    QCanBusDevice* m_device{nullptr};

private slots:
    void onErrorOccurred(QCanBusDevice::CanBusError error);
    void onFramesReceived();

private:
    QCanBusDevice *createDevice(const QString &plugin, const QString &interface);
    void connectToDevice();
    void disconnectFromDevice();
    QVector<QCanBusFrame> readAllFrames();


    int m_canId{-1};
    QCanBusDevice::CanBusError m_error{QCanBusDevice::CanBusError::NoError};
    QString m_errorStr;
    QCanBusDevice::CanBusDeviceState m_state;
    CanFrameCache m_frameCache;

    quint16 m_dcdcChargerId{0};
    quint16 m_dcdcInverterId{0};
    quint16 m_acdcCharger2Id{0};
    quint16 m_acdcInverter1Id{0};
    quint16 m_acdcInverter2Id{0};
    quint16 m_acdcInverter3Id{0};
    quint16 m_bmsId{0};
    quint16 m_imdId{0};
    void writeQueuedFrame(const QCanBusFrame &frame);
};

#endif // CANBUSROUTER_H
