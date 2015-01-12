#ifndef _i2c_conf_h
#define _i2c_conf_h

#include <stm32f4xx_gpio.h>
#include <stm32f4xx_i2c.h>

void init_I2C1(void);

#define I2C_SDA GPIO_Pin_9
#define I2C_SCL GPIO_Pin_8

#endif
