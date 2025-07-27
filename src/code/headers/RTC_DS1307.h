#ifndef RTC_DS1307_H
#define RTC_DS1307_H

    #define SEC     0
    #define MIN     1
    #define HOUR    2
    #define WEEKDAY 3
    #define DAY     4
    #define MONTH   5
    #define YEAR    6

    #define getSeconds()  (bcd2dec(RTC_DS1307_ReadData(SEC)& 0x7f))
    #define getMinutes()  (bcd2dec(RTC_DS1307_ReadData(MIN)& 0x7f))
    #define getHours()    (bcd2dec(RTC_DS1307_ReadData(HOUR)& 0x5f))
    #define getWeekDay()  (bcd2dec(RTC_DS1307_ReadData(WEEKDAY)& 0x07))
    #define getDays()     (bcd2dec(RTC_DS1307_ReadData(DAY)& 0x5f))
    #define getMonths()   (bcd2dec(RTC_DS1307_ReadData(MONTH)& 0x3f))
    #define getYears()    (bcd2dec(RTC_DS1307_ReadData(YEAR)& 0xff))

    #define setSeconds(v) (RTC_DS1307_WriteData((unsigned char)dec2bcd(v)|0x80,SEC))
    #define setMinutes(v) (RTC_DS1307_WriteData((unsigned char)dec2bcd(v),MIN))
    #define setHours(v)   (RTC_DS1307_WriteData((unsigned char)dec2bcd(v),HOUR))
    #define setWeekDay(v) (RTC_DS1307_WriteData((unsigned char)dec2bcd(v),WEEKDAY))
    #define setDays(v)    (RTC_DS1307_WriteData((unsigned char)dec2bcd(v),DAY))
    #define setMonths(v)  (RTC_DS1307_WriteData((unsigned char)dec2bcd(v),MONTH))
    #define setYears(v)   (RTC_DS1307_WriteData((unsigned char)dec2bcd(v),YEAR))

    int dec2bcd(int value);

    int bcd2dec(int value);

    void RTC_DS1307_Init(void);

    void RTC_DS1307_StartClock(void);

    void RTC_DS1307_WriteData(unsigned char value, int address);

    int RTC_DS1307_ReadData(int address);

#endif /* RTC_DS1307_H */
