/**
 ******************************************************************************
 * @file           : tca6416a.c
 * @brief          : TCA6416A library
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tca6416a.h"
#include "main.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
bool TCA6416A_begin(TCA6416A *tca, uint8_t addr_bit, I2C_HandleTypeDef *hi2c) {
    HAL_GPIO_WritePin(SAFETY_RESET_GPIO_Port, SAFETY_RESET_Pin, GPIO_PIN_SET);

    tca->i2caddr = 0x20 | addr_bit;
    tca->hi2c_ = hi2c;

    // Check if device is connected
    if(HAL_I2C_IsDeviceReady(tca->hi2c_, tca->i2caddr << 1, 2, HAL_MAX_DELAY) != HAL_OK) {
        return false;
    }

    TCA6416A_port_read(tca);
    TCA6416A_mode_read(tca);

    return true;
}

void TCA6416A_pin_mode(TCA6416A *tca, uint8_t pinNum, int mode)
{
    uint16_t mask = 1 << pinNum;

    if(mode == INPUT) {
        tca->pinModes |= mask;
    } else {
        tca->pinModes &= ~mask;
    }

    TCA6416A_mode_write(tca, tca->pinModes);
}

uint16_t TCA6416A_mode_read(TCA6416A *tca)
{
    uint8_t data[2];
    HAL_I2C_Mem_Read(tca->hi2c_, tca->i2caddr << 1, TCAREG_CONFIG0, I2C_MEMADD_SIZE_8BIT, data, 2, HAL_MAX_DELAY);

    tca->pinModes = data[0] | (data[1] << 8);

    return tca->pinModes;
}

void TCA6416A_mode_write(TCA6416A *tca, uint16_t modes)
{
    uint8_t data[3];
    data[0] = TCAREG_CONFIG0;
    data[1] = modes & 0xFF;
    data[2] = modes >> 8;

    HAL_I2C_Master_Transmit(tca->hi2c_, tca->i2caddr << 1, data, 3, HAL_MAX_DELAY);

    tca->pinModes = modes;
}

int TCA6416A_pin_read(TCA6416A *tca, uint8_t pinNum)
{
    uint16_t mask = 1 << pinNum;

    TCA6416A_port_read(tca);

    if((tca->pinState & mask) == mask)
            {
        return 1;
    } else {
        return 0;
    }
}

void TCA6416A_pin_write(TCA6416A *tca, uint8_t pinNum, uint8_t level) {
    uint16_t mask = 1 << pinNum;

    if(level == HIGH) {
        tca->pinState |= mask;
    } else {
        tca->pinState &= ~mask;
    }

    TCA6416A_port_write(tca, tca->pinState);
}

uint16_t TCA6416A_port_read(TCA6416A *tca)
{
    uint8_t data[2];
    HAL_I2C_Mem_Read(tca->hi2c_, tca->i2caddr << 1, TCAREG_INPUT0, I2C_MEMADD_SIZE_8BIT, data, 2, HAL_MAX_DELAY);

    uint16_t tempInput = data[0] | (data[1] << 8);

    tca->pinState = (tca->pinState & ~tca->pinModes) | (tempInput & tca->pinModes);

    return tca->pinState;
}

void TCA6416A_port_write(TCA6416A *tca, uint16_t i2cportval) {
    uint8_t data[3];
    data[0] = TCAREG_OUTPUT0;
    data[1] = i2cportval & 0xFF;
    data[2] = i2cportval >> 8;

    HAL_I2C_Master_Transmit(tca->hi2c_, tca->i2caddr << 1, data, 3, HAL_MAX_DELAY);

    tca->pinState = i2cportval;
}
