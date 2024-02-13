/**
 ******************************************************************************
 * @file           : rtd.c
 * @brief          : RTD library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "ain.h"
#include <math.h>

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
volatile uint16_t AIN_ADC1_REGISTER[AIN_ADC1_SAMPLES];
volatile uint16_t AIN_ADC2_REGISTER[AIN_ADC2_SAMPLES];

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
static float RTD_CalculateResistance(void) {
    // Convert to volts
    float v_out = AIN_ADC1_REGISTER[0] * (3.3f / 4095) / AIN_GAIN;
    float resistance =
            (AIN_R2 * AIN_R3 + AIN_R3 * (AIN_R1 + AIN_R2) * v_out / AIN_VIN)
                    / (AIN_R1 - (AIN_R1 + AIN_R2) * (v_out / AIN_VIN));
    return resistance;
}

/* Public functions ----------------------------------------------------------*/
