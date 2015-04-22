#ifndef _MAKECOLOR_H
#define _MAKECOLOR_H

#define HUE_RED          0
#define HUE_ORANGE      30
#define HUE_YELLOW      60
#define HUE_LIGHTGREEN  90
#define HUE_GREEN      120
#define HUE_LIGHTCYAN  150
#define HUE_CYAN       180
#define HUE_LIGHTBLUE  210
#define HUE_BLUE       240
#define HUE_PINK       270
#define HUE_VIOLET     300
#define HUE_MAGENTA    330

int makeColor(unsigned int hue, unsigned int saturation, unsigned int lightness);
unsigned int h2rgb(unsigned int v1, unsigned int v2, unsigned int hue);

#endif
