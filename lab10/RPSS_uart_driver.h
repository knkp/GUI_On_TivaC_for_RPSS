#ifndef RPSS_uart_driver_h
#define RPSS_uart_driver_h


#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"


/*
 *  Transmission Characters, what they are and what they mean
 *  ---- Stephen Copeland 4/28/2015
 */

#define CHECK_DATABASE 'a'
#define REGISTER_PATRON 'b'
#define USER_NOT_IN_DATABASE 'c'
#define USER_IN_DATABASE 'h'
#define CHECK_BREATHALYZER 'd'
#define BREATHALYZER_TEST_PASS 'e'
#define BREATHALYZER_TEST_FAIL 'f'
#define MAINTENANCE_MODE 'g'
#define PATRON_REGISTERED_SUCCESSFULLY 'i'
#define RELEASE_PATRON 'j'
#define RELEASED 'k'
#define TAXI_DEPLOYED 'l'
#define DEFAULT_STATUS 'm'
#define DEFAULT_ACK 'n'
#define WIND_NOT_REACHED 'p'
#define ERROR_STATE 'o'


/*
 * Function declarations, open references for description:
 * --- Stephen Copeland 4/28/2015
 */


void init_uart(void);
RPSS_States update_peripheral_controller(RPSS_States);
char uart_transceiver(char);

#endif
