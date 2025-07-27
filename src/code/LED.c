#include <xc.h>
#include <pic18f4550.h>
#include "headers/defines.h"
#include "headers/LED.h"

void ledInit(void) {
    TRISB = 0x00;
    PORTB = 0xFF;
    return;
}

void ledON(char led) {
    BitClr(PORTB, led);
    return;
}

void allLedON(void) {
    PORTB = 0x00;
    return;
}

void ledOFF(char led) {
    BitSet(PORTB, led);
    return;
}

void allLedOFF(void) {
    PORTB = 0xFF;
    return;
}
