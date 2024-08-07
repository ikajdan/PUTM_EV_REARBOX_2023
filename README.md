# Rearbox

This PCB combines components for the rear side of the vehicle.

## Features

Communication:

- 2 CAN transceivers
- UART (internal only)
- SPI (internal only)
- I2C (internal only)

Outputs:

- 2 fan drivers
- 2 pump drivers
- ASSI driver
- RTDS driver
- brake light driver

Inputs:

- 12 digital safety inputs
- 2 suspension load cell sensors
- 2 suspension potentiometer sensors
- 2 water pressure sensors
- 2 water temperature sensors
- monocoque temperature sensors

## Firmware

> [!IMPORTANT]
> For the CAN library to work correctly, the auto-generated HAL driver file needs to be patched.
>
> Make sure to restore any changes made by the generator to the `firmware/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_fdcan.c` file or the receiving won't work!

Below are the changes that need to be made to the `stm32g4xx_hal_fdcan.c` file:

```diff
2231c2231
<     assert_param(IS_FDCAN_RX_FIFO(RxLocation));
---
>     //assert_param(IS_FDCAN_RX_FIFO(RxLocation));
2235c2235
<         if(RxLocation == FDCAN_RX_FIFO0) /* Rx element is assigned to the Rx FIFO 0 */
---
>         if(RxLocation == 0) /* Rx element is assigned to the Rx FIFO 0 */
2343c2343
<         if(RxLocation == FDCAN_RX_FIFO0) /* Rx element is assigned to the Rx FIFO 0 */
---
>         if(RxLocation == 0) /* Rx element is assigned to the Rx FIFO 0 */
```
