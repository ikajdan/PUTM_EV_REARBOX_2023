/**
 ******************************************************************************
 * @file           : interface_task.cpp
 * @brief          : Input/output interfacing task
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "interface_task.h"
#include "cmsis_os2.h"
#include "data.h"
#include "gpio.h"
#include "main.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern osMutexId_t dataMutex;
extern Data_TypeDef data;

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void Interface_Task(void* argument) {
    for(;;) {
        if(osMutexAcquire(dataMutex, osWaitForever) == osOK) {
            if(data.rtd != data.rtd_prev) {
                if(data.rtd) {
                    HAL_GPIO_WritePin(RTDS_GPIO_Port, RTDS_Pin, GPIO_PIN_SET);
                } else {
                    HAL_GPIO_WritePin(RTDS_GPIO_Port, RTDS_Pin, GPIO_PIN_RESET);
                }

                data.rtd_prev = data.rtd;
            }

            if(data.brake_light) {
                HAL_GPIO_WritePin(BRAKE_LIGHT_GPIO_Port, BRAKE_LIGHT_Pin, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(BRAKE_LIGHT_GPIO_Port, BRAKE_LIGHT_Pin, GPIO_PIN_RESET);
            }

            osMutexRelease(dataMutex);
        }

        osDelay(100);
    }
}
