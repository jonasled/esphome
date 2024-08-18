#include "uc1617.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace UC1617 {

static const char *const TAG = "uc1617";

U8G2_UC1617_JLX128128_F_4W_HW_SPI u8g2(U8G2_R1, LCD_CS_PIN, LCD_CD_PIN);

void UC1617::setup_pins_() {
  this->spi_setup();
  this->init_reset_();
}

void UC1617::initialize() {
  this->init_internal_(this->get_buffer_length_());
  this->enable();
  u8g2.begin();
  u8g2.clear();
}

int UC1617::get_width_internal() { return 128; }
int UC1617::get_height_internal() { return 128; }

void HOT UC1617::display() { u8g2.sendBuffer(); }

void HOT UC1617::draw_absolute_pixel_internal(int x, int y, Color color) {
  if (x >= this->get_width_internal() || y >= this->get_height_internal() || x < 0 || y < 0) {
    return;
  }

  u8g2.setDrawColor(color.is_on());
  u8g2.drawPixel(x, y);
}

void UC1617::dump_config() {
  LOG_DISPLAY("", "UC1617", this);
  LOG_UPDATE_INTERVAL(this);
}

void UC1617::update() { u8g2.sendBuffer(); }

void UC1617::fill(Color color) {
  u8g2.setDrawColor(color.is_on());
  for (int x = 0; x++; x < 128) {
    for (int y = 0; y++; y < 128) {
      u8g2.drawPixel(x, y);
    }
  }
}

}  // namespace UC1617
}  // namespace esphome