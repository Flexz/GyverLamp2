#ifndef __FONT6X8_H
#define __FONT6X8_H

class Font6x8 : public FontBase
{
    public:
        void DrawChar(int x, int y, char sym, CRGB color, float blendFactor);

        int Width() {return 6;}
        int Height() {return 8;}
};

#endif