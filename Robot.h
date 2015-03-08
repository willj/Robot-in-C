#include "TM4C123GH6PM.h"
#include "SysTick.h"
#include "Mic.h"

/* */
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// PORT C
#define GPIO_PORTC_DATA_R       (*((volatile unsigned long *)0x400063FC))
#define GPIO_PORTC_DIR_R        (*((volatile unsigned long *)0x40006400))
#define GPIO_PORTC_AFSEL_R      (*((volatile unsigned long *)0x40006420))
#define GPIO_PORTC_DEN_R        (*((volatile unsigned long *)0x4000651C))
#define GPIO_PORTC_AMSEL_R      (*((volatile unsigned long *)0x40006528))
#define GPIO_PORTC_PCTL_R       (*((volatile unsigned long *)0x4000652C))

// PORT E
//#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))

//#define PBLOCK  GPIO_PORTE_DATA_R &0x02 //PE_1
#define BUZZER 									(*((volatile unsigned long *)0x40024004)) //PE_0
//#define LMOTOR  PC_6
//#define RMOTOR  PC_7
//#define LPHOTO  PE_4
//#define RPHOTO  PE_5

#define MICTHRESH 2400 // set microphone trigger threshold (possible values 0-4096)

void initPorts (void);
void beep (unsigned short freq, unsigned long ms);
