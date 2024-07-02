/**
 ******************************************************************************
 * @file           : communication_task.cpp
 * @brief          : CAN communication task
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "communication_task.h"
#include "can_interface.hpp"
#include "cmsis_os2.h"
#include "data.h"
#include "fdcan.h"
#include "iwdg.h"

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
void Communication_Task(void* argument) {
    for(;;) {
        // Receive
        if(PUTM_CAN::can.get_pc_new_data()) {
            auto pc_data = PUTM_CAN::can.get_pc_main_data();
            if(osMutexAcquire(dataMutexHandle, osWaitForever) == osOK) {
                data.rtd = pc_data.rtd;
                osMutexRelease(dataMutexHandle);
            }
        }

        if(PUTM_CAN::can.get_front_data_main_new_data()) {
            auto front_data = PUTM_CAN::can.get_front_data_main_data();
            if(osMutexAcquire(dataMutexHandle, osWaitForever) == osOK) {
                if(front_data.is_braking) {
                    data.brake_light = true;
                } else {
                    data.brake_light = false;
                }

                osMutexRelease(dataMutexHandle);
            }
        }

        // Reset watchdog
        HAL_IWDG_Refresh(&hiwdg);

        osDelay(100);
    }
}
