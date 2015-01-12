#include <stdio.h>
#include "i2c_conf.h"
#include "ad7147.h"
#include "usart.h"

int main() {
	int i, registerValue;
	char buffer[20];
	init_I2C1();
	init_USART1(9600);
	
	USART_puts(USART1, "Setup za AD7147. Trebalo bi ispisati prvih 100 registara!\r\n");
	for (i = 0; i < 100; i++) {
		registerValue = GetReg(i);
		sprintf(buffer, "Registar: %d Vrijednost registra: %d\r\n", i, registerValue);
		USART_puts(USART1, buffer);
	}
}
