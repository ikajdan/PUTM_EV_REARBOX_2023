/**
 ******************************************************************************
 * @file           : interface_task.cpp
 * @brief          : Input/output interfacing task
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "interface_task.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "data.h"
#include "gpio.h"
#include "main.h"
#include "portable.h"
#include "task.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern osMutexId_t dataMutexHandle;
extern Data_TypeDef data;

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void Interface_Task(void* argument) {
    for(;;) {
        if(osMutexAcquire(dataMutexHandle, osWaitForever) == osOK) {
            if(data.rtd != data.rtd_prev) {
                if(data.rtd) {
                    HAL_GPIO_WritePin(RTDS_GPIO_Port, RTDS_Pin, GPIO_PIN_SET);
                    data.rtd_on_time = xTaskGetTickCount() * portTICK_PERIOD_MS;
                } else {
                    HAL_GPIO_WritePin(RTDS_GPIO_Port, RTDS_Pin, GPIO_PIN_RESET);
                }

                data.rtd_prev = data.rtd;
            }

            // Turn off RTD after 2 seconds
            if(data.rtd) {
                if(xTaskGetTickCount() * portTICK_PERIOD_MS - data.rtd_on_time > 2000) {
                    data.rtd = 0;
                }
            }

            if(data.brake_light) {
                HAL_GPIO_WritePin(BRAKE_LIGHT_GPIO_Port, BRAKE_LIGHT_Pin, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(BRAKE_LIGHT_GPIO_Port, BRAKE_LIGHT_Pin, GPIO_PIN_RESET);
            }

            osMutexRelease(dataMutexHandle);
        }

        osDelay(100);
    }
}
