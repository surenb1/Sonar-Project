#include "TM4C123GH6PM.h"
#include "UART0.h"

/**
 * @file UART0.c
 *
 * @brief Source code for the UART0 driver.
 *
 * This file contains the function definitions for the UART0 driver.
 *
 * @note For more information regarding the UART module, refer to the
 * Universal Asynchronous Receivers / Transmitters (UARTs) section
 * of the TM4C123GH6PM Microcontroller Datasheet.
 *   - Link: https://www.ti.com/lit/gpn/TM4C123GH6PM
 *
 * @note Assumes that the frequency of the system clock is 50 MHz.
 *
 * @author Suren Bursalyan
 */

void UART0_Init(void)
{
// Enable the clock to the UART0 module by setting the R0 bit (Bit 0)
// in the RCGCGPIO register
SYSCTL->RCGCUART |= 0x01;

// Enable the clock to port Aa by setting the R0 bit (Bit 0)
// in the RCGCGPIO  register
SYSCTL -> RCGCGPIO |= 0x01;

// Disable the UART0 module before configuration by clearing the UARTEN
// bit (bit 0) in the CTL register
UART0->CTL &= ~0x01;

//Configure the UART0 module to use the system clock (50 MHz)
// divided by 16 by clearing the HSE bit (bit 5) in the CTL register
UART0->CTL &= ~0x20;

//Set the baus rate by writing the DIVINT field (bits 15 to 0)
// and the DIVFRAC field (Bits 5 to 0) in the IBRD and FBRD registers, respectively.
//The integer part of the calculated constant will be written to the IBRD register,
// while the fractional part will be written to the FBRD register.
// BRD = (System Clock Frequency) / ( 16 * baud rate)
// BRDI = (50,000,000) / (16 * 115200) = 27.12673611 (IBRD = 27)
//BRDF = ((0.12673611 * 64) + 0.5) = 8.611 (FBRD = 8)
UART0->IBRD = 27;
UART0->FBRD = 8;

// configure the data length of the UART packet to be 8 bits by writing the value of
//0x03 to the WLEN field (bits 6 to 5) in the LCRH register
UART0->LCRH |= 0x60;

// enable the Transmit FIFO and the recieve FIFO by settinf the FEN bit (Bit 4) in
// the LCRH register
UART0->LCRH |= 0x10;

//select on stop bit to be transmitted at the end of a UART frame by clearung
// the STP2 bit (bit 3) in the LCRH register
UART0->LCRH &= ~0x08;

//Disable the parity bit by clearing the PEN bit (Bit 1) in the LCRH register
UART0->LCRH &= ~ 0x02;

//enable the UART0 module after configuration by setting the UARTEN bit (bit 0)
// in the CTL register
UART0->CTL |= 0x01;

// select the alternate funtion for the PA1 and PA0 pins by setting Bits 1 to 0
// in the AFSEL register. the pins will be configured as RX and TX pins
GPIOA->AFSEL |= 0x03;

//Clear the PMC1 (Bits 7 to 4) and PMC0 (Bit 3 to 0) fields in the PCTL register
//for Port A before configuration
GPIOA->PCTL &= ~0xFF;

//Configure the PA1 pin to operate as a U0TX pin by writing 0x01 to the PMC1 field
//(bit 7 to 4) in the PCTL register
GPIOA->PCTL |= 0x10;

//Configure the PA0 pin to operate as a U0RX pin by writing 0x1 to the PMC0 field
//(Bits 3 to 0) in the PCTL register
GPIOA->PCTL |=0x01;

//Enable the digital functionality for the PA1 and PA0 pins by setting Bits 1 and 0
//in the DEN register
GPIOA->DEN |= 0x03;
}


// The UART0_Output_Character function will wait until the UART transmit buffer is ready to accept a new
// character and then write the specified character in the transmit buffer. The TXFF bit (Bit 5) of the UART
// Flag Register (FR) is used to check if the UART transmit buffer is full. This function will be used to
// output a character to the serial terminal using the Data Register (DR)...
void UART0_Output_Character(char data)
{
	while((UART0->FR & UART0_TRANSMIT_FIFO_FULL_BIT_MASK) != 0);
	
	UART0->DR = data;
}


// A set of characters can be transmitted using the UART0_Output_String function.
// The function will be used to transmit characters from the provided string (pt) until
// a null character is encountered...
void UART0_Output_String(char *pt)
{
	while(*pt)
	{
		UART0_Output_Character(*pt);
		pt++;
	}
}


// The UART0_Output_Unsigned_Decimal function will output an unsigned decimal integer as
// an ASCII string from the most significant to least significant digit, converting each
// digit individually. If the number 'n' is greater than or equal to 10, the function
// recursively calls itself with (n/10). The recursive call reduces 'n' by removing the 
// least significant digit each time until only the most significant digit is left.
// Then, 'n' is set to (n%10) to isolate the current least significant digit.
// If 'n' is less than 10, the function will not perform a recursive loop since 'n'
// is guaranteed to be a signle digit (0-9). The UART0_Output_Character function is
// called with the value (n + '0'). Adding zero converts the integer digit 'n' to its
// ASCII character equivalent...
void UART0_Output_Unsigned_Decimal(uint32_t n)
{
	// Use recursion to convert decimal number
	// of unspecified length as an ASCII string
	if (n >= 10)
	{
		UART0_Output_Unsigned_Decimal(n / 10);
		n = n % 10;
	}
	
	// n is between 0 and 9
	UART0_Output_Character(n + '0');
}


// Lastly, the UART0_Output_Newline function can be used to output a newline by
// transmitting the carriage return (CR) and line feed (LF) characters...
void UART0_Output_Newline(void)
{
	UART0_Output_Character(UART0_CR);
	UART0_Output_Character(UART0_LF);
}

void UART0_PrintAngle(uint8_t angle, uint32_t distance)
{
	UART0_Output_Unsigned_Decimal(angle);
	UART0_Output_Character(',');
	UART0_Output_Unsigned_Decimal(distance);
	UART0_Output_Newline();
}
