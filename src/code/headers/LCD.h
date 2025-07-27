#ifndef LCD_H
#define LCD_H
    
    void lcdInit(void);
    
	void lcdCommand(unsigned char cmd);
	
    void lcdData(unsigned char value);
    
    void lcdString(char *message);

    void lcdInt(int value);

#endif /* LCD_H */
