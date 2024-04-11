/**
 * @file      
 * @author    
 * @copyright 
 * @date      
 *
 * @brief     
 */
 #ifndef BUTTON_PRESS_T_H
 #define BUTTON_PRESS_T_H

/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include <stdint.h>
#include <stdbool.h>

#include "TimerOverflow_t.h"

/******************************************************************************
 * PUBLIC TYPES
 *****************************************************************************/
typedef struct{
	bool button_is_pressed;					/*< true if button is pressed */
	uint32_t min_overflow_trigger_count;
	uint32_t max_overflow_trigger_count;
	TimerOverflow_t* source_tov;			/*<  */
	TimerOverflow_t* target_tov;
}ButtonPress_t;


/******************************************************************************
 * EXPORTED GLOBAL VARIABLES
 *****************************************************************************/
extern ButtonPress_t btp_left;
extern ButtonPress_t btp_right;

/******************************************************************************
 * PUBLIC MACROS
 *****************************************************************************/

/******************************************************************************
 * PUBLIC FUNCTION DECLARATIONS
 *****************************************************************************/
void btp_Constructor(ButtonPress_t* btp, uint32_t min, uint32_t max,
		TimerOverflow_t* source_tov, TimerOverflow_t* target_tov);

void btp_press(ButtonPress_t* btp);

void btp_release(ButtonPress_t* btp);

void btp_incr_overflow_trigger_count(ButtonPress_t* btp, uint8_t delta);

void btp_decr_overflow_trigger_count(ButtonPress_t* btp, uint8_t delta);

#endif
