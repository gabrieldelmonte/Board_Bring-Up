#include "headers/stateMachine.h"
#include "headers/delay.h"
#include "headers/event.h"
#include "headers/LED.h"
#include "headers/output.h"
#include "headers/variables.h"

typedef void (*Function)(const unsigned char event);

typedef struct {
    unsigned char baseState;
    unsigned char previousState;
    unsigned char nextState;
    Function function;
} State;

State stateMachine[] = {
    {STATE_MENU, STATE_SECOND,    STATE_ALARMLOW,  menuFunction     }, // MENU
    {STATE_MENU, STATE_MENU,      STATE_ALARMHIGH, alarmFunction    }, // ALARMLOW
    {STATE_MENU, STATE_ALARMLOW,  STATE_LANGUAGE,  alarmFunction    }, // ALARMHIGH
    {STATE_MENU, STATE_ALARMHIGH, STATE_HOUR,      languageFunction }, // LANGUAGE
    {STATE_MENU, STATE_LANGUAGE,  STATE_MINUTE,    timeFunction     }, // HOUR
    {STATE_MENU, STATE_HOUR,      STATE_SECOND,    timeFunction     }, // MINUTE
    {STATE_MENU, STATE_MINUTE,    STATE_MENU,      timeFunction     }, // SECOND
    {STATE_MENU, STATE_WARNING,   STATE_WARNING,   warningFunction  }, // WARNING
};

void stateMachineInit() {
    ledInit();
    
    eventInit();
    outputInit();
    variablesInit();
    
    setState(STATE_MENU);
    return;
}

void stateMachineLoop() {
    unsigned char event = eventRead();
    char index;
    allLedOFF();
    if ((getState() >= STATE_MENU) && (getState() < STATE_END)) {
        if (event == EV_ALARM) {
            if (getState() != STATE_WARNING)
                setPreviousState(getState());
            setState(STATE_WARNING);
        }
        State *currentState = &stateMachine[getState()];
        currentState->function(event);
        if (event == EV_BASE)
            setState(currentState->baseState);
        if (event == EV_LEFT)
            setState(currentState->previousState);
        if (event == EV_RIGHT)
            setState(currentState->nextState);
    }
    outputPrint(getState(), getLanguage());
    Delay100ms();
    for (index = 0; index < 3; index++)
        Delay10ms();
    return;
}

void menuFunction(const unsigned char event) {
    return;
}

void alarmFunction(const unsigned char event) {
    switch (getState()) {
        case STATE_ALARMLOW:
            if (event == EV_UP)
                setAlarmLevelLow(getAlarmLevelLow() + 1);
            if (event == EV_DOWN)
                setAlarmLevelLow(getAlarmLevelLow() - 1);
            break;
        case STATE_ALARMHIGH:
            if (event == EV_UP)
                setAlarmLevelHigh(getAlarmLevelHigh() + 1);
            if (event == EV_DOWN)
                setAlarmLevelHigh(getAlarmLevelHigh() - 1);
            break;
    }
    return;
}

void languageFunction(const unsigned char event) {
    if (event == EV_UP)
        setLanguage(getLanguage() + 1);
    if (event == EV_DOWN) {
        setLanguage(getLanguage() - 1);
    }
    return;
}

void timeFunction(const unsigned char event) {
    switch (getState()) {
        case STATE_HOUR:
            if (event == EV_UP)
                setRTCHours(getRTCHours() + 1);
            if (event == EV_DOWN)
                setRTCHours(getRTCHours() - 1);
            break;
        case STATE_MINUTE:
            if (event == EV_UP)
                setRTCMinutes(getRTCMinutes() + 1);
            if (event == EV_DOWN)
                setRTCMinutes(getRTCMinutes() - 1);
            break;
        case STATE_SECOND:
            if (event == EV_UP)
                setRTCSeconds(getRTCSeconds() + 1);
            if (event == EV_DOWN)
                setRTCSeconds(getRTCSeconds() - 1);
            break;
    }
    return;
}

void warningFunction(const unsigned char event) {
    if (event != EV_ALARM)
        setState(getPreviousState());
    allLedON();
    return;
}
