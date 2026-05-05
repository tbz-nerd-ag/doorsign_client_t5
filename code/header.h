#pragma once //ruft die datei nor einmal auf
extern String ssid, password, IP, MAC;
extern uint8_t *framebuffer;
extern int id;
extern String ssidfallback, passwordfallback;
//extern const char* broker;
extern char broker[];

extern struct tm timeinfo;
extern char time_str[32];


//Declaration
void readEEPROM();
bool readRoom();

void eeprominfo();

void errormenu(int menu);

void connectwifi(String mode);
void rtctimeset();
void connectmqtt();
void sendmqtthello();
void waitofinitmsg();
void callback(char* topic, byte* payload, unsigned int length);
