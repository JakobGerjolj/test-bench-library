#ifndef TESTBENCHLIBRARY_H
#define TESTBENCHLIBRARY_H

#include <QDebug>
#include "test-bench-library_global.h"
#include "keycardsactuator.h"
#include "leversactuator.h"
#include "buttons.h"
#include "canbusrouter.h"

class TESTBENCHLIBRARY_EXPORT TestBenchLibrary
{

public:
    explicit TestBenchLibrary();
    explicit TestBenchLibrary(QSerialPort* serial_levers,QSerialPort* serial_keyCards,QString can_bus);
    void startReadingCan();
    void moveCorrectCard();
    void moveWrongCard();

private:
    LeversActuator* m_leversActuator;
    KeyCardsActuator* m_keyCardsActuator;
    Buttons* m_buttons;
    CanBusRouter* m_canBusRouter;
    CanFrameCache* m_canFrameCache;

};

#endif // TESTBENCHLIBRARY_H
