/**
 ******************************************************************************
 * @file           : rtd.c
 * @brief          : RTD library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "ain.h"
#include "main.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
volatile uint32_t AIN_ADC1_REGISTER[AIN_ADC1_CHANNELS];
volatile uint32_t AIN_ADC2_REGISTER[AIN_ADC2_CHANNELS];

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
float AIN_GetReading(AIN_Handle_TypeDef *handle)
{
    float v_out = (*handle->adc_raw * 3.3f) / 4095 / handle->gain;
    float resistance =
            (handle->r2 * handle->r3 + handle->r3 * (handle->r1 + handle->r2) * v_out / 3.3f) / (handle->r1 - (handle->r1 + handle->r2) * (v_out / 3.3f));

    return resistance;
}

uint8_t AIN_ReadTemperature(AIN_Handle_TypeDef *handle)
{

}

uint8_t AIN_ReadPressure(AIN_Handle_TypeDef *handle)
{

}

uint8_t AIN_ReadVoltage(AIN_Handle_TypeDef *handle)
{

}
