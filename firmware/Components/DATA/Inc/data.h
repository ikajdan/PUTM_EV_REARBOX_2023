/**
 ******************************************************************************
 * @file           : data.h
 * @brief          : Rearbox data
 *
 ******************************************************************************
 */

#ifndef __DATA_H__
#define __DATA_H__

/* Public includes -----------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>

/* Public typedefs -----------------------------------------------------------*/
typedef struct {
    bool brake_light;
    bool rtd;
    bool rtd_prev;
    bool rtd_buzzer;
    bool assi;
    bool assi_buzzer;
    uint8_t coolant_pressure_in;
    uint8_t coolant_pressure_out;
    uint8_t suspension_l;
    uint8_t suspension_r;
} Data_TypeDef;

typedef struct {
    bool rfu1;
    bool rfu2;
    bool asms;
    bool fw;
    bool hv;
    bool res;
    bool hvd;
    bool inv;
    bool wheel_fl;
    bool wheel_fr;
    bool wheel_rl;
    bool wheel_rr;
} Safety_TypeDef;

typedef struct {
    uint8_t mono;
    uint8_t coolant_in;
    uint8_t coolant_out;
    uint8_t oil_l;
    uint8_t oil_r;
} Temperature_TypeDef;

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

#endif /* __DATA_H__ */
