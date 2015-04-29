#include "RPSS_System.h"

void RPSS_System_init(void){
	// initialize the system
	init_clock(); // MUST call this first
	init_display();
	init_uart();
}

void init_clock(void){
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
}
