#include <Arduino.h>
#include "DAC7568.h"
#include <SPI.h>

SPISettings DAC_SPI_Settings = SPISettings(2000000, MSBFIRST, SPI_MODE1);

DAC7568::DAC7568(uint16_t vref_mv, int sync_pin)
{
  _sync_pin = sync_pin;
  pinMode(_sync_pin, OUTPUT);
  digitalWrite(_sync_pin, HIGH);

  _vref_mv = vref_mv;

  _output_gain = 1; // -A version has 1x gain, -C version has 2x gain
}

void DAC7568::begin()
{
  SPI.begin();
}

void DAC7568::set_chan_voltage(uint8_t chan_num, uint16_t voltage_mv)
{
  // calculate value to write to DAC register
  // vout = (SETVAL / 65535) * vref * gain
  // SETVAL = (vout * 65535) / (vref * gain)

  uint32_t setval = (voltage_mv * 65536) / (_vref_mv * _output_gain);
  set_chan_voltage_register(chan_num, (uint16_t)setval);
}

void DAC7568::set_chan_mode(uint8_t chan_num, channel_mode_t mode)
{
  uint32_t frame = 0b00000100000000000000000000000000;
  frame = frame | (1 << chan_num);
  frame = frame | ((mode & 0b11) << 8);
  send_spi_frame(frame);
}

void DAC7568::send_spi_frame(uint32_t frame)
{
  SPI.beginTransaction(DAC_SPI_Settings);
  digitalWrite(_sync_pin, LOW);
  SPI.transfer((uint8_t)(frame >> 24));
  SPI.transfer((uint8_t)(frame >> 16));
  SPI.transfer((uint8_t)(frame >> 8));
  SPI.transfer((uint8_t)(frame));
  digitalWrite(_sync_pin, HIGH);
  SPI.endTransaction();
}

void DAC7568::set_chan_voltage_register(uint8_t chan_num, uint16_t value)
{
  uint32_t frame = 0b00000011000000000000000000000000;
  frame = frame | ((chan_num & 0b111) << 20);
  frame = frame | (value << 4);
  send_spi_frame(frame);
}