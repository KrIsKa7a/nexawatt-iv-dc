/*******************************************************************************
* File Name:   hal_infineon_cat1b_gpio.h
*
* Description: This is the header file containing declarations and definitions,
* related to the HAL implementation for the GPIO peripheral of the Infineon CAT1B devices.
* The NexaWatt-IV.DC framework offers custom implemented HAL for several Infineon devices.
* The implementation of the current HAL is dependent on the PDL, provided by Infineon Technologies.
*
* Related Document: See README.md
*
*******************************************************************************/

#ifndef NEXAWATT_IV_DC_HAL_INFINEON_CAT1B_GPIO_H
#define NEXAWATT_IV_DC_HAL_INFINEON_CAT1B_GPIO_H

// TODO: Uncomment the pre-processor defence after development
// Prevents the compilation of the HAL Implementation in case of missing PDL
//#ifdef CY_GPIO_H
/*******************************************************************************
* Header Files
*******************************************************************************/
#include "platform_types.h"

/*******************************************************************************
* Macros
*******************************************************************************/

/*******************************************************************************
* Type definitions
*******************************************************************************/

/*******************************************************************************
* Global Variables
*******************************************************************************/


/*******************************************************************************
* Function Prototypes
*******************************************************************************/
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Init_Digital_Pin(uint8 portNum, uint8 pinNum, const NexaWattGPIOPinConfig* pinConfig);
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Set_Pin_Alt_Functions(uint8 portNum, uint8 pinNum, NwGpioPinAltFunction altFunction);
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_DeInit_Port(uint8 portNum);

NwGpioPinResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Read(uint8 portNum, uint8 pinNum);
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Write(uint8 portNum, uint8 pinNum, nw_bool value);
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Toggle(uint8 portNum, uint8 pinNum);

NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Register_EXTI(uint8 portNum, uint8 pinNum, NexaWattGPIOInterruptEdgeEXTI intrEdge, void (*isrHandlerPtr)(void));
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Trigger_Sw_EXTI(uint8 portNum, uint8 pinNum);

/*******************************************************************************
* Function Definitions
*******************************************************************************/

//#endif
#endif
