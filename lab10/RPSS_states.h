typedef enum {
	GOT_NEW_PATRON,
	IN_DATABASE,
	NOT_IN_DATABASE,
	REGISTER,            // arduino will do most of the work in this case as the peripheral controller go back to default state after return successful
	CHECK_BREATHALZYER,
	BREATHALYZER_PASS,
	BREATHALYZER_FAIL,
	DEFAULT,
	MAINTENANCE
} RPSS_States;