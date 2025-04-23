#include "rgbw-i2c-driver.h"

int main() {
  i2chw_dev_t dev;

  rgbw_driver_init(&dev, I2CHW_BUS_I2C0);
  rgbw_driver_channel_switch(&dev, 2, 1);
  rgbw_driver_set_channel_brightness(&dev, 2, 168);
  rgbw_driver_all_channels_switch(&dev, 1);
  rgbw_driver_set_color(&dev, 17, 28, 49, 251);
  rgbw_driver_all_channels_switch(&dev, 0);

  return 0;
}