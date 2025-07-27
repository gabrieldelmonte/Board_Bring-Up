#ifndef CONFIG_H
#define CONFIG_H

    #include "defines.h"

    #define PIC18F4550

    #ifdef PIC18F4550
        #pragma config MCLRE = ON
        #pragma config FOSC = HS
        #pragma config WDT = OFF
        #pragma config LVP = OFF
    #endif

#endif /* CONFIG_H */
