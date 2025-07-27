#ifndef DAC_MCP4725_H
#define DAC_MCP4725_H

    void DAC_MCP4725_I2C_Master_Init(uint32_t clock);

    void DAC_MCP4725_I2C_Master_Wait(void);

    void DAC_MCP4725_I2C_Start(void);

    void DAC_MCP4725_I2C_Stop(void);

    void DAC_MCP4725_I2C_Repeated_Start(void);

    void DAC_MCP4725_I2C_Master_Write(uint8_t data);

    uint8_t DAC_MCP4725_I2C_Master_Read(uint8_t ACK);

    void DAC_MCP4725_SetVoltage(uint16_t voltage);

    uint16_t DAC_MCP4725_Read(void);

#endif /* DAC_MCP4725_H */
