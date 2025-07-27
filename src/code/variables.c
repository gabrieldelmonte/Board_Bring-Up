#include <xc.h>
#include <pic18f4550.h>
#include "headers/defines.h"
#include "headers/RTC_DS1307.h"
#include "headers/serial.h"
#include "headers/variables.h"

#define ALARM_LOW 0x22
#define ALARM_HIGH 0x24
#define LANGUAGE 0x26
#define PREVIOUS_STATE 0x28
#define STARTED 0x40

static char state;
static int alarmLevelHigh;
static int alarmLevelLow;
static uint16_t valueADC;

static char serialBuffer[16];
static char bufferPosition;

static const char alarmProtocol[4] = "/ALM";
static const char *languageProtocol[6] = {"/LPT", "/LEN", "/LEP", "/LFR", "/LDE", "/LIT"};

void variablesInit(void) {
    setState(0);
    setRTCHours(0);
    setRTCMinutes(0);
    setRTCSeconds(0);
    bufferPosition = 0;
    resetSerialBuffer();
    if (isStarted()) {
        setAlarmLevelLow(getAlarmLevelLow());
        setAlarmLevelHigh(getAlarmLevelHigh());
    }
    else {
        setAlarmLevelLow(0);
        setAlarmLevelHigh(1000);
        setStarted();
        setLanguage(0);
    }
    return;
}

char getState(void) {
    return state;
}

void setState(char newState) {
    state = newState;
    return;
}

unsigned char getPreviousState(void) {
    return (unsigned char)RTC_DS1307_ReadData(PREVIOUS_STATE);
}

void setPreviousState(unsigned char state) {
    RTC_DS1307_WriteData(state, PREVIOUS_STATE);
    return;
}

int getAlarmLevelHigh(void) {
    return ((RTC_DS1307_ReadData(ALARM_HIGH + 1) << 8) + RTC_DS1307_ReadData(ALARM_HIGH));
}

void setAlarmLevelHigh(int newAlarmLevelHigh) {
    alarmLevelHigh = limitValue(newAlarmLevelHigh, MIN_ADC_VALUE, MAX_ADC_VALUE);
    if (alarmLevelHigh > getAlarmLevelLow()) {
        RTC_DS1307_WriteData(alarmLevelHigh & 0xFF, ALARM_HIGH);
        RTC_DS1307_WriteData((alarmLevelHigh >> 8) & 0xFF, ALARM_HIGH + 1);
    }
    return;
}

int getAlarmLevelLow(void) {
    return ((RTC_DS1307_ReadData(ALARM_LOW + 1) << 8) + RTC_DS1307_ReadData(ALARM_LOW));
}

void setAlarmLevelLow(int newAlarmLevelLow) {
    alarmLevelLow = limitValue(newAlarmLevelLow, MIN_ADC_VALUE, MAX_ADC_VALUE);
    if (alarmLevelLow < getAlarmLevelHigh()) {
        RTC_DS1307_WriteData(alarmLevelLow & 0xFF, ALARM_LOW);
        RTC_DS1307_WriteData((alarmLevelLow >> 8) & 0xFF, ALARM_LOW + 1);
    }
    return;
}

char getLanguage(void) {
    return (RTC_DS1307_ReadData(LANGUAGE) % NUMBER_LANGUAGES);
}

void setLanguage(char newLanguage) {
    if (getLanguage() == 0 && newLanguage == 0xFF) {
        newLanguage = NUMBER_LANGUAGES - 1;
    }
    RTC_DS1307_WriteData(newLanguage % NUMBER_LANGUAGES, LANGUAGE);
    return;
}

uint16_t getValueADC(void) {
    return valueADC;
}

void setValueADC(uint16_t newValueADC) {
    valueADC = (uint16_t)(((float)newValueADC / 1023.0) * 1000);
    return;
}

int getRTCHours(void) {
    return getHours();
}

void setRTCHours(int newHours) {
    if (!((getRTCHours() == 0 && newHours < getRTCHours()) || (getRTCHours() == 11 && getRTCHours() < newHours)))
        setHours(newHours);
    return;
}

int getRTCMinutes(void) {
    return getMinutes();
}

void setRTCMinutes(int newMinutes) {
    if (!((getRTCMinutes() == 0 && newMinutes < getRTCMinutes()) || (getRTCMinutes() == 59 && getRTCMinutes() < newMinutes)))
        setMinutes(newMinutes);
    return;
}

int getRTCSeconds(void) {
    return getSeconds();
}

void setRTCSeconds(int newSeconds) {
    if (!((getRTCSeconds() == 0 && newSeconds < getRTCSeconds()) || (getRTCSeconds() == 59 && getRTCSeconds() < newSeconds)))
        setSeconds(newSeconds);
    return;
}

char isStarted(void) {
    return (RTC_DS1307_ReadData(STARTED) == 0x01);
}

void setStarted(void) {
    RTC_DS1307_WriteData(0x01, STARTED);
    return;
}

int limitValue(int value, int limitInf, int limitSup) {
    return (value > limitSup) ? limitSup : (value < limitInf) ? limitInf : value;
}

unsigned char strcmp_local(const char *first, const char *second, unsigned char findex, unsigned char sindex) {
    unsigned char index;
    unsigned char value = 1;
    for (index = findex; index <= sindex; index++) {
        if (first[index] != second[index]) {
            value = 0;
            break;
        }
    }
    return value;
}

void resetSerialBuffer(void) {
    char index;
    for (index = 0; index < 15; index++)
        serialBuffer[index] = 48;
    serialBuffer[15] = '\0';
    bufferPosition = 0;
    return;
}

void addSerialBuffer(char value) {
    if (bufferPosition < 15)
        if (value != '\r' && value != '\n' && value != '\0')
            serialBuffer[bufferPosition++] = value;
    else
        bufferPosition = 0;
    serialClear();
    serialSendMessage("Buffer: ");
    serialSendMessage(serialBuffer);
    serialClear();
    serialSendChar('\r');
    serialSendChar('\n');
    return;
}

void executeProtocol(void) {
    unsigned char index;
    int value;
    // LANGUAGE: /LXXX
    if (serialBuffer[1] == 'L') {
        for (index = 0; index < 6; index++)
            if (strcmp_local(serialBuffer, languageProtocol[index], 2, 3)) {
                setLanguage(index);
                break;
            }
        return;
    }
    // ALARM: /ALMX[XXXX]
    if (strcmp_local(serialBuffer, alarmProtocol, 0, 3)) {
        value = ((serialBuffer[6] - 48) * 1000 + (serialBuffer[7] - 48) * 100 + (serialBuffer[8] - 48) * 10 + (serialBuffer[9] - 48) * 1);
        if (serialBuffer[4] == 'L' && serialBuffer[5] == '[' && serialBuffer[10] == ']')
            setAlarmLevelLow(value);
        if (serialBuffer[4] == 'H' && serialBuffer[5] == '[' && serialBuffer[10] == ']')
            setAlarmLevelHigh(value);
        return;
    }
    // HOUR: /H:XXM:XXS:XX
    if (serialBuffer[1] == 'H' && serialBuffer[2] == ':' && serialBuffer[5] == 'M' && serialBuffer[6] == ':' && serialBuffer[9] == 'S' && serialBuffer[10] == ':') {
        value = ((serialBuffer[3] - 48) * 10 + serialBuffer[4] - 48);
        setRTCHours(value);
        value = ((serialBuffer[7] - 48) * 10 + serialBuffer[8] - 48);;
        setRTCMinutes(value);
        value = ((serialBuffer[11] - 48) * 10 + serialBuffer[12] - 48);;
        setRTCSeconds(value);
        return;
    }
    return;
}
