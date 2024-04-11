/**
 * @file      
 * @author    
 * @copyright 
 * @date      
 *
 * @brief     
 */
 #ifndef TIMER_OVERFLOW_T_H
 #define TIMER_OVERFLOW_T_H

/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 * PUBLIC TYPES
 *****************************************************************************/
typedef struct{
	bool active;						/*< true if TimerOverflow_t is active */
	uint32_t overflow_counter;			/*< counter of timer overflows */
	uint32_t overflow_count_trigger;		/*< amount of timer overflows after which
	 	 	 	 	 	 	 	 	 	 overflow_counter is reseted and overflow_flag is set */
	bool overflow_flag;					/*< indicate if overflow_counter overflew */
}TimerOverflow_t;


/******************************************************************************
 * EXPORTED GLOBAL VARIABLES
 *****************************************************************************/
extern TimerOverflow_t tov_led;
extern TimerOverflow_t tov_left_button;
extern TimerOverflow_t tov_right_button;

/******************************************************************************
 * PUBLIC MACROS
 *****************************************************************************/

/******************************************************************************
 * PUBLIC FUNCTION DECLARATIONS
 *****************************************************************************/
// constructor
TimerOverflow_t* tov_Constructor(TimerOverflow_t* tov, uint32_t max_overflow_value);

// activate/deactivate TimerOverflow_t
void tov_activateOverflowTimer(TimerOverflow_t* tov);
void tov_deactivateOverflowTimer(TimerOverflow_t* tov);
bool tov_getActive(TimerOverflow_t tov);

// overflow_flag methods
bool tov_getOverflowFlag(TimerOverflow_t* tov);
void tov_setOverflowFlag(TimerOverflow_t* tov, bool new_value);

// overflow_counter methods
void tov_incrementOverflowCounter(TimerOverflow_t* tov);

// overflow_count_trigger methods
void tov_setOverflowCountTrigger(TimerOverflow_t* tov, uint32_t new_value);

// reset TimerOverflow_t instance
void tov_resetTimerOverflow(TimerOverflow_t* tov);

#endif
