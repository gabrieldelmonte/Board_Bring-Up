#include <xc.h>
#include <pic18f4550.h>
#include "headers/defines.h"
#include "headers/serial.h"

void serialInit(void) {
    TXSTA = 0b00101100; // Configure the transmission of data by serial
    RCSTA = 0b10010000; // Configure the receive of data by serial
    BAUDCON = 0b00001000;
    SPBRGH = 0b00000000;
    SPBRG = 0b00100010;
    BitSet(TRISC, 6);
    BitSet(TRISC, 7);
    return;
}   

void serialClear() {
    serialSendMessage("                    ");
    serialSendChar('\r');    
    serialSendChar('\r');
    serialSendChar('\r');
    return;
}

void serialSendChar(unsigned char character) {
    while (!BitTst(PIR1, 4)); // Wait until busy
    TXREG = character; 
    return;
}

void serialSendMessage(char *message) {
    int index = 0; 
    while (message[index] != '\0') {
        while (!BitTst(PIR1, 4)); // Wait until busy
        TXREG = message[index];
        index++;
    }
    return;
}

void serialSendInt(int value, int numberDigits) {
    int index = 1;
    int auxiliar;
    for (auxiliar = 1; auxiliar < numberDigits; auxiliar++)
        index *= 10;
    if (value < 0) {
        value *= (-1);
        serialSendChar('-');
    }
    while(index > 0) {
        serialSendChar((value / index) % 10 + 48);
        index /= 10;
    }
    return;
}

unsigned char serialRead(void) {
    char valueRead = 0;
    if (BitTst(RCSTA, 1)) {
        BitClr(RCSTA, 4);
        BitSet(RCSTA, 4);
    }
    if (BitTst(PIR1, 5)) {
        valueRead = RCREG;
    }
    return valueRead;
}
