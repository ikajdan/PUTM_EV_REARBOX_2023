/**
 ******************************************************************************
 * @file           : vnd7020aj.h
 * @brief          : VND7020AJ library
 *
 ******************************************************************************
 */

#ifndef __VND7020AJ_H__
#define __VND7020AJ_H__

/* Public includes -----------------------------------------------------------*/
#include "vnd7020aj_conf.h"

/* Public typedefs -----------------------------------------------------------*/
typedef enum {
    VND7020AJ_DISABLE = 0,
    VND7020AJ_PUMP1 = 1,
    VND7020AJ_PUMP2 = 2,
    VND7020AJ_FAN_L = 3,
    VND7020AJ_FAN_R = 4,
} VND7020AJ_Device;

/* Public defines ------------------------------------------------------------*/

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Set the current sensing mode for the given device.
 *
 * @param device The device
 */
void VND7020AJ_SetActive(VND7020AJ_Device device);

/**
 * @brief Get the active MultiSense device.
 *
 * @return The active device

 */
VND7020AJ_Device VND7020AJ_GetActive();

/**
 * @brief Get the current value of the currently selected channel.
 *
 * @return The reading of current value
 */
float VND7020AJ_GetCurrent();

#endif /* __VND7020AJ_H__ */
