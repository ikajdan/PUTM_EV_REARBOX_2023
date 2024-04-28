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
    bool send_data;
    bool data_received;
    uint8_t pump1;
    uint8_t pump2;
    uint8_t fan_l;
    uint8_t fan_r;
    bool assi;
    bool assi_buzzer;
    bool rtds;
    bool brake_light;
    bool rfu1_safety;
    bool rfu2_safety;
    bool asms_safety;
    bool fw_safety;
    bool hv_safety;
    bool res_safety;
    bool hvd_safety;
    bool inv_safety;
    bool wheel_fl_safety;
    bool wheel_fr_safety;
    bool wheel_rl_safety;
    bool wheel_rr_safety;
    uint8_t mono_temperature;
    uint8_t sense_out;
    uint8_t water_pressure1;
    uint8_t water_pressure2;
    uint8_t water_temperature1;
    uint8_t water_temperature2;
    uint8_t analog_input1;
    uint8_t analog_input2;
    uint8_t analog_potentiometer_l;
    uint8_t analog_potentiometer_r;
} FSM_Handle_TypeDef;

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern FSM_Handle_TypeDef hfsm;

/* Public function prototypes ------------------------------------------------*/

#endif /* __FSM_H__ */
