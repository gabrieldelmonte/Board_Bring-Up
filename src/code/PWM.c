#include <xc.h>
#include <pic18f4550.h>
#include "headers/defines.h"
#include "headers/PWM.h"

void pwmInit(void) {
	BitClr(TRISC, 1);      // Set RC1 as output
	BitClr(TRISC, 2);      // Set RC2 as output
	T2CON |= 0b00000011;   // Set the prescaler of TIMER2 as 1:16
	BitSet(T2CON, 2);
	CCP1CON |= 0b00001100; // Set CCP1 as PWM
	CCP2CON |= 0b00001100; // Set CCP2 as PWM
    return;
}

void pwmSet1(unsigned char percentage) {
	unsigned int value = ((unsigned int)percentage) *(PR2+1);
	value = value / 25;
	value &= 0x03ff;
	CCPR1L = (unsigned char)value >> 2;
	CCP1CON |= (value & 0x0003) << 4;
    return;
}

void pwmSet2(unsigned char percentage) {
	unsigned int value = ((unsigned int)percentage) *(PR2+1);
	value = value / 25;
	value &= 0x03ff;
	CCPR2L = (unsigned char)value >> 2;
	CCP2CON |= (value & 0x0003) << 4;
    return;
}

void pwmFrequency(unsigned int frequency) {
	PR2 = (unsigned char)(125000 / (frequency)) - 1;
    return;
}
