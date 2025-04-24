#include "rgbw-i2c-driver.h"

int main()
{
  i2chw_dev_t dev;

  i2chw_error_t error = rgbw_driver_init(&dev, I2CHW_BUS_I2C0);
  if (error != I2CHW_SUCCESS)
  {
    return error;
  }
  error = rgbw_driver_channel_switch(&dev, 2, 1);
  if (error != I2CHW_SUCCESS)
  {
    return error;
  }
  error = rgbw_driver_set_channel_brightness(&dev, 2, 168);
  if (error != I2CHW_SUCCESS)
  {
    return error;
  }
  error = rgbw_driver_all_channels_switch(&dev, 1);
  if (error != I2CHW_SUCCESS)
  {
    return error;
  }
  error = rgbw_driver_set_color(&dev, 17, 28, 49, 251);
  if (error != I2CHW_SUCCESS)
  {
    return error;
  }
  error = rgbw_driver_all_channels_switch(&dev, 0);
  if (error != I2CHW_SUCCESS)
  {
    return error;
  }

  return 0;
}