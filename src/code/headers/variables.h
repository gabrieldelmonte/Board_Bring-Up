#ifndef VARIABLES_H
#define VARIABLES_H

    #include <xc.h>

    void variablesInit(void);

    char getState(void);

    void setState(char newState);

    unsigned char getPreviousState(void);

    void setPreviousState(unsigned char state);

    int getAlarmLevelHigh(void);

    void setAlarmLevelHigh(int newAlarmLevelHigh);

    int getAlarmLevelLow(void);

    void setAlarmLevelLow(int newAlarmLevelLow);

    char getLanguage(void);

    void setLanguage(char newLanguage);
    
    uint16_t getValueADC(void);

    void setValueADC(uint16_t newValueADC);

    int getRTCHours(void);

    void setRTCHours(int newHours);

    int getRTCMinutes(void);

    void setRTCMinutes(int newMinutes);

    int getRTCSeconds(void);

    void setRTCSeconds(int newSeconds);

    char isStarted(void);

    void setStarted(void);

    int limitValue(int value, int limitInf, int limitSup);

    unsigned char strcmp_local(const char *first, const char *second, unsigned char findex, unsigned char sindex);

    void resetSerialBuffer(void);

    void addSerialBuffer(char value);

    void executeProtocol(void);

#endif /* VARIABLES_H */
