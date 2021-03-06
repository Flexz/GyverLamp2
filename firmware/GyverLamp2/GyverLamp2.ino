/*
  Версия 0.21b
  Выбор палитры для частиц и конфетти
  Счётчик количества ламп онлайн в приложении
  Синхронизация текущего эффекта с приложением
  Добавлен эффект смерч

  Версия 0.20b
  Оптимизация
  Исправление критических ошибок
  Пофикшено падение АР
  Пофикшено падение лампы во время светомузыки

  Версия 0.19b
  Минимальная версия приложения 1.17!!!
  Почищен мусор, оптимизация, повышена стабильность и производительность
  Мигает теперь 16 светиков
  Снова переделана сетевая политика, упрощён и сильно ускорен парсинг
  Изменены пределы по светодиодам, что сильно увеличило производительность
  Выключенная (программно) лампа не принимает сервисные команды кроме команды включиться
  Добавлены часы, в том числе в рассвет
  Slave работает со светомузыкой сам, если не получает данные с мастера

  Версия 0.18b
  Уменьшена чувствительность хлопков
  Увеличена плавность светомузыки
  Переделана сетевая политика
  Микрофон и датчик света опрашивает только мастер и отсылает данные слейвам своей группы
  4 клика - включить первый режим
  Отправка точного времени на лампу в режиме АР для работы рассвета и синхронизации эффектов

  Версия 0.17b
  Автосмена отключается 30 сек во время настройки режимов
  Убрана кнопка upload в режимах
  Лампа чуть мигает при получении данных
  Кастом палитра работает на огне 2020
  Вкл выкл двумя хлопками
  Плавное выключение
  Починил рассвет

  Версия 0.16b
  Исправлен масштаб огня 2020
  Фикс невыключения рассвета

  Версия 0.14b
  Мелкие баги
  Вернул искры огню
  Добавлены палитры
  Добавлен огонь 2020

  Версия 0.13b
  Улучшена стабильность

  Версия 0.12b
  Мелкие исправления

  Версия 0.11b
  Добавлен редактор палитр
  Исправлены мелкие баги в эффектах
  Переподключение к роутеру после сброса сети
  Настройка ориентации матрицы из приложения
  Переработан эффект "Частицы"
  Добавлена скорость огня
  Переключение на новый/выбранный режим при редактировании
  Отправка времени из сервиса (для АР)
  Выключение по таймеру теперь плавное
  Добавлен рассвет

  TODO:
  плавная смена режимов
  Mqtt?
  Базовый пак
  Эффект погода https://it4it.club/topic/40-esp8266-i-parsing-pogodyi-s-openweathermap/
*/

// ВНИМАНИЕ! ВНИМАНИЕ! ВНИМАНИЕ! ВНИМАНИЕ! ВНИМАНИЕ! ВНИМАНИЕ! ВНИМАНИЕ!
// ДЛЯ КОМПИЛЯЦИИ ПРОШИВКИ ПОД NODEMCU/WEMOS/ESP01/ESP12 ВЫБИРАТЬ
// Инструменты / Плата Generic ESP8266
// Инструменты / Flash Size 4MB (FS:2MB OTA)
// CPU Frequency / 160 MHz (рекомендуется для стабильности светомузыки!!!)
// При прошивке с других прошивок лампы поставить: Инструменты/Erase Flash/All Flash Contents
// ESP core 2.7.4+ http://arduino.esp8266.com/stable/package_esp8266com_index.json
// FastLED 3.4.0+ https://github.com/FastLED/FastLED/releases
#define GL_BUILD 0  // 0: com 300, 1: com 900, 2: esp1 300, 3: esp1 900, 4: module 300, 5: module 900

#include "config.h"
// ------------ БИЛДЕР -------------
// #if (GL_BUILD == 0)
// #elif (GL_BUILD == 1)
// #define MAX_LEDS 900
// #elif (GL_BUILD == 2)
// #define MAX_LEDS 300
// #define BTN_PIN 0
// #define STRIP_PIN 2
// #define USE_ADC 0
// #elif (GL_BUILD == 3)
// #define MAX_LEDS 900
// #define BTN_PIN 0
// #define STRIP_PIN 2
// #define USE_ADC 0
// #elif (GL_BUILD == 4)
// #define MAX_LEDS 300
// #define STRIP_PIN 5
// #elif (GL_BUILD == 5)
// #define MAX_LEDS 900
// #define STRIP_PIN 5
// #endif

// ---------- БИБЛИОТЕКИ -----------
#include "platforms.h"    // Porting, must be first include

#include "data.h"         // данные
#include "Time.h"         // часы
#include "TimeRandom.h"   // случайные числа по времени
//#include "FastRandom.h"   // быстрый рандом
#include "Button.h"       // библа кнопки
#include "palettes.h"     // палитры
#include "NTPClient-Gyver.h"  // сервер времени (модиф)
#include "timerMillis.h"  // таймер миллис
#include "VolAnalyzer.h"  // анализатор громкости
#include "FFT_C.h"        // фурье
#include <FastLED.h>      // лента
#include <WiFiUdp.h>      // общение по UDP
#include <EEPROM.h>       // епром
#include "mString.h"      // стринг билдер
#include "Clap.h"         // обработка хлопков

// ------------------- ДАТА --------------------
Config cfg;
Preset preset[MAX_PRESETS];
Dawn dawn;
Palette pal;
WiFiServer server(80);
WiFiUDPPort Udp;
WiFiUDPPort ntpUDP;
IPAddress broadIP;
NTPClient ntp(ntpUDP);
CRGB leds[MAX_LEDS];
Time now;
Button btn(BTN_PIN);
timerMillis EEtmr(EE_TOUT), turnoffTmr, connTmr(120000ul), dawnTmr, holdPresTmr(30000ul), blinkTmr(300);
timerMillis effTmr(30, true), onlineTmr(500, true);
TimeRandom trnd;
VolAnalyzer vol(A0), low, high;
FastFilter phot;
Clap clap;

uint16_t portNum;
uint32_t udpTmr = 0, gotADCtmr = 0;
byte btnClicks = 0, brTicks = 0;
unsigned char matrixValue[11][16];
bool gotNTP = false, gotTime = false;
bool loading = true;
int udpLength = 0;
byte udpScale = 0, udpBright = 0;

// ------------------- SETUP --------------------
void setup() {
  misc();
  delay(2000);          // ждём старта есп
#ifdef DEBUG_SERIAL
  Serial.begin(115200);
  DEBUGLN();
#endif
  startStrip();         // старт ленты
  btn.setLevel(digitalRead(BTN_PIN));   // смотрим что за кнопка
  EE_startup();         // читаем епром
#ifndef SKIP_WIFI
  checkUpdate();        // индикация было ли обновление
  showRGB();            // показываем ргб
  checkGroup();         // показываем или меняем адрес
  checkButton();        // проверяем кнопку на удержание
  startWiFi();          // старт вайфай
  setupTime();          // выставляем время
#endif
  setupADC();           // настраиваем анализ
  presetRotation(true); // форсировать смену режима
}

void loop() {
  timeTicker();       // обновляем время
  yield();
#ifndef SKIP_WIFI
  tryReconnect();     // пробуем переподключиться если WiFi упал
  yield();
  parsing();          // ловим данные
  yield();
#endif
  checkEEupdate();    // сохраняем епром
  presetRotation(0);  // смена режимов по расписанию
  effectsRoutine();   // мигаем
  yield();
  button();           // проверяем кнопку
  checkAnalog();      // чтение звука и датчика
  yield();
  iAmOnline();
}
