#include "headers/output.h"
#include "headers/defines.h"
#include "headers/LCD.h"
#include "headers/serial.h"
#include "headers/stateMachine.h"
#include "headers/variables.h"

typedef struct {
    char message[NUMBER_LANGUAGES][MAX_CHARACTERS + 1];
} LCD_Screen;

/*
State stateMachine[] = {
    {STATE_MENU, STATE_LANGUAGE,  STATE_ALARMLOW,  menuFunction     }, // MENU
    {STATE_MENU, STATE_MENU,      STATE_ALARMHIGH, alarmFunction    }, // ALARMLOW
    {STATE_MENU, STATE_ALARMLOW,  STATE_LANGUAGE,  alarmFunction    }, // ALARMHIGH
    {STATE_MENU, STATE_ALARMHIGH, STATE_HOUR,      languageFunction }, // LANGUAGE
    {STATE_MENU, STATE_LANGUAGE,  STATE_MINUTE,    timeFunction     }, // HOUR
    {STATE_MENU, STATE_HOUR,      STATE_SECOND,    timeFunction     }, // MINUTE
    {STATE_MENU, STATE_MINUTE,    STATE_MENU,      timeFunction     }, // SECOND
    {STATE_MENU, STATE_WARNING,   STATE_WARNING,   warningFunction  }, // WARNING
};
*/

LCD_Screen const screens[STATE_END] = {
    {"Bem-vindo!      ", "Welcome!        ", "Bienvenido!     ", "Bienvenue!      ", "Willkommen!     ", "Benvenuto!      "}, // STATE_MENU
    {"Alarme (inf)    ", "Alarm (low)     ", "Alarma (baja)   ", "Alarme (bas)    ", "Alarm (niedrig) ", "Allarme (basso) "}, // STATE_ALARMLOW
    {"Alarme (sup)    ", "Alarm (high)    ", "Alarma (alta)   ", "Alarme (haut)   ", "Alarm (hoch)    ", "Allarme (alto)  "}, // STATE_ALARMHIGH
    {"Alterar idioma  ", "Change language ", "Cambiar idioma  ", "Changer langue  ", "Sprache andern  ", "Cambia lingua   "}, // STATE_LANGUAGE
    {"Hora            ", "Hour            ", "Hora            ", "Heure           ", "Stunde          ", "Ora             "}, // STATE_HOUR
    {"Minutos         ", "Minutes         ", "Minutos         ", "Minutes         ", "Minuten         ", "Minuti          "}, // STATE_MINUTE
    {"Segundos        ", "Seconds         ", "Segundos        ", "Secondes        ", "Sekunden        ", "Secondi         "}, // STATE_SECOND           
    {"CUIDADO!        ", "WARNING!        ", "ADVERTENCIA!    ", "ATTENTION!      ", "WARNUNG!        ", "ATTENZIONE!     "}, // STATE_WARNING
};

static const char languages[NUMBER_LANGUAGES][16] = {
    "Portugues",
    "English",
    "Espanol",
    "Francais",
    "Deutsch",
    "Italiano",
};

void showDisplay(LCD_Screen *screen, int numberScreen, char language) {
    lcdCommand(0x01);
    lcdCommand(0x80);
    lcdString(screen->message[language]);
    lcdCommand(0xC0);
    switch (numberScreen) {
        case STATE_MENU:
            lcdData(((getRTCHours() / 10) % 10) + 48);
            lcdData((getRTCHours() % 10) + 48);
            lcdData(':');
            lcdData(((getRTCMinutes() / 10) % 10) + 48);
            lcdData((getRTCMinutes() % 10) + 48);
            lcdData(':');
            lcdData(((getRTCSeconds() / 10) % 10) + 48);
            lcdData((getRTCSeconds() % 10) + 48);
            lcdString("        ");
            break;
        case STATE_ALARMLOW:
            lcdData('[');
            lcdInt(getAlarmLevelLow());
            lcdData(']');
            lcdData(' ');
            lcdInt((int)getValueADC());
            lcdData(' ');
            lcdInt(getAlarmLevelHigh());
            lcdString("                ");
            break;
        case STATE_ALARMHIGH:
            lcdInt(getAlarmLevelLow());
            lcdData(' ');
            lcdInt((int)getValueADC());
            lcdData(' ');
            lcdData('[');
            lcdInt(getAlarmLevelHigh());
            lcdData(']');
            lcdString("                ");
            break;
        case STATE_LANGUAGE:
            lcdData('[');
            lcdString(languages[getLanguage()]);
            lcdData(']');
            break;
        case STATE_HOUR:
            lcdData('[');
            lcdData(((getRTCHours() / 10) % 10) + 48);
            lcdData((getRTCHours() % 10) + 48);
            lcdData(']');
            lcdData(':');
            lcdData(((getRTCMinutes() / 10) % 10) + 48);
            lcdData((getRTCMinutes() % 10) + 48);
            lcdData(':');
            lcdData(((getRTCSeconds() / 10) % 10) + 48);
            lcdData((getRTCSeconds() % 10) + 48);
            lcdString("        ");
            break;
        case STATE_MINUTE:            
            lcdData(((getRTCHours() / 10) % 10) + 48);
            lcdData((getRTCHours() % 10) + 48);
            lcdData(':');
            lcdData('[');
            lcdData(((getRTCMinutes() / 10) % 10) + 48);
            lcdData((getRTCMinutes() % 10) + 48);
            lcdData(']');
            lcdData(':');
            lcdData(((getRTCSeconds() / 10) % 10) + 48);
            lcdData((getRTCSeconds() % 10) + 48);
            lcdString("        ");
            break;
        case STATE_SECOND:
            lcdData(((getRTCHours() / 10) % 10) + 48);
            lcdData((getRTCHours() % 10) + 48);
            lcdData(':');
            lcdData(((getRTCMinutes() / 10) % 10) + 48);
            lcdData((getRTCMinutes() % 10) + 48);
            lcdData(':');
            lcdData('[');
            lcdData(((getRTCSeconds() / 10) % 10) + 48);
            lcdData((getRTCSeconds() % 10) + 48);
            lcdData(']');
            lcdString("        ");
            break;
        case STATE_WARNING:
            lcdString("!!!!!!!!!!!!!!!!");
            break;
    }
    return;
}

void showSerial(LCD_Screen *screen, int numberScreen, char language) {
    serialClear();
    serialSendMessage(screen->message[language]);
    switch (numberScreen) {
        case STATE_MENU:
            serialSendChar(((getRTCHours() / 10) % 10) + 48);
            serialSendChar((getRTCHours() % 10) + 48);
            serialSendChar(':');
            serialSendChar(((getRTCMinutes() / 10) % 10) + 48);
            serialSendChar((getRTCMinutes() % 10) + 48);
            serialSendChar(':');
            serialSendChar(((getRTCSeconds() / 10) % 10) + 48);
            serialSendChar((getRTCSeconds() % 10) + 48);
            serialClear();
            serialSendChar('\r');
            serialSendChar('\n');
            break;
        case STATE_ALARMLOW:
            serialSendChar('[');
            serialSendInt(getAlarmLevelLow(), 4);
            serialSendChar(']');
            serialSendChar(' ');
            serialSendInt((int)getValueADC(), 4);
            serialSendChar(' ');
            serialSendInt(getAlarmLevelHigh(), 4);
            serialClear();
            serialSendChar('\r');
            serialSendChar('\n');
            break;
        case STATE_ALARMHIGH:
            serialSendInt(getAlarmLevelLow(), 4);
            serialSendChar(' ');
            serialSendInt((int)getValueADC(), 4);
            serialSendChar(' ');
            serialSendChar('[');
            serialSendInt(getAlarmLevelHigh(), 4);
            serialSendChar(']');
            serialClear();
            serialSendChar('\r');
            serialSendChar('\n');
            break;
        case STATE_LANGUAGE:
            serialSendChar('[');
            serialSendMessage(languages[getLanguage()]);
            serialSendChar(']');
            serialClear();
            serialSendChar('\r');
            serialSendChar('\n');
            break;
        case STATE_HOUR:
            serialSendChar('[');
            serialSendChar(((getRTCHours() / 10) % 10) + 48);
            serialSendChar((getRTCHours() % 10) + 48);
            serialSendChar(']');
            serialSendChar(':');
            serialSendChar(((getRTCMinutes() / 10) % 10) + 48);
            serialSendChar((getRTCMinutes() % 10) + 48);
            serialSendChar(':');
            serialSendChar(((getRTCSeconds() / 10) % 10) + 48);
            serialSendChar((getRTCSeconds() % 10) + 48);
            serialClear();
            serialSendChar('\r');
            serialSendChar('\n');
            break;
        case STATE_MINUTE:            
            serialSendChar(((getRTCHours() / 10) % 10) + 48);
            serialSendChar((getRTCHours() % 10) + 48);
            serialSendChar(':');
            serialSendChar('[');
            serialSendChar(((getRTCMinutes() / 10) % 10) + 48);
            serialSendChar((getRTCMinutes() % 10) + 48);
            serialSendChar(']');
            serialSendChar(':');
            serialSendChar(((getRTCSeconds() / 10) % 10) + 48);
            serialSendChar((getRTCSeconds() % 10) + 48);            
            serialClear();
            serialSendChar('\r');
            serialSendChar('\n');
            break;
        case STATE_SECOND:
            serialSendChar(((getRTCHours() / 10) % 10) + 48);
            serialSendChar((getRTCHours() % 10) + 48);
            serialSendChar(':');
            serialSendChar(((getRTCMinutes() / 10) % 10) + 48);
            serialSendChar((getRTCMinutes() % 10) + 48);
            serialSendChar(':');
            serialSendChar('[');
            serialSendChar(((getRTCSeconds() / 10) % 10) + 48);
            serialSendChar((getRTCSeconds() % 10) + 48);  
            serialSendChar(']');
            serialClear();
            serialSendChar('\r');
            serialSendChar('\n');
            break;
        case STATE_WARNING:
            serialSendMessage("!!!!!!!!!!!!!!!!");
            serialClear();
            serialSendChar('\r');
            serialSendChar('\n');
            break;
    }
    return;
}

void outputInit(void) {
    lcdInit();
    serialInit();
    return;
}

void outputPrint(int numberScreen, char language) {
    LCD_Screen *screen = &screens[numberScreen];
    showDisplay(screen, numberScreen, language);
    showSerial(screen, numberScreen, language);
    return;
}
