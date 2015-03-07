// SysTick timer

#define NVIC_ST_CTRL_R      (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R    (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R   (*((volatile unsigned long *)0xE000E018))

void initSysTick(void);
void sysTickWait(unsigned long delay);
void sysTickWaitMicroseconds(unsigned long delay);
void sysTickWaitMilliseconds(unsigned long delay);
