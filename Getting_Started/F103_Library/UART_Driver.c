#include "UART_Driver.h"

void UART_init() 
{
	//USART 1 using clock speed 72Mhz, USART 2 and 3 using 36Mhz
	//USART3 -> PB10 (Tx) and PB11 (Rx)
	//USART2 -> PA2 (Tx) and PA3 (Rx)
	//USART1 -> PA9 (Tx) and PA10(Rx)

	// Enable USART2 clock
	RCC->APB1ENR |= (1 << 17);

  // Configure USART2 pins (TX = PA2, RX = PA3)
  RCC->APB2ENR |= (1 << 2); // Enable GPIOA clock
  GPIOA->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2 | GPIO_CRL_CNF3 | GPIO_CRL_MODE3);
  GPIOA->CRL |= (GPIO_CRL_CNF2_1 | GPIO_CRL_MODE2_1); // TX: AF, Push-Pull, 50 MHz
  GPIOA->CRL |= GPIO_CRL_CNF3_0; // RX: Floating input

  // Bu?c 3: Configure USART2
  USART2->CR1 &= ~(1 << 13); // turn offf USART2
  USART2->CR1 &= ~(1 << 12);  // 8-bit data
  USART2->CR2 &= ~((1 << 13)|(1 << 12)); // 1 stop bit
  USART2->CR1 &= ~(1 << 10);  // No parity control
  USART2->BRR = 0xEA6; // 9600 baud rate

	//step 4:  enable USART2
  USART2->CR1 |= (1 << 13);
  USART2->CR1 |= ((1 << 3) | (1 << 2)); // Transmitter and Receiver enable
	
}
char USART2_ReceiveChar(void) {
	char receive;
  while (!(USART2->SR & (1 << 5))); ///waite RXNE set
	receive = USART2->DR;
  return receive;
}


void USART2_SendChar(char data) {
    // Wait until the transmit buffer is empty
    while (!(USART2->SR & (1 << 7)));

    // Send the data
    USART2->DR = data;

    // Wait until TC=1 to ensure transmission of the last frame is complete
    while (!(USART2->SR & (1 << 6)));
}

void UART_SendString(char str[])
{
	int i = 0;
	while (str[i] != '\0')
	{
		USART2_SendChar(str[i]);
		i++;
	}
}


void USART2_ReceiveString(char* buffer, int bufferSize) {
    int i = 0;
	char received;
	
	//Read char until buffer is full or newline character is received
	do
	{
		received = USART2_ReceiveChar();
		buffer[i] = received;
		i++;
	}while (received != '\n' && i < bufferSize - 1);
	//set null is the last pos
	buffer[i] = '\0';
}


