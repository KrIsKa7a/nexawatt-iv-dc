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
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Init_Digital_Pin(const uint8 portNum, const uint8 pinNum, const NexaWattGPIOPinConfig* const pinConfig)
{
    return NW_GPIO_FATAL_ERR;
}

NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Set_Pin_Alt_Functions(const uint8 portNum, const uint8 pinNum, const NwGpioPinAltFunction altFunction)
{
    return NW_GPIO_FATAL_ERR;
}

NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_DeInit_Port(const uint8 portNum)
{
    return NW_GPIO_FATAL_ERR;
}

NwGpioPinResult NexaWatt_HalWrapperGpio_Pin_Read(const uint8 portNum, const uint8 pinNum)
{
    return 0u;
}

NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Pin_Write(const uint8 portNum, const uint8 pinNum, const nw_bool value)
{
    return NW_GPIO_FATAL_ERR;
}

NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Pin_Toggle(const uint8 portNum, const uint8 pinNum)
{
    return NW_GPIO_FATAL_ERR;
}

NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Register_EXTI(const uint8 portNum, const uint8 pinNum, const NexaWattGPIOInterruptEdgeEXTI intrEdge, void (*const isrHandlerPtr)(void))
{
    return NW_GPIO_FATAL_ERR;
}

NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Trigger_Sw_EXTI(const uint8 portNum, const uint8 pinNum)
{
    return NW_GPIO_FATAL_ERR;
}