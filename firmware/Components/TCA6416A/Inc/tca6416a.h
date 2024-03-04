/**
 ******************************************************************************
 * @file           : tca6416a.h
 * @brief          : TCA6416A library
 *
 ******************************************************************************
 */

#ifndef __TCA6416A_H__
#define __TCA6416A_H__

/* Public includes -----------------------------------------------------------*/
#include "stm32g4xx_hal.h"
#include "stdbool.h"
#include "stdint.h"

/* Public typedefs -----------------------------------------------------------*/
typedef struct {
    I2C_HandleTypeDef *hi2c;
    uint8_t i2caddr;
    uint16_t pinState;
    uint16_t pinModes;
} TCA6416A_Handle_TypeDef;

/* Public defines ------------------------------------------------------------*/
#define TCA_PIN_SET 1
#define TCA_PIN_RESET 0
#define TCA_PIN_INPUT 0
#define TCA_PIN_OUTPUT 1

#define TCA_REG_INPUT0 0x00
#define TCA_REG_INPUT1 0x01
#define TCA_REG_OUTPUT0 0x02
#define TCA_REG_OUTPUT1 0x03
#define TCA_REG_CONFIG0 0x06
#define TCA_REG_CONFIG1 0x07

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern TCA6416A_Handle_TypeDef htca;

/* Public function prototypes ------------------------------------------------*/
bool TCA6416A_Init(TCA6416A_Handle_TypeDef *tca, I2C_HandleTypeDef *hi2c, uint8_t addr_bit);
void TCA6416A_SetPinMode(TCA6416A_Handle_TypeDef *tca, uint8_t pin_num, int mode);
uint16_t TCA6416A_ReadMode(TCA6416A_Handle_TypeDef *tca);
void TCA6416A_WriteMode(TCA6416A_Handle_TypeDef *tca, uint16_t modes);
int TCA6416A_ReadPin(TCA6416A_Handle_TypeDef *tca, uint8_t pin_number);
void TCA6416A_WritePin(TCA6416A_Handle_TypeDef *tca, uint8_t pin_number, uint8_t level);
uint16_t TCA6416A_ReadPort(TCA6416A_Handle_TypeDef *tca);
void TCA6416A_WritePort(TCA6416A_Handle_TypeDef *tca, uint16_t i2cportval);

#endif /* __TCA6416A_H__ */
