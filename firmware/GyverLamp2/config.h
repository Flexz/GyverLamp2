// ---------- Настройки -----------
#define GL_KEY "GL"         // ключ сети
#define TARGET_ESP32
//#define TARGET_ESP8266

// ------------ Кнопка -------------
#define BTN_PIN 0           // пин кнопки GPIO4 (D2). Или 0 для схемы с ESP-01 !!
#define USE_BTN 1           // 1 использовать кнопку, 0 нет

// ------------- АЦП --------------
#define USE_ADC 0           // можно выпилить АЦП
#define USE_CLAP 1          // два хлопка в ладоши вкл выкл лампу
#define MIC_VCC D3          // питание микрофона
#define PHOT_VCC D2         // питание фоторезистора

// ------------ Лента -------------
#define STRIP_PIN 12         // пин ленты  
#define MAX_LEDS 600        // макс. светодиодов
#define STRIP_CHIP WS2812   // чип ленты
#define STRIP_COLOR GRB     // порядок цветов в ленте
#define STRIP_VOLT 5        // напряжение ленты, V
/*
  WS2811, GBR, 12V
  WS2812, GRB, 5V
  WS2813, GRB, 5V
  WS2815, GRB, 12V
  WS2818, RGB, 12V
*/

// ------------ WiFi AP ------------
const char AP_NameChar[] = "GyverLamp2";
const char WiFiPassword[] = "12345678";

// ------------ Прочее -------------
#define GL_VERSION 21
#define EE_TOUT 30000       // таймаут сохранения епром после изменения, мс
#define DEBUG_SERIAL        // закомментируй чтобы выключить отладку (скорость 115200)
#define EE_KEY 55           // ключ сброса WiFi (измени для сброса всех настроек)
#define NTP_UPD_PRD 5       // период обновления времени с NTP сервера, минут
