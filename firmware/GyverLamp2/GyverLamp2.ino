// 0.10
// исправлена обработка ключа
// добавлена совместимость с nodemcu
// поворот матрицы
// обновление прошивок для разных схем
// исправлен цвет огня
// индикация обновления при запуске

// мигает 8:
// красным - не смог подключиться к АР
// зелёным - смог подключиться к АР
// жёлтым - создал свою АП
// бирюзовым - успешно обновился на новую версию
// синим - обновился на ту же версию
// розовым - сброс всех настроек (первый запуск)

// Generic ESP8266, 4MB (FS:2MB OTA)
// ESP core 2.7.4+ http://arduino.esp8266.com/stable/package_esp8266com_index.json
// FastLED 3.4.0+ https://github.com/FastLED/FastLED/releases

#include "config.h"
// ------------ БИЛДЕР -------------
//#define MAX_LEDS 1200

// esp01
//#define BTN_PIN 0
//#define STRIP_PIN 2
//#define USE_ADC 0

// GL2 module
//#define STRIP_PIN 5     // GPIO5 на gl module (D1 на wemos/node)

// ---------- БИБЛИОТЕКИ -----------
#include "platforms.h"    // Porting, must be first include

#include "data.h"         // данные
#include "Time.h"         // часы
#include "TimeRandom.h"   // случайные числа по времени
#include "FastRandom.h"   // быстрый рандом
#include "Button.h"       // библа кнопки
#include "palettes.h"     // палитры
#include "NTPClient-Gyver.h"  // сервер времени (модиф)
#include "timerMillis.h"  // таймер миллис
#include "VolAnalyzer.h"  // анализатор громкости
#include "FFT_C.h"        // фурье
#include <FastLED.h>      // лента
#include <WiFiUdp.h>      // общение по UDP
#include <EEPROM.h>       // епром

// ------------------- ДАТА --------------------
Config cfg;
Preset preset[MAX_PRESETS];
Dawn dawn;
WiFiServer server(80);
WiFiUDPPort Udp;
WiFiUDPPort ntpUDP;
NTPClient ntp(ntpUDP);
CRGB leds[MAX_LEDS];
Time now;
Button btn(BTN_PIN);
timerMillis EEtmr(EE_TOUT), turnoffTmr;
TimeRandom trnd;
VolAnalyzer vol(A0), low, high;
FastFilter phot;

byte btnClicks = 0, brTicks = 0;
unsigned char matrixValue[11][16];
bool gotNTP = false;
void blink8(CRGB color);

// ------------------- SETUP --------------------
void setup() {
  delay(800);
  memset(matrixValue, 0, sizeof(matrixValue));
#ifdef DEBUG_SERIAL
  Serial.begin(115200);
  DEBUGLN();
#endif
  EEPROM.begin(512);    // старт епром
  startStrip();         // старт ленты  
  btn.setLevel(digitalRead(BTN_PIN));   // смотрим что за кнопка
  EE_startup();         // читаем епром
  checkUpdate();        // индикация было ли обновление
  showRGB();            // показываем ргб  
  checkGroup();         // показываем или меняем адрес
  checkButton();        // проверяем кнопку на удержание
  startWiFi();          // старт вайфай
  setupTime();          // выставляем время
  setupADC();           // настраиваем анализ
  presetRotation(true); // форсировать смену режима
}

void loop() {
  timeTicker();       // обновляем время
  yield();
  parsing();          // ловим данные
  yield();
  checkEEupdate();    // сохраняем епром
  presetRotation(0);  // смена режимов по расписанию
  effectsRoutine();   // мигаем
  yield();
  button();           // проверяем кнопку
  checkAnalog();      // чтение звука и датчика
}
