/**
 * Original Works:
 * https://github.com/baoshi/ESP-I2C-OLED/blob/master/user/i2c.c
 */

#include "my_includes.h"

#define SDA_MUX     PERIPHS_IO_MUX_GPIO5_U
#define SDA_FUNC    FUNC_GPIO5
#define SDA_PIN     5
#define SDA_BIT     BIT5

#define SCL_MUX     PERIPHS_IO_MUX_GPIO4_U
#define SCL_FUNC    FUNC_GPIO4
#define SCL_PIN     4
#define SCL_BIT     BIT4

#define _DELAY      os_delay_us(1)

#ifndef GPIO_PIN_ADDR
 #define GPIO_PIN_ADDR(i) (GPIO_PIN0_ADDRESS + i*4)
#endif

#define _SDA1 GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, SDA_BIT)
#define _SDA0 GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, SDA_BIT)

#define _SCL1 GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, SCL_BIT)
#define _SCL0 GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, SCL_BIT)

#define _SDAX ((GPIO_REG_READ(GPIO_IN_ADDRESS) >> SDA_PIN) & 0x01)
#define _SCLX ((GPIO_REG_READ(GPIO_IN_ADDRESS) >> SCL_PIN) & 0x01)

void i2c_init(void){
    PIN_FUNC_SELECT(SDA_MUX, SDA_FUNC);
    PIN_FUNC_SELECT(SCL_MUX, SCL_FUNC);

    GPIO_REG_WRITE(
        GPIO_PIN_ADDR(GPIO_ID_PIN(SDA_PIN)),
        GPIO_REG_READ(GPIO_PIN_ADDR(GPIO_ID_PIN(SDA_PIN))) | GPIO_PIN_PAD_DRIVER_SET(GPIO_PAD_DRIVER_ENABLE)
    );

    GPIO_REG_WRITE(
        GPIO_PIN_ADDR(GPIO_ID_PIN(SCL_PIN)),
        GPIO_REG_READ(GPIO_PIN_ADDR(GPIO_ID_PIN(SCL_PIN))) | GPIO_PIN_PAD_DRIVER_SET(GPIO_PAD_DRIVER_ENABLE)
    );

    _SDA1;
    _SCL1;

    GPIO_REG_WRITE(GPIO_ENABLE_ADDRESS, GPIO_REG_READ(GPIO_ENABLE_ADDRESS) | SDA_BIT | SCL_BIT);

    return;
}

uint8_t i2c_start(void){
    _SDA1;
    _SCL1;
    _DELAY;

    if (_SDAX == 0) return I2C_FALSE;

    _SDA0;
    _DELAY;
    _SCL0;

    return I2C_TRUE;
}

void i2c_stop(void){
    _SDA0;
    _SCL1;
    _DELAY;

    while (_SCLX == 0);

    _SDA1;
    _DELAY;
}

uint8_t i2c_write(uint8_t data)
{
    uint8_t ibit;
    uint8_t ret;

    for (ibit = 0; ibit < 8; ++ibit)
    {
        if (data & 0x80)
            _SDA1;
        else
            _SDA0;

        _DELAY;
        _SCL1;
        _DELAY;
        data = data << 1;
        _SCL0;
    }
    _SDA1;
    _DELAY;
    _SCL1;
    _DELAY;

    ret = (_SDAX == 0);
    _SCL0;
    _DELAY;

    return ret;
}

uint8_t ICACHE_FLASH_ATTR i2c_read(void)
{
    uint8_t data = 0;
    uint8_t ibit = 8;

    _SDA1;
    while (ibit--)
    {
        data = data << 1;
        _SCL0;
        _DELAY;
        _SCL1;
        _DELAY;
        if (_SDAX)
            data = data | 0x01;
    }
    _SCL0;

    return data;
}

void i2c_set_ack(uint8_t ack)
{
    _SCL0;

    if (ack)
        _SDA0;
    else
        _SDA1;

    _DELAY;

    _SCL1;
    _DELAY;
    _SCL0;
    _DELAY;

    _SDA1;
}
