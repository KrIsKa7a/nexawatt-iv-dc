/*******************************************************************************
* File Name:   hal_wrapper_gpio.c
*
* Description: This is the source file containing definitions,
* related to the HAL Wrapper for the GPIO peripheral. This wrapper is directly
* used by the NexaWattIV.DC framework and aims to provide maximum level of
* abstraction on the used MCU.
*
* Related Document: See README.md
*
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "hal_wrapper_gpio.h"

/*******************************************************************************
* Macros
*******************************************************************************/

/*******************************************************************************
* Type definitions
*******************************************************************************/

/*******************************************************************************
* Local Variables
*******************************************************************************/

/*******************************************************************************
* Local Function Prototypes
*******************************************************************************/

/*******************************************************************************
* Function Definitions
*******************************************************************************/
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Init_Digital_Pin(uint8 portNum, uint8 pinNum, const NexaWattGPIOPinConfig* const pinConfig)
{
    return 0;
}

NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_DeInit_Pin(uint8 portNum, uint8 pinNum)
{
    return 0;
}

NwGpioPinResult NexaWatt_HalWrapperGpio_Pin_Read(uint8 portNum, uint8 pinNum)
{
    return 0;
}

void NexaWatt_HalWrapperGpio_Pin_Write(uint8 portNum, uint8 pinNum, nw_bool value)
{

}

void NexaWatt_HalWrapperGpio_Pin_Toggle(uint8 portNum, uint8 pinNum)
{

}

void NexaWatt_HalWrapperGpio_Register_EXTI(uint8 portNum, uint8 pinNum, NexaWattGPIOInterruptEdgeEXTI intrEdge, void (*isrHandlerPtr)(void))
{

}

void NexaWatt_HalWrapperGpio_Trigger_Sw_EXTI(uint8 portNum, uint8 pinNum)
{

}