/**
 ******************************************************************************
 * @file           : ain_conf.h
 * @brief          : AIN library configuration
 *
 ******************************************************************************
 */

#ifndef __AIN_CONFIG_H__
#define __AIN_CONFIG_H__

/* Public includes -----------------------------------------------------------*/

/* Public typedefs -----------------------------------------------------------*/

/* Public defines ------------------------------------------------------------*/
/**
 * @brief RTD's nominal resistance
 */
#define AIN_R0 100

/**
 * @brief Wheatstone bridge resistor values
 *
 *
 *       ┌───[ R3 ]──(Vout+)──[ Rx ]───┐
 *       │                             │
 * VIN ──┤                             ├── GND
 *       │                             │
 *       └───[ R1 ]──(Vout-)──[ R2 ]───┘
 *
 */
#define AIN_R1 1000
#define AIN_R2 100
#define AIN_R3 1000

/**
 * @brief Wheatstone bridge reference voltage
 */
#define AIN_VIN 3.3f

/**
 * @brief Instrumentation amplifier gain
 */
#define AIN_GAIN 6

/**
 * @brief The number of samples to be averaged when measuring the temperature
 */
#define AIN_ADC1_SAMPLES 6
#define AIN_ADC2_SAMPLES 4

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

#endif /* __AIN_CONFIG_H__ */
