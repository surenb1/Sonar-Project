#include "TM4C123GH6PM.h"
#include <stdint.h>
#include "PWM.h"

// Generate PWM signal on PF2 pin...
void PWM_Init(uint16_t period_constant, uint16_t duty_cycle)
{
	if (duty_cycle >= period_constant) return;
	
	SYSCTL->RCGCPWM |= 0x02;
	
	SYSCTL->RCGCGPIO |= 0x20;
	
	GPIOF->AFSEL |= 0X04;
	
	GPIOF->PCTL &= ~0x00000F00;
	
	GPIOF->PCTL |= 0x00000500;
	
	GPIOF->DEN |= 0x04;
	
	PWM1->_3_CTL &= ~0x01;
	
	PWM1->_3_CTL &= ~0x02;
	
	PWM1->_3_GENA |= 0xC0;
	
	PWM1->_3_GENA |= 0X08;
	
	PWM1->_3_LOAD = (period_constant - 1);
	
	PWM1->_3_CMPA = (duty_cycle - 1);
	
	PWM1->_3_CTL |= 0x01;
	
	PWM1->ENABLE |= 0x40;
}

// Configure PWM clock frequency to be 3.125 MHz...
void PWM_Clock_Init(void)
{
	SYSCTL->RCC |= 0x00100000;
	
	SYSCTL->RCC &= ~0x000E0000;
	
	SYSCTL->RCC |= 0x00060000;
}

void PWM_Update_Duty_Cycle(uint16_t duty_cycle)
{
	// Set the duty cycle by writing to the COMPA field (Bits 15 to 0)
	// in the PWM3CMPA register. When the counter matches the value in this register,
	// the PWM signal will be driven high
	PWM1->_3_CMPA = (duty_cycle - 1);
}