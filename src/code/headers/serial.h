#ifndef SERIAL_H
#define SERIAL_H

    void serialInit(void);

    void serialClear(void);

    void serialSendChar(unsigned char character);
    
    void serialSendMessage(char *message);

    void serialSendInt(int value, int numberDigits);

	unsigned char serialRead(void);

#endif /* SERIAL_H */
