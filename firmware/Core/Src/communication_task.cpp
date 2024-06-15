/**
 ******************************************************************************
 * @file           : fsm.c
 * @brief          : Finite-state machine library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "data.h"
// #include "PUTM_EV_CAN_LIBRARY/lib/can_interface.hpp"
#include "cmsis_os2.h"
#include "communication_task.h"
#include "fdcan.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
// extern osMutexId_t sharedDataMutexHandle;
extern Data_TypeDef sharedData;

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void Communication_Task(void* argument) {
    for(;;) {
        //        // Send
        //        if(interfaceData.state_changed) {
        //            PUTM_CAN::Dashboard frame = {
        //                    .ready_to_drive_button = interfaceData.rtd_button,
        //                    .ts_activation_button = interfaceData.tsa_button,
        //                    .user_button = interfaceData.usr_button,
        //            };
        //            auto message = PUTM_CAN::Can_tx_message<PUTM_CAN::Dashboard>(frame,
        //                    PUTM_CAN::can_tx_header_DASHBOARD);
        //
        //            message.send(hfdcan1);
        //
        //            interfaceData.state_changed = false;
        //        }
        //
        //        // Receive
        //        if(PUTM_CAN::can.get_pc_new_data()) {
        //            auto pc_data = PUTM_CAN::can.get_pc_main_data();
        //            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
        //                sharedData.speed = pc_data.vehicleSpeed;
        //                osMutexRelease(sharedDataMutexHandle);
        //            }
        //        }
        //
        //        // Reset watchdog
        //        HAL_IWDG_Refresh (&hiwdg);

        osDelay(100);
    }
}
