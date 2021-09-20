#include "display.h"

#define STROBE_TM1 13
#define CLOCK_TM 4      // clock = GPIO connected to clock line of module
#define DIO_TM 5        // data = GPIO connected to data line of module
#define HIGH_FREQ false //default false, If using a high freq CPU > ~100 MHZ set to true.

DisplayPanel::DisplayPanel()
{
    // Constructor object (GPIO STB , GPIO CLOCK , GPIO DIO, use high freq MCU)
    ledMap = new TM1638plus(STROBE_TM1, CLOCK_TM, DIO_TM, HIGH_FREQ);
    ledMap->displayBegin();
}

void DisplayPanel::DisplayLedMap(uint32_t data0, uint32_t data1)
{
    ledMap->display7Seg(0, data0 % 0x100);
    ledMap->display7Seg(1, data0 / 0x100 % 0x100);
    ledMap->display7Seg(2, data0 / 0x10000 % 0x100);
    ledMap->display7Seg(3, data0 / 0x1000000);
    ledMap->display7Seg(4, data1 % 0x100);
}
