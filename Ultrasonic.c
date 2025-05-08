/**
 * @file Ultrasonic.c
 * @brief Ultrasonic sensor driver using Timer Capture on TM4C123GH6PM.
 */
#include "TM4C123GH6PM.h"
#include "Ultrasonic.h"
#include "SysTick_Delay.h"

#define TRIG_PIN (1 << 2) // PA2
#define ECHO_PIN (1 << 3) // PA3

void Ultrasonic_Init(void)
{
	SYSCTL->RCGCGPIO |= 0x01;	// ENABLE CLOCK TO PORT A
	GPIOA->DIR |= TRIG_PIN;		// SET PA2 (TRIGGER PIN) AS OUTPUT
	GPIOA->DEN |= TRIG_PIN;		// ENABLE DIGITAL FUNCTIONALITY OF PA2
	GPIOA->DATA &= ~TRIG_PIN;	// ENSURE TRIGGER PIN STARTS LOW
	
	GPIOA->DIR &= ~ECHO_PIN;	// SET PA3 (ECHO) AS INPUT
	GPIOA->DEN |= ECHO_PIN;		// ENABLE DIGITAL FUNCTIONALITY OF PA3
	
}

uint32_t Ultrasonic_Read_Distance(void)
{
	uint32_t time = 0;				// INITIALIZE VARIABLE 'time' FOR LATER USE
	
	GPIOA->DATA |= TRIG_PIN;	// SET TRIGGER PIN HIGH
	SysTick_Delay1us(10);			// WAIT 10 us
	GPIOA->DATA &= ~TRIG_PIN;	// SET TRIGGER PIN BACK DOWN TO LOW
	
	while ((GPIOA->DATA & ECHO_PIN) == 0)
	{
		time++;
		SysTick_Delay1us(1);
		if (time > 5000)
		{
			return 100;
		}
	}
	
	while ((GPIOA->DATA & ECHO_PIN) != 0)
	{
		time++;
		SysTick_Delay1us(1);
	}
	
	uint32_t distance_cm = time / 58;
	
	return distance_cm;
}
