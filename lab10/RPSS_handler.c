#include "RPSS_System.h"

RPSS_States RPSS_Handler(RPSS_States state){
	switch(state){
		case GOT_NEW_PATRON:
			state = update_peripheral_controller(GOT_NEW_PATRON);
			break;
		case IN_DATABASE: // if they are in the database, they need to be tested and have there stuff returned, or not
			state = update_peripheral_controller(IN_DATABASE);
			break;
		case NOT_IN_DATABASE:  // if they are not in the database, thi sis a new user, register them
			state = update_peripheral_controller(NOT_IN_DATABASE);
			break;
		case BREATHALYZER_PASS:
			state = update_peripheral_controller(BREATHALYZER_PASS);
			break;
		case BREATHALYZER_FAIL:
			display_waiting_time();
			state = update_peripheral_controller(BREATHALYZER_FAIL);
			break;
		case DEFAULT:
			display_intro();
			state = update_peripheral_controller(DEFAULT);
			break;
		case OUTRO:
			display_outro();
			state = DEFAULT;
			break;
		case MAINTENANCE:
			break;
		case ERROR:
			break;
		default :
			break;
	}

	return state;
}
