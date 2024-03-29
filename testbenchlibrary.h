#ifndef TESTBENCHLIBRARY_H
#define TESTBENCHLIBRARY_H

#include "test-bench-library_global.h"
#include "keycardsactuator.h"
#include "leversactuator.h"
#include "buttons.h"

class TESTBENCHLIBRARY_EXPORT TestBenchLibrary
{

public:
    TestBenchLibrary();

private:
    LeversActuator* m_leversActuator;
    KeyCardsActuator* m_keyCardsActuator;
    Buttons* m_buttons;

};

#endif // TESTBENCHLIBRARY_H
