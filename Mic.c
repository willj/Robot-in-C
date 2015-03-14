#include "Mic.h"

/*********************************************************************************
 *	Initialize the mic on Analog In 5 (PD2), using sequencer 3.
 *
 ********************************************************************************/

void initMic (void) {
	volatile unsigned long delay;
	
	SYSCTL_RCGC2_R |= 0x08;            // Turn on the clock for Port D (00001000 or 8 or 0x08)
	delay = SYSCTL_RCGC2_R;            // This causes a delay to allow the clock to start
	
	// Port D
	// PD2 as Analog In 5
	GPIO_PORTD_DIR_R &= ~0x03;         // Make PD2 input
	GPIO_PORTD_AFSEL_R |= 0x03;        // Enable the alt function for PD2
	GPIO_PORTD_DEN_R &= ~0x03;         // Disable digital on PD2
	GPIO_PORTD_AMSEL_R |= 0x03;        // Enable analog function on PD2
	
	SYSCTL_RCGC0_R |= 0x00010000;      // Activate ADC0
	delay = SYSCTL_RCGC0_R;		
	SYSCTL_RCGC0_R &= ~0x00000300;     // Configure for max 125k samples/sec
	ADC0_SSPRI_R = 0x0123;             // set sequencer 3 to highest priority, and make sure the others are unique
	ADC0_ACTSS_R &= ~0x0008;           // Disable sequencer 3 during setup
	ADC0_EMUX_R &= ~0xF000;            // Set it for software trigger (the software will ask for the value from input)
	ADC0_SSMUX3_R &= ~0x000F;          // Clear the SS3 field
	ADC0_SSMUX3_R += 5;                // Set the channel to AIN5 (PD2)
	ADC0_SSCTL3_R = 0x0006;            // Clear TS0 (temperature sensor) to 0, IE0 to 1 (set a flag when data sample is complete/ready)
                                     // set END0 to 1 because this is the last/only sample in sequence
                                     // bit 0 is D0 which is cleared because we don't want differential mode
	ADC0_ACTSS_R |= 0x0008;            // Finally, enable sequencer 3 again.
	
}

/*********************************************************************************
 *	Read the mic input, return val between 0 and 4095
 *
 ********************************************************************************/

unsigned long readMic (void) {  
	unsigned long result;
  ADC0_PSSI_R = 0x0008;               // Initiate Sequencer 3/tell it we want a sample
	
	// RIS (Raw Interrupt Status) bit 3 for Sequencer 3 
	// this will be a 0 whilst it is still collecting the 12 bits, but will flip to 1 when the sample is ready
	while((ADC0_RIS_R&0x08) == 0) {};	  // Mask RIS_R so we only get bit 3, wait for it to become a 1 (or not a 0)
	
	result = ADC0_SSFIFO3_R&0xFFF;      // read the result
	ADC0_ISC_R = 0x0008;                // set this which acknowledges you've read it and sets the RIS back to 0 for next sample
	
	return result;
}

