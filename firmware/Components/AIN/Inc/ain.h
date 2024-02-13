/**
 ******************************************************************************
 * @file           : ain.h
 * @brief          : AIN library
 *
 ******************************************************************************
 */

#ifndef __AIN_H__
#define __AIN_H__

/* Public includes -----------------------------------------------------------*/
#include "ain_conf.h"
#include "stm32g4xx_hal.h"

/* Public typedefs -----------------------------------------------------------*/

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern volatile uint16_t AIN_ADC1_REGISTER[AIN_ADC1_SAMPLES];
extern volatile uint16_t AIN_ADC2_REGISTER[AIN_ADC2_SAMPLES];

/* Public function prototypes ------------------------------------------------*/

#endif /* __AIN_H__ */
