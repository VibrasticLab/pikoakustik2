/**
 * Original works:
 * https://github.com/baoshi/ESP-I2C-OLED/blob/master/include/i2c.h
 */

#ifndef OLED_I2C_H
#define OLED_I2C_H

#include <stdint.h>

#define I2C_TRUE    0
#define I2C_FALSE   1

void i2c_init(void);
uint8_t i2c_start(void);
void i2c_stop(void);
uint8_t i2c_write(uint8_t data);
uint8_t i2c_read(void);
void i2c_set_ack(uint8_t ack);

#endif // SSD1306_I2C_H
