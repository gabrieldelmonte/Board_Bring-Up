#ifndef DEFINES_H
#define DEFINES_H

    #define PIC18F4550

    #define FREQ 20000000

    #define SPEED 25

    #define NUMBER_LANGUAGES 6

    #define MAX_CHARACTERS 16

    #define MAX_STRING_LENGTH 15

    #define MIN_ADC_VALUE 0000
    #define MAX_ADC_VALUE 1000

	#define BitSet(arg,bit) ((arg) |= (1<<bit))
	#define BitClr(arg,bit) ((arg) &= ~(1<<bit)) 
	#define BitFlp(arg,bit) ((arg) ^= (1<<bit)) 
	#define BitTst(arg,bit) ((arg) & (1<<bit))

#endif /* DEFINES_H */
