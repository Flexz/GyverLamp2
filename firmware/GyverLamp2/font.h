#include <FastLED.h>
#include "data.h"

extern CRGB leds[];
extern Config cfg;

uint16_t getPix(int x, int y);

class FontBase
{
    public:
        void DrawChar(int x, int y, char sym, CRGB color, float blendFactor);
        int Width();
        int Height();
};

#include "font6x8.h"