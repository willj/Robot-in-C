#include "Robot.h"

/**********************************************************************
 *		Port of EE40LX Robot code to C for TM4C123GXL
 *********************************************************************/

int main (void){
	
	initSysTick();
	initPorts();
	initMic();
		
	while (1){
		unsigned short i;
		unsigned short maxval = 0;
		unsigned short val = 0;
		
		// Step 1: beep a bunch of times!
		
		for (i=1; i<5; i++)
		{
			beep(1000, 100*i);
			sysTickWaitMilliseconds(100*i);
		}
		
		// Step 2: listen to the microphone for ~100 ms

		for (i=1; i<100; i++){
			val = readMic();
			if (val > maxval){
				maxval = val;
			}
			sysTickWaitMilliseconds(1);
		}
		
		if (maxval > MICTHRESH) {
			// temporary beeps...
			beep(1000, 100);
			sysTickWaitMilliseconds(100);
			beep(1000, 100);
			sysTickWaitMilliseconds(100);
			beep(1000, 100);
		}
	}
}

//generate a square wave at a given frequency for ms miliseconds
void beep (unsigned short freq, unsigned long ms) {
	unsigned long k;
	unsigned long semiper = (long) (1000000/(freq*2));
	unsigned long loops = (long)((ms*1000)/(semiper*2));
	for (k=0;k<loops;k++)
	{
		BUZZER = 1; //set buzzer pin high
		sysTickWaitMicroseconds(semiper); //for half of the period
		
		BUZZER = 0;	//set buzzer pin low
		sysTickWaitMicroseconds(semiper); //for the other half of the period
	}
}

void initPorts (void){
	volatile unsigned long delay;

	SYSCTL_RCGC2_R |= 0x14;		// Turn on the clock for Ports C,E (00010100 or 20 or 0x14)
	delay = SYSCTL_RCGC2_R;		// This causes a delay to allow the clock to start
		
	// Port E
	// PE0 for Buzzer - Digital Out.
	// PE1 for Power Block - Digital Out.
	
	GPIO_PORTE_AMSEL_R &= 0x00;			// Disable analog on Port E (all 8 bits)
	GPIO_PORTE_PCTL_R &= 0x00; 			// Same again to config as GPIO
	GPIO_PORTE_DIR_R |= 0x03; 			// Set for PE0, PE1 as outputs
	GPIO_PORTE_AFSEL_R &= ~0x03;	// Clear Alt functions in PE0,1
	GPIO_PORTE_DEN_R |= 0x03; 			// SET to enable Digital on PE0,1
	
}
