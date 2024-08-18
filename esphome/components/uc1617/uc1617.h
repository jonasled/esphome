#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"
#include "esphome/components/display/display_buffer.h"
#include <U8g2lib.h>

namespace esphome {
namespace UC1617 {

class UC1617 : public display::DisplayBuffer,
                public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_HIGH, spi::CLOCK_PHASE_TRAILING,
                                      spi::DATA_RATE_8MHZ> {
 public:
  const uint8_t UC1617_POWERDOWN = 0x04;
  const uint8_t UC1617_ENTRYMODE = 0x02;
  const uint8_t UC1617_EXTENDEDINSTRUCTION = 0x01;

  const uint8_t UC1617_DISPLAYBLANK = 0x0;
  const uint8_t UC1617_DISPLAYNORMAL = 0x4;
  const uint8_t UC1617_DISPLAYALLON = 0x1;
  const uint8_t UC1617_DISPLAYINVERTED = 0x5;

  const uint8_t UC1617_FUNCTIONSET = 0x20;
  const uint8_t UC1617_DISPLAYCONTROL = 0x08;
  const uint8_t UC1617_SETYADDR = 0x40;
  const uint8_t UC1617_SETXADDR = 0x80;

  const uint8_t UC1617_SETTEMP = 0x04;
  const uint8_t UC1617_SETBIAS = 0x10;
  const uint8_t UC1617_SETVOP = 0x80;
  uint8_t contrast_;

  void set_contrast(uint8_t contrast) { this->contrast_ = contrast; }
  float get_setup_priority() const override { return setup_priority::PROCESSOR; }

  void command(uint8_t value);
  void data(uint8_t value);

  void initialize();
  void dump_config() override;
  void HOT display();

  void update() override;

  void fill(Color color) override;

  void setup() override {
    this->initialize();
  }

  display::DisplayType get_display_type() override { return display::DisplayType::DISPLAY_TYPE_BINARY; }

 protected:

  void draw_absolute_pixel_internal(int x, int y, Color color) override;

  void start_command_();
  void end_command_();
  void start_data_();
  void end_data_();

  int get_width_internal() override;
  int get_height_internal() override;

};

}  // namespace UC1617
}  // namespace esphome