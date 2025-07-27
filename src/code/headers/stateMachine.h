#ifndef STATEMACHINE_H
#define STATEMACHINE_H

    enum {
        STATE_MENU,
        STATE_ALARMLOW,
        STATE_ALARMHIGH,
        STATE_LANGUAGE,
        STATE_HOUR,
        STATE_MINUTE,
        STATE_SECOND,
        STATE_WARNING,
        STATE_END
    };
    
    void stateMachineInit(void);

    void stateMachineLoop(void);

    void menuFunction(const unsigned char event);

    void alarmFunction(const unsigned char event);

    void languageFunction(const unsigned char event);

    void timeFunction(const unsigned char event);

    void warningFunction(const unsigned char event);

#endif /* STATEMACHINE_H */
