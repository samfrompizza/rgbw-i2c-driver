#ifndef RGBW_I2C_DRIVER
#define RGBW_I2C_DRIVER

#include "i2chw.h"

#define RGBW_DRIVER_ADDR 0x30

#define RESET_REG 0x00
#define ENABLE_REG 0x04
#define IOUT_D1_REG 0x06
#define IOUT_D2_REG 0x07
#define IOUT_D3_REG 0x08
#define IOUT_D4_REG 0x09

#define RESET_DELAY_MCS 200

/** 
 * @brief Initialize RGBW chip
 * 
 * @param dev - pointer to I2C device configuration
 * @param bus_num - number of I2C bus
 * @return hal_error_t - initialization result
 *         I2CHW_SUCCESS - the chip was initialized successfully
 *         I2CHW_ERR_INVALID_PARAMS - invalid parameters are given
 *         I2CHW_ERR_HW - the chip was not initialized because of HW issues 
 */
i2chw_error_t rgbw_driver_init(i2chw_dev_t *dev, i2chw_bus_t bus);

/** 
 * @brief Set channel brightness
 * 
 * @param dev - pointer to I2C device configuration
 * @param channel - number of channel
 * @param brightness - value from 0 to 191, any higher value will reach Imax
 * @return i2chw_error_t - result of transmission
 *         I2CHW_SUCCESS - all data has been transmitted
 *         I2CHW_ERR_INVALID_PARAMS - invalid parameters are given
 *         I2CHW_ERR_TIMEOUT - transmission was not finished because of execution timeout
 *         I2CHW_ERR_NACK - the device did't set ACK bit
 *         I2CHW_ERR_HW - the bus has hardware issues
 */
i2chw_error_t rgbw_driver_set_channel_brightness(i2chw_dev_t *dev, uint8_t channel, uint8_t brightness);

/** 
 * @brief Turn the channel ON/OFF
 * 
 * @param dev - pointer to I2C device configuration
 * @param channel - number of channel
 * @param state - 1 - ON, 0 - OFF
 * @return i2chw_error_t - result of transmission
 *         I2CHW_SUCCESS - all data has been transmitted
 *         I2CHW_ERR_INVALID_PARAMS - invalid parameters are given
 *         I2CHW_ERR_TIMEOUT - transmission was not finished because of execution timeout
 *         I2CHW_ERR_NACK - the device did't set ACK bit
 *         I2CHW_ERR_HW - the bus has hardware issues
 */
i2chw_error_t rgbw_driver_channel_switch(i2chw_dev_t *dev, uint8_t channel, bool state);

/** 
 * @brief Turn all channels ON/OFF
 * 
 * @param dev - pointer to I2C device configuration
 * @param state - 1 - ON, 0 - OFF
 * @return i2chw_error_t - result of transmission
 *         I2CHW_SUCCESS - all data has been transmitted
 *         I2CHW_ERR_INVALID_PARAMS - invalid parameters are given
 *         I2CHW_ERR_TIMEOUT - transmission was not finished because of execution timeout
 *         I2CHW_ERR_NACK - the device did't set ACK bit
 *         I2CHW_ERR_HW - the bus has hardware issues
 */
i2chw_error_t rgbw_driver_all_channels_switch(i2chw_dev_t *dev, bool state);

/** 
 * @brief Set the color in RGBW space
 * 
 * @param dev - pointer to I2C device configuration
 * @param r - D1 channel value
 * @param g - D2 channel value
 * @param b - D3 channel value
 * @param w - D4 channel value
 * @return i2chw_error_t - result of transmission
 *         I2CHW_SUCCESS - all data has been transmitted
 *         I2CHW_ERR_INVALID_PARAMS - invalid parameters are given
 *         I2CHW_ERR_TIMEOUT - transmission was not finished because of execution timeout
 *         I2CHW_ERR_NACK - the device did't set ACK bit
 *         I2CHW_ERR_HW - the bus has hardware issues
 */
i2chw_error_t rgbw_driver_set_color(i2chw_dev_t *dev, uint8_t r, uint8_t g, uint8_t b, uint8_t w);

#endif