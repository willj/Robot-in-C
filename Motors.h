
#define SYSCTL_RCGC0_R          (*((volatile unsigned long *)0x400FE100))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCC_R            (*((volatile unsigned long *)0x400FE060))

// PORT B
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))

// PWM config

#define SYSCTL_RCGCPWM_R        (*((volatile unsigned long *)0x400FE640))
#define PWM0_CTL_R              (*((volatile unsigned long *)0x40028040))
#define PWM0_GENA_R             (*((volatile unsigned long *)0x40028060))
#define PWM0_GENB_R             (*((volatile unsigned long *)0x40028064))
#define PWM0_LOAD_R             (*((volatile unsigned long *)0x40028050))
#define PWM0_CMPA_R             (*((volatile unsigned long *)0x40028058))
#define PWM0_CMPB_R             (*((volatile unsigned long *)0x4002805C))
#define PWM_ENABLE_R            (*((volatile unsigned long *)0x40028008))

void initMotors (void);
void leftMotor (unsigned char state);
void rightMotor (unsigned char state);
