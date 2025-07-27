#include "code/headers/stateMachine.h"

void main(void) {
    stateMachineInit();
    while (1) 
        stateMachineLoop();
    return;
}
