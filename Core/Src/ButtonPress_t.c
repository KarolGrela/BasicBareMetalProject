/**
 * @file        
 * @author      
 * @copyright
 */

/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include "ButtonPress_t.h"

/******************************************************************************
 * DEFINES
 *****************************************************************************/


/******************************************************************************
 * GLOBAL VARIABLES
 *****************************************************************************/
ButtonPress_t btp_left;
ButtonPress_t btp_right;

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
void btp_Constructor(ButtonPress_t* btp, uint32_t min, uint32_t max,
		TimerOverflow_t* source_tov, TimerOverflow_t* target_tov)
{
	btp->button_is_pressed = false;
	btp->min_overflow_trigger_count = min;
	btp->max_overflow_trigger_count = max;
	btp->source_tov = source_tov;
	btp->target_tov = target_tov;
}

void btp_press(ButtonPress_t* btp)
{
	btp->button_is_pressed = true;
	tov_activateOverflowTimer(btp->source_tov);
}

void btp_release(ButtonPress_t* btp)
{
	btp->button_is_pressed = false;
	tov_deactivateOverflowTimer(btp->source_tov);
}

void btp_incr_overflow_trigger_count(ButtonPress_t* btp, uint8_t delta)
{
	uint32_t curr_trigger = btp->target_tov->overflow_count_trigger;
	if (curr_trigger + delta > btp->max_overflow_trigger_count)
	{
		tov_setOverflowCountTrigger(btp->target_tov, btp->max_overflow_trigger_count);
	}
	else
	{
		tov_setOverflowCountTrigger(btp->target_tov, curr_trigger + delta);
	}
}

void btp_decr_overflow_trigger_count(ButtonPress_t* btp, uint8_t delta)
{
	uint32_t curr_trigger = btp->target_tov->overflow_count_trigger;
	if ( ((int32_t)curr_trigger - delta) < ((int32_t)(btp->min_overflow_trigger_count)) )
	{
		tov_setOverflowCountTrigger(btp->target_tov, btp->min_overflow_trigger_count);
	}
	else
	{
		tov_setOverflowCountTrigger(btp->target_tov, curr_trigger - delta);
	}
}

/******************************************************************************
 * PRIVATE FUNCTION DEFINITIONS
 *****************************************************************************/

