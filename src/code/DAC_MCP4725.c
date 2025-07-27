#include <xc.h>
#include <pic18f4550.h>
#include "headers/config.h"
#include "headers/defines.h"
#include "headers/DAC_MCP4725.h"

void DAC_MCP4725_I2C_Master_Init(uint32_t clock) {
    BitSet(TRISB, 0);
    BitSet(TRISB, 1);
    SSPSTATbits.SMP = 1;
    SSPCON1bits.SSPEN = 1;
    SSPCON1bits.SSPM = 0b1000;
    SSPADD = (uint8_t)((FREQ/(4.0 * clock)) - 1);
    SSPCON2 = 0x00;
    return;
}

void DAC_MCP4725_I2C_Master_Wait(void) {
    while ((SSPCON2 & 0b00011111) || (SSPSTAT & 0b00000100));
    return;
}

void DAC_MCP4725_I2C_Start(void) {
    DAC_MCP4725_I2C_Master_Wait();
    SSPCON2bits.SEN = 1;
    return;
}

void DAC_MCP4725_I2C_Stop(void) {
    DAC_MCP4725_I2C_Master_Wait();
    SSPCON2bits.PEN = 1;
    return;
}

void DAC_MCP4725_I2C_Repeated_Start(void) {
    DAC_MCP4725_I2C_Master_Wait();
    SSPCON2bits.RSEN = 1;
    return;
}

void DAC_MCP4725_I2C_Master_Write(uint8_t data) {
    DAC_MCP4725_I2C_Master_Wait();
    SSPBUF = data;
    return;
}

uint8_t DAC_MCP4725_I2C_Master_Read(uint8_t ACK) {
    uint8_t data;
    DAC_MCP4725_I2C_Master_Wait();
    SSPCON2bits.RCEN = 1;
    DAC_MCP4725_I2C_Master_Wait();
    data = SSPBUF;
    DAC_MCP4725_I2C_Master_Wait();
    SSPCON2bits.ACKDT = (ACK) ? 0 : 1;
    SSPCON2bits.ACKEN = 1;
    return data;
}

void DAC_MCP4725_SetVoltage(uint16_t voltage) {
    DAC_MCP4725_I2C_Start();
    DAC_MCP4725_I2C_Master_Wait();
    DAC_MCP4725_I2C_Master_Write(0b11000000);
    DAC_MCP4725_I2C_Master_Wait();
    DAC_MCP4725_I2C_Master_Write(0b01000000); 
    DAC_MCP4725_I2C_Master_Wait();
    DAC_MCP4725_I2C_Master_Write((uint8_t)(voltage >> 4));
    DAC_MCP4725_I2C_Master_Wait();
    DAC_MCP4725_I2C_Master_Write((uint8_t)((voltage & 0b1111) << 4));
    DAC_MCP4725_I2C_Master_Wait();
    DAC_MCP4725_I2C_Stop();
    DAC_MCP4725_I2C_Master_Wait();
    return;
}

uint16_t DAC_MCP4725_Read(void) {
    uint8_t byte2;    
    uint8_t byte3;    
    uint8_t byte4;    
    uint8_t byte5;    
    uint8_t byte6;
    uint16_t data;
    DAC_MCP4725_I2C_Start();
    DAC_MCP4725_I2C_Master_Wait();
    DAC_MCP4725_I2C_Master_Write(0b11000001);
    DAC_MCP4725_I2C_Master_Wait();
    byte2 = DAC_MCP4725_I2C_Master_Read(4);
    byte3 = DAC_MCP4725_I2C_Master_Read(3);
    byte4 = DAC_MCP4725_I2C_Master_Read(2);
    byte5 = DAC_MCP4725_I2C_Master_Read(1);
    byte6 = DAC_MCP4725_I2C_Master_Read(0);
    data = (((uint16_t)byte5 << 8) | byte6);
    DAC_MCP4725_I2C_Stop();
    DAC_MCP4725_I2C_Master_Wait();
    return data;
}
