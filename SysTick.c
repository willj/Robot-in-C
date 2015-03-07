#include "SysTick.h"

void initSysTick(void){
  NVIC_ST_CTRL_R = 0;               // disable SysTick during setup
  NVIC_ST_CTRL_R = 0x00000005;      // enable SysTick with core clock
}

// The delay parameter is in units of the 80 MHz core clock. (12.5 ns)
void sysTickWait(unsigned long delay){
  NVIC_ST_RELOAD_R = delay-1;  // number of counts to wait
  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
  }
}
// 80000*12.5ns equals 1ms
void sysTickWaitMilliseconds(unsigned long delay){
  unsigned long i;
  for(i=0; i<delay; i++){
    sysTickWait(80000);  // wait 1ms
  }
}

// 80*12.5ns equals 1microsecond
void sysTickWaitMicroseconds(unsigned long delay){
  unsigned long i;
  for(i=0; i<delay; i++){
    sysTickWait(80);  // wait 1ms
  }
}
