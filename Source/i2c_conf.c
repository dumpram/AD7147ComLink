#include "i2c_conf.h"

void init_I2C1() {
	I2C_InitTypeDef I2C_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/** Enable clocks **/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	
	/** Configure GPIO for I2C **/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD; 
	GPIO_InitStruct.GPIO_Pin = I2C_SCL | I2C_SDA;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
	
	/* initialize the I2C_ClockSpeed member */
  I2C_InitStruct.I2C_ClockSpeed = 100000;
  /* Initialize the I2C_Mode member */
  I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
  /* Initialize the I2C_DutyCycle member */
  I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
  /* Initialize the I2C_OwnAddress1 member */
  I2C_InitStruct.I2C_OwnAddress1 = 33;
  /* Initialize the I2C_Ack member */
  I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
  /* Initialize the I2C_AcknowledgedAddress member */
  I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1, &I2C_InitStruct);
	I2C_Cmd(I2C1, ENABLE);
}
