#include "headers/delay.h"

void Delay40us(void) {
	unsigned char index;
	for (index = 0; index < 25; index++)
        __asm("NOP");
    return;
}

void Delay2ms(void) {
	unsigned char index;
	for(index = 0; index < 50; index++)
		Delay40us();
    return;
}

void Delay10ms(void) {
	unsigned char index;
	for(index = 0; index < 5; index++)
		Delay2ms();
    return;
}

void Delay100ms(void) {
	unsigned char index;
	for(index = 0; index < 10; index++)
		Delay10ms();
    return;
}
