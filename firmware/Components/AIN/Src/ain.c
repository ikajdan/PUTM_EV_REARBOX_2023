/**
 ******************************************************************************
 * @file           : ain.c
 * @brief          : AIN library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "ain.h"
#include "main.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define NOMINAL_RESISTANCE 100.0f
#define BETA_VALUE 3950.0f
#define REFERENCE_TEMPERATURE 25.0f

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
volatile uint32_t AIN_ADC1_REGISTER[AIN_ADC1_CHANNELS];
volatile uint32_t AIN_ADC2_REGISTER[AIN_ADC2_CHANNELS];

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
uint8_t AIN_GetResistance(AIN_Handle_TypeDef *handle)
{
    float v_out = (*handle->adc_raw * 3.3f) / 4095 / handle->gain;
    float resistance =
            (handle->r2 * handle->r3 + handle->r3 * (handle->r1 + handle->r2) * v_out / 3.3f) / (handle->r1 - (handle->r1 + handle->r2) * (v_out / 3.3f));

    return resistance;
}

uint8_t AIN_GetTemperature(AIN_Handle_TypeDef *handle)
{
    float v_out = (*handle->adc_raw * 3.3f) / 4095 / handle->gain;
    float resistance =
            (handle->r2 * handle->r3 + handle->r3 * (handle->r1 + handle->r2) * v_out / 3.3f) / (handle->r1 - (handle->r1 + handle->r2) * (v_out / 3.3f));
    float steinhart = log(resistance / BETA_VALUE);
    steinhart /= BETA_VALUE;
    steinhart += 1.0f / REFERENCE_TEMPERATURE;
    steinhart = 1.0f / steinhart;
    return steinhart;
}

uint8_t AIN_GetPressure(AIN_Handle_TypeDef *handle)
{
    float v_out = (*handle->adc_raw * 3.3f) / 4095 / handle->gain;
    float pressure = 0.5f + (v_out - 0.5f) * 1000.0f / 4.0f;
    pressure /= 100.0f; // Convert to bars

    return pressure;
}
