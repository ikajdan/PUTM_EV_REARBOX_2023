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
    uint8_t i2caddr;
    I2C_HandleTypeDef *hi2c_;
    uint16_t pinState;
    uint16_t pinModes;
} TCA6416A;

/* Public defines ------------------------------------------------------------*/
#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1
#define TCAREG_INPUT0 0x00
#define TCAREG_INPUT1 0x01
#define TCAREG_OUTPUT0 0x02
#define TCAREG_OUTPUT1 0x03
#define TCAREG_CONFIG0 0x06
#define TCAREG_CONFIG1 0x07

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
bool TCA6416A_begin(TCA6416A *tca, uint8_t addr_bit, I2C_HandleTypeDef *hi2c);

void TCA6416A_pin_mode(TCA6416A *tca, uint8_t pinNum, int mode);
uint16_t TCA6416A_mode_read(TCA6416A *tca);
void TCA6416A_mode_write(TCA6416A *tca, uint16_t modes);

int TCA6416A_pin_read(TCA6416A *tca, uint8_t pinNum);
void TCA6416A_pin_write(TCA6416A *tca, uint8_t pinNum, uint8_t level);

uint16_t TCA6416A_port_read(TCA6416A *tca);
void TCA6416A_port_write(TCA6416A *tca, uint16_t i2cportval);

#endif /* __TCA6416A_H__ */
