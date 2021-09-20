#include <Arduino.h>
#include <TM1638plus.h>

class DisplayPanel
{
private:
    TM1638plus* ledMap;

public:
    DisplayPanel();
    void DisplayLedMap(uint32_t data0, uint32_t data1);
};