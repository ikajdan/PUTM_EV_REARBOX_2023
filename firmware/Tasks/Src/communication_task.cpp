/**
 ******************************************************************************
 * @file           : communication_task.cpp
 * @brief          : CAN communication task
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "communication_task.h"
#include "cmsis_os2.h"
#include "data.h"
#include "fdcan.h"
#include "iwdg.h"
#include <can_interface.hpp>

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
void Communication_Task(void* argument) {
    for(;;) {
        // Receive
        if(PUTM_CAN::can.get_pc_new_data()) {
            auto pc_data = PUTM_CAN::can.get_pc_main_data();
            if(osMutexAcquire(dataMutex, osWaitForever) == osOK) {
                data.rtd = pc_data.rtd;
                osMutexRelease(dataMutex);
            }
        }

        // Reset watchdog
        HAL_IWDG_Refresh(&hiwdg);

        osDelay(100);
    }
}
