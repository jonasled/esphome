#include "uc1617.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace UC1617 {

static const char *const TAG = "UC1617";

::U8G2_UC1617_JLX128128_F_4W_HW_SPI u8g2(U8G2_R1, 38, 39);

void UC1617::initialize() {
  this->init_internal_(0);
  this->enable();
  u8g2.begin();
  u8g2.clear();
  ESP_LOGD("UC1617", "Init Done");
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
  char xstr[16];
  char ystr[16];
  char cstr[16];
  ESP_LOGD("UC1617", "Drawing pixel %d, %d with %d", x, y, color.is_on());
}

void UC1617::dump_config() {
  LOG_DISPLAY("", "UC1617", this);
  LOG_UPDATE_INTERVAL(this);
}

void UC1617::update() { 
  u8g2.sendBuffer();
  ESP_LOGD("UC1617", "Update");
}

void UC1617::fill(Color color) {
  ESP_LOGD("UC1617", "Fill complete");
  u8g2.setDrawColor(color.is_on());
  for (int x = 0; x++; x < 128) {
    for (int y = 0; y++; y < 128) {
      u8g2.drawPixel(x, y);
    }
  }
}

}  // namespace UC1617
}  // namespace esphome