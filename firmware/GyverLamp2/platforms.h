#ifndef __PLATFORMS_H
#define __PLATFORMS_H

#ifdef TARGET_ESP32

// ---------- ESP32 port by Flexz -----------
#define FASTLED_ESP32_I2S

#define D6 6 //На ESP32 недоступен (занят под свои нужды платы)
#define D5 5 //На ESP32 недоступен (занят под свои нужды платы)
#define D4 4
#define D3 3
#define D2 2
#define D1 1
#define D0 0
#define UDP_TX_PACKET_MAX_SIZE 8192 //Заголовок WiFiUdp для ESP8266 определяет эту константу, а для ESP32 - нет

#include "WiFi.h"

class WiFiUDPPort : public WiFiUDP
{
public:
  WiFiUDPPort() : WiFiUDP() {}
  using Print::write; //Расширение ради этой строчки, в версии WiFiUDP для ESP8266 она есть, а для ESP32 - нет
};

#elif defined TARGET_ESP8266

#include <ESP8266WiFi.h>  // базовая либа есп
#include "ESP8266httpUpdate.h"  // OTA

#else
#error Target platforn not defined
#endif

#endif
