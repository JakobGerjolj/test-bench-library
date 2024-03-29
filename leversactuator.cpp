#include "leversactuator.h"

#include <QDebug>
#include <QTimer>


LeversActuator::LeversActuator(QSerialPort *serial, QObject *parent)
    :QObject(parent)
    ,m_serial(serial)
{
    connect(m_serial, &QSerialPort::readyRead, this, &LeversActuator::handleReadyRead);
    QTimer::singleShot(1000, this, &LeversActuator::home);
}

void LeversActuator::home()
{
    m_serial->write(QByteArray{"<home>\r\n"});
    m_serial->flush();
}

void LeversActuator::homeLeft()
{
    m_serial->write(QByteArray{"<homeLeft>\r\n"});
    m_serial->flush();
}

void LeversActuator::homeRight()
{
    m_serial->write(QByteArray{"<homeRight>\r\n"});
    m_serial->flush();
}

void LeversActuator::move(LeversActuator::Lever lever, LeversActuator::Direction direction, int steps)
{
    int leverInt = 0;
    int dirInt = 0;

    switch (lever) {
    case Lever::left:
        leverInt = 1;
        break;
    case Lever::right:
        leverInt = 2;
        break;
    }

    switch (direction) {
    case Direction::forward:
        dirInt = 1;
        break;
    case Direction::reverse:
        dirInt = 2;
        break;
    }

    auto command = QString("<move, %1, %2, %3>\r\n").arg(leverInt).arg(dirInt).arg(steps);
    //    auto command = QString("<move, %1, 2, %3>\r\n").arg(leverInt).arg(steps);

    m_serial->write(command.toUtf8());
    m_serial->flush();
}

void LeversActuator::moveBoth(LeversActuator::Direction direction, int steps)
{
    int dirInt = 0;

    switch (direction) {
    case Direction::forward:
        dirInt = 1;
        break;
    case Direction::reverse:
        dirInt = 2;
        break;
    }

    auto command = QString("<moveBoth, 0, %2, %3>\r\n").arg(dirInt).arg(steps);

    m_serial->write(command.toUtf8());
    m_serial->flush();
}

void LeversActuator::moveTest()
{
    move(right, forward, 400);
}

void LeversActuator::startMoving()
{
    m_serial->write(QByteArray{"<moving>\r\n"});
    m_serial->flush();
}

void LeversActuator::stopMoving()
{
    m_serial->write(QByteArray{"<stop>\r\n"});
    m_serial->flush();
}

int LeversActuator::leftPosition() const
{
    return m_leftPosition;
}

int LeversActuator::rightPosition() const
{
    return m_rightPosition;
}



void LeversActuator::setLeftPosition(int leftPosition)
{
    if (m_leftPosition == leftPosition)
        return;

    m_leftPosition = leftPosition;
    emit leftPositionChanged(m_leftPosition);
}

void LeversActuator::setRightPosition(int rightPosition)
{
    if (m_rightPosition == rightPosition)
        return;

    m_rightPosition = rightPosition;
    emit rightPositionChanged(m_rightPosition);
}



void LeversActuator::handleReadyRead()
{
    auto readData = m_serial->readAll();

    //    qDebug() << readData;
    QString data = readData.simplified();



    //    if(m_isInit)
    //    {
    //        if(data == "l:1-")
    //            setLeftPosition(leftPosition() - 1);

    //        if(data == "l:1+")
    //            setLeftPosition(leftPosition() + 1);

    //        if(data == "r:1-")
    //            setRightPosition(rightPosition() - 1);

    //        if(data == "r:1+")
    //            setRightPosition(rightPosition() + 1);

    //        if(data == "b:1-")
    //        {
    //            setLeftPosition(leftPosition() - 1);
    //            setRightPosition(rightPosition() - 1);
    //        }

    //        if(data == "b:1+")
    //        {
    //            setLeftPosition(leftPosition() + 1);
    //            setRightPosition(rightPosition() + 1);
    //        }
    //    } else {
    //        if(data == "homeRight")
    //            m_isHomeRight = true;

    //        if(data == "homeLeft")
    //            m_isHomeLeft = true;

    //        if(m_isHomeLeft && m_isHomeRight)
    //        {
    //            m_isInit = true;
    //            qDebug() << "INIT";
    //        }
    //    }
}
