/**
 ******************************************************************************
 * @file           : vnd7020aj.c
 * @brief          : VND7020AJ library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "vnd7020aj.h"
#include "ain.h"
#include "main.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
VND7020AJ_Device VND7020AJ_ActiveDevice = VND7020AJ_DISABLE;

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void VND7020AJ_SetActive(VND7020AJ_Device device) {
    if(VND7020AJ_ActiveDevice == device) {
        return;
    }

    // Disable the sense output
    HAL_GPIO_WritePin(SENSE_ENABLE_FANS_GPIO_Port, SENSE_ENABLE_FANS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SENSE_ENABLE_PUMPS_GPIO_Port, SENSE_ENABLE_PUMPS_Pin, GPIO_PIN_RESET);

    switch(device) {
        case VND7020AJ_PUMP1:
            // Set the active device
            VND7020AJ_ActiveDevice = device;

            // Set the multiplexer address to 00
            HAL_GPIO_WritePin(SENSE_ADDRESS_IN0_GPIO_Port, SENSE_ADDRESS_IN0_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(SENSE_ADDRESS_IN1_GPIO_Port, SENSE_ADDRESS_IN1_Pin, GPIO_PIN_RESET);

            // Enable the pumps' sense
            HAL_GPIO_WritePin(SENSE_ENABLE_PUMPS_GPIO_Port, SENSE_ENABLE_PUMPS_Pin, GPIO_PIN_SET);
            break;

        case VND7020AJ_PUMP2:
            // Set the active device
            VND7020AJ_ActiveDevice = device;

            // Set the multiplexer address to 10
            HAL_GPIO_WritePin(SENSE_ADDRESS_IN0_GPIO_Port, SENSE_ADDRESS_IN0_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(SENSE_ADDRESS_IN1_GPIO_Port, SENSE_ADDRESS_IN1_Pin, GPIO_PIN_RESET);

            // Enable the pumps' sense
            HAL_GPIO_WritePin(SENSE_ENABLE_PUMPS_GPIO_Port, SENSE_ENABLE_PUMPS_Pin, GPIO_PIN_SET);
            break;

        case VND7020AJ_FAN_L:
            // Set the active device
            VND7020AJ_ActiveDevice = device;

            // Set the multiplexer address to 00
            HAL_GPIO_WritePin(SENSE_ADDRESS_IN0_GPIO_Port, SENSE_ADDRESS_IN0_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(SENSE_ADDRESS_IN1_GPIO_Port, SENSE_ADDRESS_IN1_Pin, GPIO_PIN_RESET);

            // Enable the fans' sense
            HAL_GPIO_WritePin(SENSE_ENABLE_FANS_GPIO_Port, SENSE_ENABLE_FANS_Pin, GPIO_PIN_SET);
            break;

        case VND7020AJ_FAN_R:
            // Set the active device
            VND7020AJ_ActiveDevice = device;

            // Set the multiplexer address to 10
            HAL_GPIO_WritePin(SENSE_ADDRESS_IN0_GPIO_Port, SENSE_ADDRESS_IN0_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(SENSE_ADDRESS_IN1_GPIO_Port, SENSE_ADDRESS_IN1_Pin, GPIO_PIN_RESET);

            // Enable the fans' sense
            HAL_GPIO_WritePin(SENSE_ENABLE_FANS_GPIO_Port, SENSE_ENABLE_FANS_Pin, GPIO_PIN_SET);
            break;

        case VND7020AJ_DISABLE:
            return;

        default:
            return;
    }
}

VND7020AJ_Device VND7020AJ_GetActive() {
    return VND7020AJ_ActiveDevice;
}

float VND7020AJ_GetCurrent() {
    float v_sense = AIN_ADC1_REGISTER[ADC_CHANNEL_SENSE_OUT] * (3.3f / 4095);
    float i_out = VND7020AJ_MULTISENSE_K * v_sense / VND7020AJ_MULTISENSE_R;

    return i_out;
}
