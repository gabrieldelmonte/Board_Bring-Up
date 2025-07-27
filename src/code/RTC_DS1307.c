#include <xc.h>
#include <pic18f4550.h>
#include "headers/config.h"
#include "headers/defines.h"
#include "headers/RTC_DS1307.h"
#include "headers/I2C.h"

#define DS1307_CTRL_ID 0b11011110

#define I2C_WRITE 0
#define I2C_READ  1

int dec2bcd(int value) {
	return ((value / 10 * 16) + (value % 10));
}

int bcd2dec(int value) {
	return ((value / 16 * 10) + (value % 16));
}

void RTC_DS1307_Init(void) {
	I2C_Init();
    return;
}

void RTC_DS1307_StartClock(void) {
	int seconds;
	seconds = RTC_DS1307_ReadData(SEC);
	RTC_DS1307_WriteData(0x7f & seconds, SEC);
	return;
}

void RTC_DS1307_WriteData(unsigned char value, int address) {
    I2C_WriteByte(1, 0, (unsigned char)(DS1307_CTRL_ID | I2C_WRITE));
	I2C_WriteByte(0, 0, (unsigned char)address);
	I2C_WriteByte(0, 1, (unsigned char)value);
    return;
}

int RTC_DS1307_ReadData(int address) {
	int result;
	I2C_WriteByte(1, 0, (unsigned char)(DS1307_CTRL_ID | I2C_WRITE));
	I2C_WriteByte(0, 0, (unsigned char)address);
	I2C_WriteByte(1, 0, (unsigned char)(DS1307_CTRL_ID | I2C_READ));
	result = I2C_ReadByte(1, 1);
	return result;
}
