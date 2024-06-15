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

            osMutexRelease(dataMutex);
        }

        osDelay(100);
    }
}
