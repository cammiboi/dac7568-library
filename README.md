# DAC7568 Library

Arduino Library to control the 8 channel digital to analog converter IC DAC7568 from TI.

## DAC7568 Features

* 8 programmable voltage outputs
* Buffered outputs, no need for external OP amp
* 3.3V or 5V supply operation
* Internal high accuracy reference 2.5V (not yet supported in this libarary)

## Important Notes

There are 2 versions of this IC:
* -A gain 1x, max output 2.5V when using internal ref, or 1x VREF_IN pin if using external voltage ref
* -C gain 2x, max output 5V when using internal ref, or 2x VREF_IN pin if using external voltage ref

## Using the Library

```c
#include <Arduino.h>
#include "DAC7568.h"

DAC7568 DAC = DAC7568(3300, 17); // setup DAC, 3.3V external reference (VREF_IN pin), pin 17 for SYNC

void setup()
{
}

void loop()
{
    DAC.set_chan_voltage(0, 1000); // set channel 0 (A) to 1V
    DAC.set_chan_voltage(3, 2500); // set channel 3 (D) to 2.5V

    delay(3000);

    DAC.set_chan_voltage(0, 3000); // set channel 0 (A) to 3V
    DAC.set_chan_voltage(3, 500);  // set channel 3 (D) to 0.5V

    delay(3000);
}
```

## Functions

```c
set_chan_voltage(uint8_t chan_num, uint16_t voltage_mv);  // set chan_num (0-7) to voltage_mv mv

set_chan_mode(uint8_t chan_num, channel_mode_t mode);     // set chan_num to mode (see enum in .h file for options) the DAC channels default to ON
```
