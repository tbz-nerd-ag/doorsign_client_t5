#include <Arduino.h>
#include <EEPROM.h>

//projedt files
#include <header.h>

//512 Byte | one letter a Byte
static int EEPROM_SIZE = 512;
//EEPROM info | NAMEadd = address | NAMEdata = data || address equals letter  || COUNT LETTERS!!!
static int ssidadd = 0, passadd = 20, idadd= 50, roomadd = 55, crcadd = 500;
String ssid = "", password = "";
int id = -1;
String ssidfallback = "", passwordfallback = "";


void readEEPROM() {
  //ssid and password for wifi
  //String ssid = "", password = "";

  uint16_t sum = 0;
  uint8_t crcwifi;

  Serial.println("Begin to read EEPROM ...");

  EEPROM.begin(EEPROM_SIZE);

  //check if EEPROM Address is initialized || didnt check corruption
  if (EEPROM.read(ssidadd) != 0xFF) {
    ssid = EEPROM.readString(ssidadd);
    Serial.println("Found SSID Data in EEPROM ...");
    //Serial.println(ssid);
  } else {
    Serial.println("Didnt find SSID Data in EEPROM!");
    //fallback 
    if (ssidfallback != "") {
      ssid = ssidfallback;
      Serial.println("Found SSID Fallback");
    } else {
      Serial.println("Didnt find SSID Data!");
    }
  }
  if (EEPROM.read(passadd) != 0xFF) {
    password = EEPROM.readString(passadd);
    Serial.println("Found Password Data in EEPROM ...");
    //Serial.println(password);
  } else {
    Serial.println("Didnt find Password Data in EEPROM!");
    //fallback 
    if (passwordfallback != "") {
      password = passwordfallback;
      Serial.println("Found Password Fallback");
    } else {
      Serial.println("Didnt find Password Data!");
    }
  }
    if (EEPROM.read(idadd) != 0xFF) {
    id = EEPROM.readInt(idadd);
    Serial.println("Found Device ID in EEPROM ...");
  } else {
    Serial.println("Didnt find Device ID in EEPROM!");
  }
  Serial.println("Read CRC ...");
  if (EEPROM.read(crcadd) != 0xFF) {
    crcwifi = EEPROM.readUChar(crcadd);
    Serial.println("Found CRC Data in EEPROM ...");
  } else {
    Serial.println("Didnt find CRC Data in EEPROM!");
  }

  for (size_t i = 0; i < (ssid.length() + password.length()); i++) {
    if (i < ssid.length()) sum += (uint8_t)ssid[i];
    else sum += (uint8_t)password[i - ssid.length()];
  }

  uint8_t calc = sum & 0xFF; // 1-Byte Prüfsumme

  if (calc != crcwifi) {
    Serial.println("EEPROM CRC ERROR | Try again!");
    Serial.println("Calc CRC:"+ String(calc));
    if (ssidfallback != "") {
      password = ssidfallback;
      Serial.println("Found SSID Fallback");
    } else {
      Serial.println("Didnt find SSID Data!");
    }
    if (passwordfallback != "") {
      password = passwordfallback;
      Serial.println("Found Password Fallback");
    } else {
      Serial.println("Didnt find Password Data!");
    }
  } else {
    Serial.println("CRC Check finished ...");
  }

  Serial.println("End read EEPROM ...");
}

bool readRoom() {
  if (EEPROM.read(roomadd) != 0xFF) {
    ssid = EEPROM.readDouble(roomadd);
    Serial.println("Found Room Number in EEPROM ...");
    return true;
  } else {
    Serial.println("Didnt find Room Number in EEPROM!");
    return false;
  }
}
