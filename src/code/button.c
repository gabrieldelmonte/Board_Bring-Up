#include <xc.h>
#include <pic18f4550.h>
#include "headers/defines.h"
#include "headers/button.h"

void buttonInit(void) {
    BitClr(UCON, 3);
    BitSet(UCFG, 3);
    TRISC = 0xFF;
    return;
}
