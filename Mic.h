
#define SYSCTL_RCGC0_R          (*((volatile unsigned long *)0x400FE100))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// PORT D
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))

// ADC registers
#define ADC0_SSPRI_R 						(*((volatile unsigned long *)0x40038020))
#define ADC0_ACTSS_R 						(*((volatile unsigned long *)0x40038000))
#define ADC0_EMUX_R 						(*((volatile unsigned long *)0x40038014))
#define ADC0_SSMUX3_R 					(*((volatile unsigned long *)0x400380A0))
#define ADC0_SSCTL3_R 					(*((volatile unsigned long *)0x400380A4))

#define ADC0_PSSI_R  						(*((volatile unsigned long *)0x40038028))		
#define ADC0_RIS_R 							(*((volatile unsigned long *)0x40038004))	
#define ADC0_SSFIFO3_R					(*((volatile unsigned long *)0x400380A8))
#define ADC0_ISC_R							(*((volatile unsigned long *)0x4003800C))

void initMic (void);
unsigned long readMic (void);
