#include "Motors.h"
#include <stdint.h>
#include "SysTick.h"

/*********************************************************************************
 *	Initialize two PWM modules on:
 *	M0PWM0 = PB6 = Left motor
 *	M0PWM1 = PB7 = Right Motor
 *	This is used to reduce the voltage, with a 50% duty cycle (on 50%, off 50%)
 *	we get around 50% of 3.3v as the output, or 1.65v
 ********************************************************************************/

#define MOTOR_PERIOD 19999         // number of clock ticks per period
#define LOW_DUTY 19995             // amount of period to get output low (0v)
#define HIGH_DUTY 9999             // amount of period to get output high (1.65v)

void initMotors (void){
	
	volatile unsigned long delay;

	SYSCTL_RCGC0_R |= 0x00100000;         // Enable PWM clock
	delay = SYSCTL_RCGC0_R;

	SYSCTL_RCGC2_R |= 0x02;               // Turn on the clock for Port B 
	delay = SYSCTL_RCGC2_R;		      

	// we need more of a delay waiting for Port B
	delayMilliseconds(10);
	
	GPIO_PORTB_AFSEL_R |= 0xC0;           // Enable the alt function for PB6/7
	GPIO_PORTB_DEN_R |= 0xC0;             // Enable digital on PB6/7
	GPIO_PORTB_AMSEL_R &= 0x00;           // Disable analog function on all PB pins
	GPIO_PORTB_PCTL_R |= 0x44000000;      // Set Port control to select PWM as the Alt function
	
	// Divide the 80MHz system clock by 8 to get 10MHz PWM clock
	// Set the period to 20,000. so 10,000,000 / 20,000 = 500Hz wave period, which is just above the Energia frequency.
	
	SYSCTL_RCC_R |= 0x00100000;           // Enable PWM clock divisor
	SYSCTL_RCC_R &= ~0x000C0000;          // Set to /8 divider
	
	PWM0_CTL_R = 0x00000000;              // Configure the PWM generator for countdown mode with immediate updates to the parameters.
	PWM0_GENA_R = 0x0000008C;             // High on load, low on comparator A down
	PWM0_GENB_R = 0x0000080C;             // High on load, low on comparator B down
	
	PWM0_LOAD_R = MOTOR_PERIOD;           // This is the period (20000 - 1), number of clock ticks per period
	
	// How much of the period the output will remain low. 
	// When it's running for these motors we want 50% (10000)
	// But set to 100% for init
	// Setting this to match the period seems to result in a full 3.3v output, but just below gives 0v as expected
	PWM0_CMPA_R = LOW_DUTY;
	PWM0_CMPB_R = LOW_DUTY;
	
	PWM0_CTL_R = 0x00000001;              // Enable PWM
	PWM_ENABLE_R |= 0x00000003;           // Enable PWM Outputs on M0PWM0 (PB6) + M0PWM1 (PB7)
	
}

// switch left motor state, 0 = off, 1 = on

void leftMotor (unsigned char state){
	if (state == 1) {
		PWM0_CMPA_R = HIGH_DUTY;
	} else {
		PWM0_CMPA_R = LOW_DUTY;		
	}
}

void rightMotor (unsigned char state){
	if (state == 1) {
		PWM0_CMPB_R = HIGH_DUTY;
	} else {
		PWM0_CMPB_R = LOW_DUTY;		
	}
}
