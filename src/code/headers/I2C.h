#ifndef I2C_H
#define I2C_H

    void I2C_delay(void);
    
    unsigned char read_SCL(void);
    
    void clear_SCL(void);
    
    unsigned char read_SDA(void);
    
    void clear_SDA(void);

    void I2C_Init(void);

    void I2C_Start(void);

    void I2C_Stop(void);

    void I2C_WriteBit(unsigned char bit);
    
    unsigned char I2C_WriteByte(unsigned char start, unsigned char stop, unsigned char byte);
    
    unsigned char I2C_ReadBit(void);
    
    unsigned char I2C_ReadByte(unsigned char nack, unsigned char stop);

#endif /* I2C_H */
