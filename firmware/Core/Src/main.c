/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "fdcan.h"
#include "i2c.h"
#include "iwdg.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pwm.h"
#include "ain.h"
#include "fsm.h"
#include "tca6416a.h"
#include "vnd7020aj.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_FDCAN1_Init();
    MX_FDCAN2_Init();
    MX_I2C3_Init();
    MX_USART3_UART_Init();
    MX_I2C2_Init();
    MX_DAC1_Init();
    MX_SPI3_Init();
    MX_ADC1_Init();
    MX_ADC2_Init();
    MX_TIM2_Init();
    MX_TIM15_Init();
    MX_I2C1_Init();
    MX_IWDG_Init();
    MX_TIM1_Init();
    MX_TIM3_Init();
    /* USER CODE BEGIN 2 */
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)AIN_ADC1_REGISTER, AIN_ADC1_CHANNELS);
    HAL_ADC_Start_DMA(&hadc2, (uint32_t*)AIN_ADC2_REGISTER, AIN_ADC2_CHANNELS);

    HAL_TIM_Base_Start_IT(&htim1); // (10 Hz) Control loop
    HAL_TIM_Base_Start_IT(&htim3); // (3.53 Hz) ASSI light

    HAL_TIM_PWM_Start(&htim_pump, TIM_CHANNEL_PUMP1); // (10 kHz) Pump 1 PWM
    HAL_TIM_PWM_Start(&htim_pump, TIM_CHANNEL_PUMP2); // (10 kHz) Pump 2 PWM
    HAL_TIM_PWM_Start(&htim_fan, TIM_CHANNEL_FAN_L); // (10 kHz) Left fan PWM
    HAL_TIM_PWM_Start(&htim_fan, TIM_CHANNEL_FAN_R); // (10 kHz) Right fan PWM

    // Turn on pumps and fans
    PWM_SetDutyCycle(&htim_pump, TIM_CHANNEL_PUMP1, 70);
    PWM_SetDutyCycle(&htim_pump, TIM_CHANNEL_PUMP2, 70);
    PWM_SetDutyCycle(&htim_fan, TIM_CHANNEL_FAN_L, 70);
    PWM_SetDutyCycle(&htim_fan, TIM_CHANNEL_FAN_R, 70);

    TCA6416A_Init(&htca, &hi2c3, 0x20);
    TCA6416A_SetPinMode(&htca, PIN_RFU2, TCA_PIN_INPUT);
    TCA6416A_SetPinMode(&htca, PIN_RFU1, TCA_PIN_INPUT);
    TCA6416A_SetPinMode(&htca, PIN_ASMS, TCA_PIN_INPUT);
    TCA6416A_SetPinMode(&htca, PIN_FW, TCA_PIN_INPUT);
    TCA6416A_SetPinMode(&htca, PIN_HV, TCA_PIN_INPUT);
    TCA6416A_SetPinMode(&htca, PIN_RES, TCA_PIN_INPUT);
    TCA6416A_SetPinMode(&htca, PIN_HVD, TCA_PIN_INPUT);
    TCA6416A_SetPinMode(&htca, PIN_INV, TCA_PIN_INPUT);
    TCA6416A_SetPinMode(&htca, PIN_WHEEL_FL, TCA_PIN_INPUT);
    TCA6416A_SetPinMode(&htca, PIN_WHEEL_FR, TCA_PIN_INPUT);
    TCA6416A_SetPinMode(&htca, PIN_WHEEL_RL, TCA_PIN_INPUT);
    TCA6416A_SetPinMode(&htca, PIN_WHEEL_RR, TCA_PIN_INPUT);

    TCA6416A_SetPinMode(&htca, PIN_ERROR_LED, TCA_PIN_OUTPUT);
    TCA6416A_SetPinMode(&htca, PIN_SAFETY_LED, TCA_PIN_OUTPUT);
    TCA6416A_SetPinMode(&htca, PIN_FUSE_LED, TCA_PIN_OUTPUT);

    // Turn on all LEDs
    TCA6416A_WritePin(&htca, PIN_ERROR_LED, TCA_PIN_SET);
    TCA6416A_WritePin(&htca, PIN_SAFETY_LED, TCA_PIN_SET);
    TCA6416A_WritePin(&htca, PIN_FUSE_LED, TCA_PIN_SET);

    AIN_Handle_TypeDef hain_mono_temperature = { 1000, 3000, 1000, 2000, 4.09f,
            AIN_ADC1_REGISTER[ADC_CHANNEL_MONO_TEMPERATURE] };
    AIN_Handle_TypeDef hain_sense_out = { 1000, 3000, 1000, 2000, 4.09f,
            AIN_ADC1_REGISTER[ADC_CHANNEL_SENSE_OUT] };
    AIN_Handle_TypeDef hain_water_pressure1 = { 1000, 3000, 1000, 2000, 4.09f,
            AIN_ADC1_REGISTER[ADC_CHANNEL_WATER_PRESSURE1] };
    AIN_Handle_TypeDef hain_water_pressure2 = { 1000, 3000, 1000, 2000, 4.09f,
            AIN_ADC1_REGISTER[ADC_CHANNEL_WATER_PRESSURE2] };
    AIN_Handle_TypeDef hain_water_temperature1 = { 1000, 3000, 1000, 2000, 4.09f,
            AIN_ADC1_REGISTER[ADC_CHANNEL_WATER_TEMPERATURE1] };
    AIN_Handle_TypeDef hain_water_temperature2 = { 1000, 3000, 1000, 2000, 4.09f,
            AIN_ADC1_REGISTER[ADC_CHANNEL_WATER_TEMPERATURE2] };
    AIN_Handle_TypeDef hain_analog_input1 = { 1000, 3000, 1000, 2000, 4.09f,
            AIN_ADC2_REGISTER[ADC_CHANNEL_ANALOG_INPUT1] };
    AIN_Handle_TypeDef hain_analog_input2 = { 1000, 3000, 1000, 2000, 4.09f,
            AIN_ADC2_REGISTER[ADC_CHANNEL_ANALOG_INPUT2] };
    AIN_Handle_TypeDef hain_analog_potentiometer_l = { 1000, 3000, 1000, 2000, 4.09f,
            AIN_ADC2_REGISTER[ADC_CHANNEL_ANALOG_POTENTIOMETER_L] };
    AIN_Handle_TypeDef hain_analog_potentiometer_r = { 1000, 3000, 1000, 2000, 4.09f,
            AIN_ADC2_REGISTER[ADC_CHANNEL_ANALOG_POTENTIOMETER_R] };
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while(1)
    {
        if(hfsm.send_data) {
            hfsm.send_data = false;

            hfsm.mono_temperature = AIN_ReadTemperature(&hain_mono_temperature);
            hfsm.sense_out = AIN_ReadTemperature(&hain_sense_out);
            hfsm.water_pressure1 = AIN_ReadPressure(&hain_water_pressure1);
            hfsm.water_pressure2 = AIN_ReadPressure(&hain_water_pressure2);
            hfsm.water_temperature1 = AIN_ReadTemperature(&hain_water_temperature1);
            hfsm.water_temperature2 = AIN_ReadTemperature(&hain_water_temperature2);
            hfsm.analog_input1 = AIN_ReadVoltage(&hain_analog_input1);
            hfsm.analog_input2 = AIN_ReadVoltage(&hain_analog_input2);
            hfsm.analog_potentiometer_l = AIN_ReadVoltage(&hain_analog_potentiometer_l);
            hfsm.analog_potentiometer_r = AIN_ReadVoltage(&hain_analog_potentiometer_r);

            // TODO: Send data
        }

        if(hfsm.data_received) {
            hfsm.data_received = false;
            // TODO: Process received data

            PWM_SetDutyCycle(&htim_pump, TIM_CHANNEL_PUMP1, hfsm.pump1);
            PWM_SetDutyCycle(&htim_pump, TIM_CHANNEL_PUMP2, hfsm.pump2);
            PWM_SetDutyCycle(&htim_fan, TIM_CHANNEL_FAN_L, hfsm.fan_l);
            PWM_SetDutyCycle(&htim_fan, TIM_CHANNEL_FAN_R, hfsm.fan_r);

            HAL_GPIO_WritePin(ASSI_BUZZER_GPIO_Port, ASSI_BUZZER_Pin, hfsm.assi_buzzer ? GPIO_PIN_SET : GPIO_PIN_RESET);
            HAL_GPIO_WritePin(RTDS_GPIO_Port, RTDS_Pin, hfsm.rtds ? GPIO_PIN_SET : GPIO_PIN_RESET);
            HAL_GPIO_WritePin(BRAKE_LIGHT_GPIO_Port, BRAKE_LIGHT_Pin, hfsm.brake_light ? GPIO_PIN_SET : GPIO_PIN_RESET);
        }
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

    /** Configure the main internal regulator output voltage
     */
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV12;
    RCC_OscInitStruct.PLL.PLLN = 85;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV8;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
            {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
            | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
            {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
/**
 * @brief  Period elapsed callback in non-blocking mode
 * @param  htim: TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim == &htim1) {
        if(hfsm.state == FSM_RUNNING) {
            hfsm.send_data = true;
        } else {
            if(HAL_GetTick() > STARTUP_DELAY) {
                if(hfsm.state == FSM_STARTUP) {
                    hfsm.state = FSM_RUNNING;

                    TCA6416A_WritePin(&htca, PIN_ERROR_LED, TCA_PIN_RESET);
                    TCA6416A_WritePin(&htca, PIN_SAFETY_LED, TCA_PIN_RESET);
                    TCA6416A_WritePin(&htca, PIN_FUSE_LED, TCA_PIN_RESET);
                }
            }
        }

        HAL_IWDG_Refresh(&hiwdg); // 2 seconds timeout
    } else if(htim == &htim3) {
        if(hfsm.assi) {
            HAL_GPIO_WritePin(ASSI_LED_R_GPIO_Port, ASSI_LED_R_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(ASSI_LED_G_GPIO_Port, ASSI_LED_G_Pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(ASSI_LED_R_GPIO_Port, ASSI_LED_R_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(ASSI_LED_G_GPIO_Port, ASSI_LED_G_Pin, GPIO_PIN_RESET);
        }
    }
}

/**
 * @brief  EXTI line detection callbacks
 * @param  GPIO_Pin: Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == SAFETY_INT_Pin) {
        hfsm.rfu1_safety = TCA6416A_ReadPin(&htca, PIN_RFU1);
        hfsm.rfu2_safety = TCA6416A_ReadPin(&htca, PIN_RFU2);
        hfsm.asms_safety = TCA6416A_ReadPin(&htca, PIN_ASMS);
        hfsm.fw_safety = TCA6416A_ReadPin(&htca, PIN_FW);
        hfsm.hv_safety = TCA6416A_ReadPin(&htca, PIN_HV);
        hfsm.res_safety = TCA6416A_ReadPin(&htca, PIN_RES);
        hfsm.hvd_safety = TCA6416A_ReadPin(&htca, PIN_HVD);
        hfsm.inv_safety = TCA6416A_ReadPin(&htca, PIN_INV);
        hfsm.wheel_fl_safety = TCA6416A_ReadPin(&htca, PIN_WHEEL_FL);
        hfsm.wheel_fr_safety = TCA6416A_ReadPin(&htca, PIN_WHEEL_FR);
        hfsm.wheel_rl_safety = TCA6416A_ReadPin(&htca, PIN_WHEEL_RL);
        hfsm.wheel_rr_safety = TCA6416A_ReadPin(&htca, PIN_WHEEL_RR);
    }
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while(1) {
        hfsm.state = FSM_ERROR;
        TCA6416A_WritePin(&htca, PIN_ERROR_LED, TCA_PIN_SET);
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    // printf("Wrong parameters value: file %s on line %lu\r\n", file, line);
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
