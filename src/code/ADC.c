#include <xc.h>
#include <pic18f4550.h>
#include "headers/defines.h"
#include "headers/ADC.h"

 void adcInit(void) {
	BitSet(TRISA, 0);    // Set the RA0 as input
	ADCON0 = 0b00000001; // Select the Channel 0
	ADCON1 = 0b00001110; // Just AN0 is analog and the reference is based on VSS/VDD
	ADCON2 = 0b10101010; // Time of conversion: 12 TAD, FOSC/32
    return;
}

 unsigned int adcRead(void) {
	unsigned int valueRead;
	ADCON0 |= 0b00000010;      // Initialize the conversion
    while (BitTst(ADCON0, 1)); // Wait to finish
	valueRead = ADRESH ;       // Read the register
	valueRead <<= 8;
	valueRead += ADRESL;       // Read the register
	return valueRead;
}
