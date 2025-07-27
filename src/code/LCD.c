#include <xc.h>
#include <pic18f4550.h>
#include "headers/defines.h"
#include "headers/LCD.h"
#include "headers/delay.h"

#define RS 2
#define EN 3

void lcdInit(void) {
    ADCON1 = 0b00001110;
	BitClr(TRISA, RS);
	BitClr(TRISA, EN);
	TRISD = 0x00;
    Delay10ms();
    lcdCommand(0x38);
    Delay2ms();
    Delay2ms();
    lcdCommand(0x38);
    Delay2ms();
    lcdCommand(0x38);
    lcdCommand(0x38);
    lcdCommand(0x06);
    lcdCommand(0x0F);
    lcdCommand(0x01);
    return;
}

void lcdCommand(unsigned char command) {
	BitClr(PORTA, RS);
    PORTD = (unsigned char)(
            ((command & 0b00000001) << 7) |
            ((command & 0b00000010) << 5) |
            ((command & 0b00000100) << 3) |
            ((command & 0b00001000) << 1) |
            ((command & 0b00010000) >> 1) |
            ((command & 0b00100000) >> 3) |
            ((command & 0b01000000) >> 5) |
            ((command & 0b10000000) >> 7));
    BitSet(PORTA, EN);
	BitClr(PORTA, EN);
    if((command == 0x02) || (command == 0x01))
       Delay2ms();   
    else
	   Delay40us();
    return;
}

void lcdData(unsigned char value) {
	BitSet(PORTA, RS);
    PORTD = (unsigned char)(
            ((value & 0b00000001) << 7) |
            ((value & 0b00000010) << 5) |
            ((value & 0b00000100) << 3) |
            ((value & 0b00001000) << 1) |
            ((value & 0b00010000) >> 1) |
            ((value & 0b00100000) >> 3) |
            ((value & 0b01000000) >> 5) |
            ((value & 0b10000000) >> 7));
    BitSet(PORTA, EN);
	BitClr(PORTA, EN);
	BitClr(PORTA, RS);
	Delay40us();
    return;
}

void lcdString(char *message) {
	int index = 0;
	while (message[index] != 0) {
		lcdData(message[index]);
		index++;
	}
    return;
}

void lcdInt(int value) {
    if (value < 0) {
        value = value * (-1);
        lcdData('-');
    }
    lcdData((value / 1000) % 10 + 48);
    lcdData((value / 100) % 10 + 48);
    lcdData((value / 10) % 10 + 48);
    lcdData((value / 1) % 10 + 48);
    return;
}
