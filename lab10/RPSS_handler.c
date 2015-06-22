#include "RPSS_System.h"


RPSS_States RPSS_Handler(RPSS_States state){
	switch(state){
		case GOT_NEW_PATRON:
			display_welcome();
			state = update_peripheral_controller(GOT_NEW_PATRON);
			break;
		case IN_DATABASE: // if they are in the database, they need to be tested and have there stuff returned, or not
			display_database_check();
			state = update_peripheral_controller(IN_DATABASE);
			break;
		case NOT_IN_DATABASE:  // if they are not in the database, this is a new user, register them
			display_registration();
			state = update_peripheral_controller(NOT_IN_DATABASE);
			break;
		case BREATHALYZER_PASS:
			display_release_items();
			state = update_peripheral_controller(BREATHALYZER_PASS);
			break;
		case BREATHALYZER_FAIL:
			display_waiting_time();
			state = update_peripheral_controller(BREATHALYZER_FAIL);
			break;
		case DEFAULT:
			display_get_ID();
			//display_intro();
			//state = update_peripheral_controller(DEFAULT);
			state = DEFAULT;
			break;
		case OUTRO:
			display_outro();
			state = DEFAULT;
			break;
		case WIND_THRESHOLD_NOT_REACHED:
			display_failed_to_get_breath();
			state = OUTRO;
			break;
		case MAINTENANCE:
			display_maintenance_mode();
			state = update_peripheral_controller(MAINTENANCE); // wait for command to leave maintenance mode
			break;
		default:  // error state
			display_error_state();
			state = update_peripheral_controller(ERROR); // wait for command to leave error mode
	}

	return state;
}
