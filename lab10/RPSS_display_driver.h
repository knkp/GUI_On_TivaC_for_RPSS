#ifndef RPSS_display_driver_h
#define RPSS_display_driver_h
#include "RPSS_System.h"

int init_display(void);
void wait_for_touch(void);
void display_intro(void);
void display_outro(void);
void display_release_items(void);
void display_waiting_time(void);
void display_welcome(void);
void display_release_items(void);
void display_database_check(void);
void display_registration(void);
void display_error_state(void);
void display_maintenance_mode(void);

#endif
