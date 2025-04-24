#include "rgbw-i2c-driver.h"

#include <time.h>
#include <unistd.h>

i2chw_error_t rgbw_driver_init(i2chw_dev_t *dev, i2chw_bus_t bus)
{
  i2chw_cfg_t cfg = {
      .bus_freq = I2CHW_400_KHZ, // Because of min clock period = 2.5us
      .dir_mode = I2CHW_MASTER_MODE};
  i2chw_error_t error = I2CHW_Configure(bus, &cfg);
  if (error != I2CHW_SUCCESS)
    return error;

  error = I2CHW_Init(bus);
  if (error != I2CHW_SUCCESS)
    return error;

  dev->bus_num = bus;
  dev->dev_addr = RGBW_DRIVER_ADDR;
  dev->addr_width = I2CHW_ADDR_WIDTH_7BIT;

  uint8_t reset_cfg[2] = {RESET_REG, 0xE0};
  error = I2CHW_WriteSync(dev, reset_cfg, sizeof(reset_cfg));
  if (error != I2CHW_SUCCESS)
    return error;

  usleep(RESET_DELAY_MCS);

  return I2CHW_SUCCESS;
}

i2chw_error_t rgbw_driver_set_channel_brightness(i2chw_dev_t *dev, uint8_t channel, uint8_t brightness)
{
  uint8_t reg_addr = IOUT_D1_REG + (channel - 1);
  uint8_t data[2] = {reg_addr, brightness};
  return I2CHW_WriteSync(dev, data, sizeof(data));
}

i2chw_error_t rgbw_driver_channel_switch(i2chw_dev_t *dev, uint8_t channel, bool state)
{
  // Reading current state of 4-th register
  uint8_t enable_reg_state;
  uint8_t data[2] = {ENABLE_REG};
  i2chw_error_t error = I2CHW_WriteReadSync(dev, data, sizeof(data[0]), &enable_reg_state, sizeof(enable_reg_state));
  if (error != I2CHW_SUCCESS)
    return error;

  if (state)
    enable_reg_state |= (1u << (channel - 1));
  else
    enable_reg_state &= ~(1u << (channel - 1));
  data[1] = enable_reg_state;

  return I2CHW_WriteSync(dev, data, sizeof(data));
}

i2chw_error_t rgbw_driver_all_channels_switch(i2chw_dev_t *dev, bool state)
{
  uint8_t data[2] = {ENABLE_REG, 0x00};
  if (state)
    data[1] = 0x55;

  return I2CHW_WriteSync(dev, data, sizeof(data));
}

i2chw_error_t rgbw_driver_set_color(i2chw_dev_t *dev, uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
  uint8_t data[8] = {
      IOUT_D1_REG, r,
      IOUT_D2_REG, g,
      IOUT_D3_REG, b,
      IOUT_D4_REG, w};

  for (uint8_t i = 0; i < 4; i++)
  {
    uint8_t frame[] = {data[2 * i], data[2 * i + 1]};
    i2chw_error_t error = I2CHW_WriteSync(dev, frame, sizeof(frame));
    if (error != I2CHW_SUCCESS)
      return error;
  }

  return I2CHW_SUCCESS;
}
