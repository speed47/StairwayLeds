#ifndef _MAKECOLOR_H
#define _MAKECOLOR_H

#define HUE_RED     0
#define HUE_ORANGE  60
#define HUE_YELLOW  120
#define HUE_GREEN   180
#define HUE_BLUE    240
#define HUE_VIOLET  300

int makeColor(unsigned int hue, unsigned int saturation, unsigned int lightness);
unsigned int h2rgb(unsigned int v1, unsigned int v2, unsigned int hue);

#endif
