#ifndef DAC7568_H
#define DAC7568_H

#include <Arduino.h>

enum channel_mode_t
{
    CHANNEL_ON = 0,
    CHANNEL_OFF_1k = 1,
    CHANNEL_OFF_100k = 2,
    CHANNEL_OFF = 3
};

class DAC7568
{
public:
    DAC7568(uint16_t vref_mv, int sync_pin);
    void begin();
    void set_chan_mode(uint8_t chan_num, channel_mode_t mode);
    void set_chan_voltage(uint8_t chan_num, uint16_t voltage_mv);

private:
    uint16_t _vref_mv;
    uint8_t _output_gain;
    int _sync_pin;

    void send_spi_frame(uint32_t frame);
    void set_chan_voltage_register(uint8_t chan_num, uint16_t value);
};

#endif