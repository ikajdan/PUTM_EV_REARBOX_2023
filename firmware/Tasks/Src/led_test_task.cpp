/**
 ******************************************************************************
 * @file           : led_test_task.cpp
 * @brief          : LED test task
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "led_test_task.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "data.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern Data_TypeDef data;
extern osMutexId_t dataMutexHandle;

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void Led_Test_Task(void* argument) {
    for(;;) {
        if(osMutexAcquire(dataMutexHandle, osWaitForever) == osOK) {
            osDelay(pdMS_TO_TICKS(3000));

            data.led_test = false;

            osMutexRelease(dataMutexHandle);

            osThreadTerminate(osThreadGetId());
        }
    }
}
