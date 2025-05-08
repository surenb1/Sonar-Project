#include "TM4C123GH6PM.h"
#include "PWM.h"
#include "SysTick_Delay.h"
#include "Ultrasonic.h"
#include "UART0.h"
#include <stdint.h>

#define PERIOD_CONSTANT 62500

float angle;

float Duty_Cycle_to_Angle(uint32_t duty_cycle)
{
	return 0.0576f * (duty_cycle - 3125);
}

int main(void)
{
	// Initialize SysTick Timer...
	SysTick_Delay_Init();
	
	// Initialize Ultrasonic Sensor...
	// PA2 to TRIG (as output)
	// PA3 to ECHO (as input)
	Ultrasonic_Init();
	
	// Initialize UART0 communication at Baud Rate of 115200...
	// PA0 as Rx (Receiver)
	// PA1 as Tx (Transmitter)
	UART0_Init();
	
	// Initialize PWM clock to operate at 3.125 MHz...
	PWM_Clock_Init();
	
	// Initialize PWM signal...
	// Servo will start all the way to the left...
	PWM_Init(PERIOD_CONSTANT, 3125); // 1ms pulse corresponds with 3125 duty cycle (all the way to the left) <-- call this 0 degrees
	
	/*
	SysTick_Delay1ms(500);
	
	PWM_Update_Duty_Cycle(6250); // 2ms pulse corresponds with 6250 duty cycle (all the way to the right) <-- call this 180 degrees
	
	SysTick_Delay1ms(500);
	
	PWM_Update_Duty_Cycle(4688); // 1.5ms pulse corresponds with 4688 duty cycle (in the middle) <-- call this 90 degrees
	
	SysTick_Delay1ms(500);
	*/
	
	// How do i convert this to angle?
	while (1)
	{
		for (int i = 3125; i <= 6250; i+=40)
		{
			PWM_Update_Duty_Cycle(i);
			angle = Duty_Cycle_to_Angle(i);
			Ultrasonic_Read_Distance();
			UART0_PrintAngle((uint8_t)angle, Ultrasonic_Read_Distance());
			SysTick_Delay1ms(20);
		}
		
		for (int i = 6250; i >= 3125; i-=40)
		{
			PWM_Update_Duty_Cycle(i);
			angle = Duty_Cycle_to_Angle(i);
			Ultrasonic_Read_Distance();
			UART0_PrintAngle((uint8_t)angle, Ultrasonic_Read_Distance());
			SysTick_Delay1ms(20);
		}
	}
	
}