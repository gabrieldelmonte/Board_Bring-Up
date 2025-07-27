#ifndef EVENT_H
#define EVENT_H

    enum {
        EV_UP,
        EV_DOWN,
        EV_LEFT,
        EV_RIGHT,
        EV_BASE,
        EV_ALARM,
        EV_NOEVENT
    };

    void eventInit(void);

    unsigned char eventButton(void);

    unsigned char eventSerial(unsigned char character);

    unsigned char eventRead(void);

#endif /* EVENT_H */
