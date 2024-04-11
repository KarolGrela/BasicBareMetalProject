/**
 * @file        
 * @author      
 * @copyright
 */

/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include "TimerOverflow_t.h"

/******************************************************************************
 * DEFINES
 *****************************************************************************/


/******************************************************************************
 * GLOBAL VARIABLES
 *****************************************************************************/
TimerOverflow_t tov_led;
TimerOverflow_t tov_left_button;
TimerOverflow_t tov_right_button;

/******************************************************************************
 * PRIVATE TYPES
 *****************************************************************************/


/******************************************************************************
 * PRIVATE FUNCTION DECLARATIONS
 *****************************************************************************/


/******************************************************************************
 * STATIC VARIABLES
 *****************************************************************************/


/******************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 *****************************************************************************/
// constructor
TimerOverflow_t* tov_Constructor(TimerOverflow_t* tov, uint32_t max_overflow_value)
{
	tov->overflow_counter = 0;
	tov->overflow_count_trigger = max_overflow_value;
	tov->overflow_flag = false;
	tov_deactivateOverflowTimer(tov);

	return tov;
}

// activate/deactivate OverflowTimer
void tov_activateOverflowTimer(TimerOverflow_t* tov)
{
	tov->active = true;
}
void tov_deactivateOverflowTimer(TimerOverflow_t* tov)
{
	tov->active = false;
}
bool tov_getActive(TimerOverflow_t tov)
{
	return tov.active;
}


// overflow_flag methods
bool tov_getOverflowFlag(TimerOverflow_t* tov)
{
	// get overflow_flag value
	bool overflow_flag_value = tov->overflow_flag;
	// reset overflow_flag if it's set to true
	if (tov->overflow_flag == true)
	{
		tov->overflow_flag = false;
	}
	// return old value of overflow_flag
	return overflow_flag_value;
}
void tov_setOverflowFlag(TimerOverflow_t* tov, bool new_value)
{
	tov->overflow_flag = new_value;
}

// overflow_counter methods
void tov_incrementOverflowCounter(TimerOverflow_t* tov)
{
	// increment overflow counter value
	tov->overflow_counter += 1;
	// check if counter overflows
	if (tov->overflow_counter >= tov->overflow_count_trigger)
	{
		tov_setOverflowFlag(tov, true);
		tov->overflow_counter = 0;
	}
}

// max_overflow_counter methods
void tov_setOverflowCountTrigger(TimerOverflow_t* tov, uint32_t new_value)
{
	tov->overflow_count_trigger = new_value;
}

// reset TimerOverflow_t instance
void tov_resetTimerOverflowInstance(TimerOverflow_t* tov)
{
	tov->overflow_counter = 0;
	tov->overflow_flag = false;
}

/******************************************************************************
 * PRIVATE FUNCTION DEFINITIONS
 *****************************************************************************/

