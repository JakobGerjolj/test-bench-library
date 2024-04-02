#include "testbenchlibrary.h"

TestBenchLibrary::TestBenchLibrary()
{

}

TestBenchLibrary::TestBenchLibrary(QSerialPort* serial_levers, QSerialPort* serial_keyCards, QString can_bus)
{
    m_canBusRouter= new CanBusRouter(1,"socketcan", can_bus);
    // m_leversActuator= new LeversActuator(serial_levers);
    // m_keyCardsActuator= new KeyCardsActuator(serial_keyCards);
    // m_buttons = new Buttons;

}

void TestBenchLibrary::startReadingCan()
{
    m_canBusRouter->takeReceivedFrames(1);
}

void TestBenchLibrary::moveCorrectCard()
{
    //m_keyCardsActuator->approchRightCard();
    qDebug()<<"Moved right card";
}

void TestBenchLibrary::moveWrongCard()
{
    //m_keyCardsActuator->approchLeftCard();
    qDebug()<<"Moved wrong card";
}
