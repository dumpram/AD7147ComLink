#include <ad7147.h>
#include <stm32f4xx_spi.h>
#include <stm32f4xx_gpio.h>


unsigned short int GetReg(unsigned short int Addr)
{
		unsigned short int Ret_Value = 0x0000;
		uint8_t NumByteToRead = 2;
		uint8_t writeAddr = 0x58;
		uint8_t readAddr = 0x59;
	
		
			/* Wait while I2C line is busy */
		while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
		
			/* Generate start condition */
		I2C_GenerateSTART(I2C1, ENABLE);	
	
			/* Test on EV5 and clear it */
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
			/* Send address */
			/* 3 LSB
				 ADD0 --> 0
				 ADD1 --> 0
				 Write operation --> 0 */
		I2C_Send7bitAddress(I2C1, writeAddr ,I2C_Direction_Transmitter);
			
			/* Test on EV6 and clear it */
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
			/* Clear EV6 by setting again the PE bit */
		I2C_Cmd(I2C1, ENABLE);
			
			/* Send register address (MSB)*/
		I2C_SendData(I2C1, Addr>>8);
		
			/* Test on EV8 and clear it */
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
		
			/* Send register address (LSB)*/
		I2C_SendData(I2C1, Addr);
		
			/* Test on EV8 and clear it */
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
		
			/* Send STRAT condition a second time */
		I2C_GenerateSTART(I2C1, ENABLE);
		
			/* Test on EV5 and clear it */
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
			
			
			/* Send address */
			/* 3 LSB
				 ADD0 --> 0
				 ADD1 --> 0
				 Read operation --> 1 */
		I2C_Send7bitAddress(I2C1, readAddr, I2C_Direction_Receiver);
		
			/* Test on EV6 and clear it */
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
		
			/* Test on EV7 and clear it */
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
		
			/* Read a upper byte from the AD7147 */
		Ret_Value |= I2C_ReceiveData(I2C1);
		
			/* Shift upper byte left to make place for lower byte */
		Ret_Value = Ret_Value<<8;
		
			/* Disable Acknowledgement */
 		I2C_AcknowledgeConfig(I2C1, DISABLE);
		
		/* Test on EV7 and clear it */
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
		
		/* Read a lower byte from the AD7147 */
   	Ret_Value |= I2C_ReceiveData(I2C1);
		
			/* Disable Acknowledgement */
		I2C_AcknowledgeConfig(I2C1, DISABLE);
		
			/* Generate STOP Condition */
		I2C_GenerateSTOP(I2C1, ENABLE);   
				
			/* Enable Acknowledgement to be ready for another reception */
		I2C_AcknowledgeConfig(I2C1, ENABLE);
		
		return Ret_Value;
}


void SetReg (unsigned short int Addr, unsigned short int Data)
{
		uint8_t writeAddr = 0x58;
	
			/* Wait while I2C line is busy */
		while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
		
			/* Generate start condition */
		I2C_GenerateSTART(I2C1, ENABLE);	
	
			/* Test on EV5 and clear it */
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
		/* Send address */
			/* 3 LSB
				 ADD0 --> 0
				 ADD1 --> 0
				 Write operation --> 0 */
		I2C_Send7bitAddress(I2C1, writeAddr, I2C_Direction_Transmitter);
			
			/* Test on EV6 and clear it */
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
			/* Clear EV6 by setting again the PE bit */
		I2C_Cmd(I2C1, ENABLE);
			
			/* Send register address (MSB)*/
		I2C_SendData(I2C1, Addr>>8);
		
			/* Test on EV8 and clear it */
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
		
			/* Send register address (LSB)*/
		I2C_SendData(I2C1, Addr);
		
			/* Test on EV8 and clear it */
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
				
			/* Send the data to write in (MSB)*/
		I2C_SendData(I2C1, Data>>8);
	
			/* Test on EV8 and clear it */
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
		
			/* Send the data to write in (LSB) */
		I2C_SendData(I2C1, Data);
	
			/* Test on EV8 and clear it */
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
			
			/* Generate STOP Condition */
		I2C_GenerateSTOP(I2C1, ENABLE);
}

unsigned short int SPISend(unsigned short int Comm_Wrd, unsigned short int Data_Wrd)
{
	uint16_t Ret_Value;
 	int i;
	GPIOE->BSRRH = GPIO_Pin_7;
	//SPI_I2S_SendData(SPI1,Comm_Wrd);
 	SPI1->DR = Comm_Wrd;
	while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
	while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until receive complete
	while( SPI1->SR & SPI_I2S_FLAG_BSY ); // wait until SPI is not busy anymore
	
	for (i=0; i<50;i++);
	//SPI_I2S_SendData(SPI1,Data_Wrd);
	SPI1->DR = Data_Wrd;
	while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
	while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until receive complete
	while( SPI1->SR & SPI_I2S_FLAG_BSY ); // wait until SPI is not busy anymore
	Ret_Value = SPI1->DR; 
	for (i=0; i<50;i++);
	
	GPIOE->BSRRL = GPIO_Pin_7;
	return Ret_Value;
}





	

