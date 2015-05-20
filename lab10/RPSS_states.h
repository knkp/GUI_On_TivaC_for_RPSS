typedef enum {
	GOT_NEW_PATRON,
	IN_DATABASE,
	NOT_IN_DATABASE,
	REGISTER,            // arduino will do most of the work in this case as the peripheral controller go back to default state after return successful
	BREATHALYZER_PASS,
	BREATHALYZER_FAIL,
	WIND_THRESHOLD_NOT_REACHED,
	OUTRO,
	DEFAULT,
	MAINTENANCE,
	ERROR
} RPSS_States;
