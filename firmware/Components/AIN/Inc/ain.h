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
#include <stdint.h>

/* Public typedefs -----------------------------------------------------------*/
/**
 * @brief Wheatstone bridge resistors
 *
 *
 *       ┌───[ R3 ]──(Vout+)──[ Rx ]───┐
 *       │                             │
 * VIN ──┤                             ├── GND
 *       │                             │
 *       └───[ R1 ]──(Vout-)──[ R2 ]───┘
 *
 */

typedef struct {
    const int r0;  // Nominal resistance
    const int r1;  // Wheatstone bridge resistor values
    const int r2;
    const int r3;
    const float gain;         // Instrumentation amplifier gain
    const uint32_t* adc_raw;  // ADC register pointer
} AIN_Handle_TypeDef;

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern volatile uint32_t AIN_ADC1_REGISTER[AIN_ADC1_CHANNELS];
extern volatile uint32_t AIN_ADC2_REGISTER[AIN_ADC2_CHANNELS];

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief  Get resistance from analog input
 * @param  handle: AIN handle
 * @retval Resistance in Ohms
 */
uint8_t AIN_GetResistance(AIN_Handle_TypeDef* handle);

/**
 * @brief  Get temperature from analog input
 * @param  handle: AIN handle
 * @retval Temperature in Celsius
 */
uint8_t AIN_GetTemperature(AIN_Handle_TypeDef* handle);

/**
 * @brief  Get pressure from analog input
 * @param  handle: AIN handle
 * @retval Pressure in Bars
 */
uint8_t AIN_GetPressure(AIN_Handle_TypeDef* handle);

#endif /* __AIN_H__ */
