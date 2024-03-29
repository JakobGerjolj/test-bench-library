#include "keycardsactuator.h"

#include <QDebug>

KeyCardsActuator::KeyCardsActuator(QSerialPort *serial, QObject *parent)
    : QObject(parent)
    , m_serial(serial)
{
    connect(m_serial, &QSerialPort::readyRead, this, &KeyCardsActuator::handleReadyRead);
}

void KeyCardsActuator::approchLeftCard()
{
    m_serial->write(QByteArray{"1\r\n"});
    m_serial->flush();
}

void KeyCardsActuator::approchRightCard()
{
    m_serial->write(QByteArray{"2\r\n"});
    m_serial->flush();
}

int KeyCardsActuator::leftCardStatus() const
{
    return m_leftCardStatus;
}

int KeyCardsActuator::rightCardStatus() const
{
    return m_rightCardStatus;
}

void KeyCardsActuator::setLeftCardStatus(int leftCardStatus)
{
    if (m_leftCardStatus == leftCardStatus)
        return;

    m_leftCardStatus = leftCardStatus;
    emit leftCardStatusChanged(m_leftCardStatus);
}

void KeyCardsActuator::setRightCardStatus(int rightCardStatus)
{
    if (m_rightCardStatus == rightCardStatus)
        return;

    m_rightCardStatus = rightCardStatus;
    emit rightCardStatusChanged(m_rightCardStatus);
}

void KeyCardsActuator::handleReadyRead()
{
    auto readData = m_serial->readLine();

    QString data = readData.simplified();

    if(data == "left home")
        setLeftCardStatus(1);

    if(data == "left approached")
        setLeftCardStatus(2);

    if(data == "right home")
        setRightCardStatus(1);

    if(data == "right approached")
        setRightCardStatus(2);

}
