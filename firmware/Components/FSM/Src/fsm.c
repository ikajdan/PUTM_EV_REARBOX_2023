/**
 ******************************************************************************
 * @file           : fsm.c
 * @brief          : Finite-state machine library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "fsm.h"
#include <stddef.h>

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
FSM_Handle_TypeDef hfsm = {
        .state = FSM_STARTUP,
        .send_data = false,
        .data_received = false,
        .pump1 = 0,
        .pump2 = 0,
        .fan_l = 0,
        .fan_r = 0,
        .assi = false,
        .rtds = false,
        .brake_light = false,
        .rfu1_safety = false,
        .rfu2_safety = false,
        .asms_safety = false,
        .fw_safety = false,
        .hv_safety = false,
        .res_safety = false,
        .hvd_safety = false,
        .inv_safety = false,
        .wheel_fl_safety = false,
        .wheel_fr_safety = false,
        .wheel_rl_safety = false,
        .wheel_rr_safety = false,
        .mono_temperature = 0,
        .sense_out = 0,
        .water_pressure1 = 0,
        .water_pressure2 = 0,
        .water_temperature1 = 0,
        .water_temperature2 = 0,
        .analog_input1 = 0,
        .analog_input2 = 0,
        .analog_potentiometer_l = 0,
        .analog_potentiometer_r = 0,
};
/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
