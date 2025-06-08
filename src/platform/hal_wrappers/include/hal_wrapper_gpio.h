/*******************************************************************************
* File Name:   hal_wrapper_gpio.h
*
* Description: This is the header file containing declarations and definitions,
* related to the HAL Wrapper for the GPIO peripheral. This wrapper is directly
* used by the NexaWatt-IV.DC framework and aims to provide maximum level of
* abstraction on the used MCU.
*
* Related Document: See README.md
*
*******************************************************************************/

#ifndef NEXAWATT_IV_DC_HAL_WRAPPER_GPIO_H
#define NEXAWATT_IV_DC_HAL_WRAPPER_GPIO_H

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
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Init_Digital_Pin(uint8 portNum, uint8 pinNum, const NexaWattGPIOPinConfig* pinConfig);
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_DeInit_Port(uint8 portNum);

NwGpioPinResult NexaWatt_HalWrapperGpio_Pin_Read(uint8 portNum, uint8 pinNum);
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Pin_Write(uint8 portNum, uint8 pinNum, nw_bool value);
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Pin_Toggle(uint8 portNum, uint8 pinNum);

NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Register_EXTI(uint8 portNum, uint8 pinNum, NexaWattGPIOInterruptEdgeEXTI intrEdge, void (*isrHandlerPtr)(void));
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Trigger_Sw_EXTI(uint8 portNum, uint8 pinNum);

/*******************************************************************************
* Function Definitions
*******************************************************************************/

#endif
