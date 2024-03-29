#include <QTimer>

#include "canframecache.h"

CanFrameCache::CanFrameCache(QObject *parent)
    : QObject{parent}
{
    m_receiptTimer.setSingleShot(true);
    m_receiptTimer.setInterval(200);
    m_receiptTimer.callOnTimeout([this]() { handleLostOwnFrame(); });
}

QSet<int> CanFrameCache::enqueueIncomingFrames(const QVector<QCanBusFrame> &frameColl)
{
    auto ecuIdColl = QSet<int>{};
    for (const auto &frame : frameColl)
    {
        ecuIdColl.insert(frame.frameId());
        m_incomingCache[frame.frameId()].append(frame);
    }
    return ecuIdColl;
}

QVector<QCanBusFrame> CanFrameCache::takeIncomingFrames(int ecuId)
{
    return m_incomingCache.take(ecuId);
}

QCanBusFrame CanFrameCache::enqueueOutgoingFrame(const QCanBusFrame &frame)
{
    auto wasEmptyOnEntry = m_outgoingCache.isEmpty();

    m_outgoingCache.append(frame);
    if (wasEmptyOnEntry)
    {
        m_receiptTimer.start();
        return frame;
    }
    return c_invalidFrame;
}

QCanBusFrame CanFrameCache::dequeueOutgoingFrame()
{
    if (!m_outgoingCache.isEmpty())
    {
        m_receiptTimer.stop();
        m_outgoingCache.removeFirst();
    }
    if (!m_outgoingCache.isEmpty())
    {
        m_receiptTimer.start();
        return m_outgoingCache.first();
    }
    return c_invalidFrame;
}

void CanFrameCache::handleLostOwnFrame()
{
    auto lostFrame = c_invalidFrame;
    if (!m_outgoingCache.isEmpty())
    {
        lostFrame = m_outgoingCache.takeFirst();
    }
    auto nextFrame = c_invalidFrame;
    if (!m_outgoingCache.isEmpty())
    {
        nextFrame = m_outgoingCache.first();
    }
    emit ownFrameLost(lostFrame, nextFrame);
}

int CanFrameCache::sourceEcuId(const QCanBusFrame &frame) const
{
    return static_cast<int>(frame.frameId() & 0x000000FF);
}
