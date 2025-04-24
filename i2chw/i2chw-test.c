#include "i2chw.h"

#include <stdio.h>

i2chw_error_t I2CHW_Init(const i2chw_bus_t bus_num)
{
  printf("I2C bus initialized. Bus number: %d.\n", bus_num);
  return I2CHW_SUCCESS;
}

i2chw_error_t I2CHW_Configure(const i2chw_bus_t bus_num, const i2chw_cfg_t *p_config)
{
  printf("I2C bus configured. Bus number: %d.\n", bus_num);
  printf("Bus frequency: %d\n", p_config->bus_freq);
  printf("Direction mode: %d\n", p_config->dir_mode);
  printf("\n");
  return I2CHW_SUCCESS;
}

i2chw_error_t I2CHW_WriteSync(const i2chw_dev_t *p_dev, const uint8_t *p_tx_data, const uint16_t tx_data_len)
{
  printf("%d bytes of data transmitted to %d.\n", tx_data_len, p_dev->dev_addr);
  printf("Reg: %d, data: %d\n", p_tx_data[0], p_tx_data[1]);
  printf("\n");
  return I2CHW_SUCCESS;
}

i2chw_error_t I2CHW_WriteReadSync(const i2chw_dev_t *p_dev, const uint8_t *p_tx_data,
                                  const uint16_t tx_data_len, uint8_t *p_rx_data, const uint16_t rx_data_len)
{
  printf("%d bytes of data transmitted to %d.\n", tx_data_len, p_dev->dev_addr);
  printf("Reg: %d, data: %d\n", p_tx_data[0], p_tx_data[1]);
  printf("%d bytes of data recieved from %d.\n", rx_data_len, p_dev->dev_addr);
  printf("Reg: %d, data: %d\n", p_rx_data[0], p_rx_data[1]);
  printf("\n");
  return I2CHW_SUCCESS;
}

i2chw_error_t I2CHW_ReadSync(const i2chw_dev_t *p_dev, uint8_t *p_rx_data, const uint16_t rx_data_len)
{
  printf("%d bytes of data recieved from %d.\n", rx_data_len, p_dev->dev_addr);
  printf("Reg: %d, data: %d\n", p_rx_data[0], p_rx_data[1]);
  printf("\n");
  return I2CHW_SUCCESS;
}
