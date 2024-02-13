/**
 ******************************************************************************
 * @file           : fsm.h
 * @brief          : Finite-state machine library
 *
 ******************************************************************************
 */

#ifndef __FSM_H__
#define __FSM_H__

/* Public includes -----------------------------------------------------------*/
#include "fsm_conf.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Public typedefs -----------------------------------------------------------*/
typedef enum {
    FSM_STARTUP,
    FSM_RUNNING,
    FSM_ERROR,
} FSM_Device_State;

typedef struct {
    FSM_Device_State state;
} FSM_Handle_TypeDef;
/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern FSM_Handle_TypeDef hfsm;
/* Public function prototypes ------------------------------------------------*/

#endif /* __FSM_H__ */
