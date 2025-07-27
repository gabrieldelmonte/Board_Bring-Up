#ifndef PWM_H
#define PWM_H

    void pwmInit(void);

	void pwmSet1(unsigned char percentage);
    
	void pwmSet2(unsigned char percentage);
	
    void pwmFrequency(unsigned int frequency);

#endif /* PWM_H */
