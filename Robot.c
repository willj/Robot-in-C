#include "Robot.h"

/**********************************************************************
 *		Port of EE40LX Robot code to C for TM4C123GXL
 *********************************************************************/

int main (void){
	
	initSysTick();
	initPorts();
	initMic();
	initMotors();
		
	while (1){
		unsigned short i;
		unsigned short maxval = 0;
		unsigned short val = 0;
		
		// turn off both motors
		leftMotor(0);
		rightMotor(0);
		
		// Step 1: beep a bunch of times!
		
		for (i=1; i<5; i++)
		{
			beep(1000, 100*i);
			delayMilliseconds(100*i);
		}
		
		// Step 2: listen to the microphone for ~100 ms
    
		for (i=1; i<100; i++){
			val = readMic();
			if (val > maxval){
				maxval = val;
			}
			delayMilliseconds(1);
		}
		
		if (maxval > MICTHRESH) {
			
			// Make the "siren" noise by alternating 1200 Hz and 800 Hz tones
			for (i=0; i<5; i++)
			{
					beep(1200, 100);
					beep(800,  100);
			}
			
			// Shake motors back and forth rapidly
			for (i=0; i<3; i++)
			{
					rightMotor(1);
					delayMilliseconds(200);
					rightMotor(0);
					leftMotor(1);
					delayMilliseconds(200);
					leftMotor(0);
			}
			// Make a series of tones with increasing frequency from 300-100 Hz
			// then come back down
			for (i=30; i<100; i+=1){
				beep(10*i, 10);
			}
			
			for (i=100; i>30; i-=1){
				beep(10*i, 10);
			}
		}
		
		// Step 3: read the status of photocells and adjust motor output
		
		PBLOCK = 0x02;                 // Turn on the powerblock to photocells & amp
		delayMicroseconds(20);         // delay for the circuit to settle
		
		if (LPHOTO){
			leftMotor(1);
		}
		
		if (RPHOTO){
			rightMotor(1);
		}
		
		PBLOCK = 0x00;                 // Turn off the power
		
		delayMilliseconds(500);
	}
}

//generate a square wave at a given frequency for ms miliseconds
void beep (unsigned short freq, unsigned long ms) {
	unsigned long k;
	unsigned long semiper = (long) (1000000/(freq*2));
	unsigned long loops = (long)((ms*1000)/(semiper*2));
	
	for (k=0;k<loops;k++)
	{
		BUZZER = 0x01; //set buzzer pin high
		delayMicroseconds(semiper);     //for half of the period
		
		BUZZER = 0x00;	//set buzzer pin low
		delayMicroseconds(semiper);    //for the other half of the period
	}
}

void initPorts (void){
	volatile unsigned long delay;

	SYSCTL_RCGC2_R |= 0x14;          // Turn on the clock for Ports C,E (00010100 or 20 or 0x14)
	delay = SYSCTL_RCGC2_R;          // This causes a delay to allow the clock to start
		
	// Port E
	// PE0 for Buzzer - Digital Out.
	// PE1 for Power Block - Digital Out.
	// PE4 for left photo sensor - Digital In
	// PE5 for left photo sensor - Digital In
	
	GPIO_PORTE_AMSEL_R &= 0x00;     // Disable analog on Port E (all 8 bits)
	GPIO_PORTE_PCTL_R &= 0x00;      // Same again to config as GPIO
	GPIO_PORTE_DIR_R |= 0x03;       // Set PE0, PE1 as outputs
	GPIO_PORTE_DIR_R &= ~0x30;      // Clear PE4, PE5 for use as inputs
	GPIO_PORTE_AFSEL_R &= ~0x33;    // Clear Alt functions in PE0,1,4,5
	GPIO_PORTE_DEN_R |= 0x33;       // SET to enable Digital on PE0,1,4,5
	
}
