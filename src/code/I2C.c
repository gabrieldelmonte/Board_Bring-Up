#include <xc.h>
#include <pic18f4550.h>
#include "headers/defines.h"
#include "headers/I2C.h"

#define SDA()     BitTst(PORTB, 0)
#define SDA_OFF() BitClr(PORTB, 0)
#define SDA_IN()  BitSet(TRISB, 0)
#define SDA_OUT() BitClr(TRISB, 0)

#define SCL()     BitTst(PORTB, 1)
#define SCL_OFF() BitClr(PORTB, 1)
#define SCL_IN()  BitSet(TRISB, 1)
#define SCL_OUT() BitClr(TRISB, 1)

unsigned char started = 0;

void I2C_delay(void) {
    int index = 0;
    for (index = 0; index < SPEED / 2; index++)
        __asm("NOP");
    return;
}

unsigned char read_SCL(void) {
    SCL_IN();
    return !!SCL();
}

void clear_SCL(void) {
    SCL_OUT();
    SCL_OFF();
    return;
}

unsigned char read_SDA(void) {
    SDA_IN();
    return !!SDA();
}

void clear_SDA(void) {
    SDA_OUT();
    SDA_OFF();
    return;
}

void I2C_Init(void) {
    SDA_IN();
    SCL_IN();
    return;
}

void I2C_Start(void) {
    if (started) { 
		read_SDA();
		I2C_delay();
		while (!read_SCL());
		I2C_delay();
	}
	if (!read_SDA()) {
        // Error
	}
	clear_SDA();
	I2C_delay();
	clear_SCL();
	started = 1;
    return;
}

void I2C_Stop(void) {
	clear_SDA();
	I2C_delay();
	while (!read_SCL());
	I2C_delay();
	if (!read_SDA()) {
        // Error
	}
	I2C_delay();
	started = 0;
    return;
}

void I2C_WriteBit(unsigned char bit) {
    if (bit)
		read_SDA();
    else
		clear_SDA();
	I2C_delay();
	while (!read_SCL());
	if (bit && !read_SDA()) {
        // Error
	}
	I2C_delay();
	clear_SCL();
	I2C_delay();
    return;
}

unsigned char I2C_WriteByte(unsigned char start, unsigned char stop, unsigned char byte) {
    unsigned char bit;
	unsigned char nack;
	if (start)
		I2C_Start();
	for (bit = 0; bit < 8; bit++) {
		I2C_WriteBit((byte & 0x80) != 0);
		byte <<= 1;
	}
	nack = I2C_ReadBit();
	if (stop)
		I2C_Stop();
	return nack;
}

unsigned char I2C_ReadBit(void) {
    unsigned char bit;
	read_SDA();
	I2C_delay();
	while (!read_SCL());
	bit = read_SDA();
	I2C_delay();
	clear_SCL();
	I2C_delay();
	return bit;
}

unsigned char I2C_ReadByte(unsigned char nack, unsigned char stop) {
    unsigned char byte = 0;
	unsigned char bit;
	for (bit = 0; bit < 8; bit++)
		byte = (unsigned char)(byte << 1) | I2C_ReadBit();
	I2C_WriteBit(nack);
	if (stop)
		I2C_Stop();
	return byte;
}
