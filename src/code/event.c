#include <xc.h>
#include <pic18f4550.h>
#include "headers/event.h"
#include "headers/defines.h"
#include "headers/delay.h"
#include "headers/ADC.h"
#include "headers/button.h"
#include "headers/LCD.h"
#include "headers/serial.h"
#include "headers/variables.h"

static unsigned char isCommand;

void eventInit(void) {
    adcInit();
    buttonInit();
    serialInit();
    isCommand = 0;
    return;
}

unsigned char eventButton(void) {
    static unsigned char oldEvent = EV_NOEVENT;
    unsigned char event = EV_NOEVENT;
    if (!BitTst(PORTC, 0)) // SW0
        event = EV_LEFT;
    if (!BitTst(PORTC, 1)) // SW1
        event = EV_BASE;
    if (!BitTst(PORTC, 2)) // SW2
        event = EV_RIGHT;
    if (!BitTst(PORTC, 4)) // SW3
        event = EV_DOWN;
    if (!BitTst(PORTC, 5)) // SW4
        event = EV_UP;
    if (event != oldEvent) {
        oldEvent = event;
        return event;
    }
    return EV_NOEVENT;
}

unsigned char eventSerial(unsigned char character) {
    unsigned char event = EV_NOEVENT;
    if (character == 'W' || character == 'w')
        event = EV_UP;
    if (character == 'A' || character == 'a')
        event = EV_LEFT;
    if (character == 'S' || character == 's')
        event = EV_DOWN;
    if (character == 'D' || character == 'd')
        event = EV_RIGHT;
    if (character == 'R' || character == 'r')
        event = EV_BASE;
    return event;
}

unsigned char eventRead(void) {
    unsigned char event = EV_NOEVENT;
    unsigned char character = serialRead();
    Delay2ms();
    setValueADC(adcRead());
    Delay2ms();
    if (character == '/') {
        isCommand = 1;
    }
    if (!isCommand)
        event = (eventSerial(character) != EV_NOEVENT) ? eventSerial(character) : eventButton();
    else {
        if (character == '\r' || character == '\n') {
            isCommand = 0;
            executeProtocol();
            resetSerialBuffer();
        }
        else
            if (character != 0)
                addSerialBuffer(character);
    }
    Delay10ms();
    if (getValueADC() > getAlarmLevelHigh() || getValueADC() < getAlarmLevelLow())
        event = EV_ALARM;
    return event;
}
