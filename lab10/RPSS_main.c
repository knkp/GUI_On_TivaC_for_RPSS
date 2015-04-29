#include "RPSS_System.h"



// set state machine to defatul state
RPSS_States state = DEFAULT;

int main(void){
	// initiaze system, including uart and kentec display drivers
	RPSS_System_init();

	while(1){
		// start the state machine and let it run for the lifetime of uptime
		state = RPSS_Handler(state);
	}
}
