#include "RPSS_System.h"

RPSS_States RPSS_Handler(RPSS_States state){
	switch(state){
		case GOT_NEW_PATRON:
			break;
		case IN_DATABASE:
			break;
		case NOT_IN_DATABASE:
			break;
		case REGISTER:
			break;
		case CHECK_BREATHALZYER:
			break;
		case BREATHALYZER_PASS:
			break;
		case BREATHALYZER_FAIL:
			break;
		case DEFAULT:
			display_intro();
			state = DEFAULT;
			break;
		case MAINTENANCE:
			break;
		default :
			break;
	}

	return state;
}
