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
/**
 * \brief HAL function that provides GPIO pin initialization using the framework standardized
 * configuration structures and types. The function performs validation of the provided pin configuration
 * and initializes the GPIO pin according to the provided configuration, if validated successfully.
 * \param portNum - The number of the configured GPIO port.
 * \param pinNum - The number of the configured GPIO port pin.
 * \param pinConfig - A pointer, containing the framework's standardized GPIO pin configuration structure.
 * \return NW_GPIO_BAD_PARAM - The validation of the provided pin configuration failed.
 * Please make sure that the provided port and pin numbers are existing for the Infineon CAT1B devices and use the provided enumerated types by the framework.
 * \return NW_GPIO_SUCCESS - The validation of the provided pin configuration was successful. The pin is configured and ready for use.
 */
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Init_Digital_Pin(uint8 portNum, uint8 pinNum, const NexaWattGPIOPinConfig* pinConfig);

/**
 * \brief HAL function that can be used to set/change the alternate function of an already configured GPIO pin.
 * Please note that the passed GPIO Alternate Function value is not validated! The function will assert in case of
 * providing a wrong/non-existing Alternate Function value.
 * \param portNum - The number of the configured GPIO port.
 * \param pinNum - The number of the configured GPIO port pin.
 * \param altFunction - The number of the desired Alternate Function. Please consult with the device datasheet for more details.
 * \return NW_GPIO_BAD_PARAM - The provided combination of port and pin number does not exist for the Infineon CAT1B device.
 * \return NW_GPIO_SUCCESS - The alternate function is set to the corresponding register, if no assertions occurred.
 */
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Set_Pin_Alt_Functions(uint8 portNum, uint8 pinNum, NwGpioPinAltFunction altFunction);

/**
 * \brief HAL function that can be used to de-initialize an already configured GPIO port.
 * The function ensures that registers of the GPIO port are reset to their default values.
 * The function can be used if re-initialization of a GPIO port is needed, due to some kind of failure event.
 * \param portNum - The number of the GPIO port to be de-initialized.
 * \return NW_GPIO_BAD_PARAM - The provided port number does not exist for the Infineon CAT1B device.
 * \return NW_GPIO_SUCCESS - The GPIO port is de-initialized and ready to be re-initialized.
 */
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_DeInit_Port(uint8 portNum);

NwGpioPinResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Read(uint8 portNum, uint8 pinNum);

/**
 * \brief HAL function that can be used to write a digital value (true or false) to already configured
 * GPIO pin. The function performs a validation for the existence of the provided combination of GPIO port and pin numbers for Infineon CAT1B devices.
 * The provided value is being written to the provided port output register at the provided pin's corresponding bit.
 * \param portNum - The number of the desired GPIO port for the write.
 * \param pinNum - The number of the desired GPIO pin for the write.
 * \param value - The value to be written to the output register.
 * \return NW_GPIO_BAD_PARAM - The provided combination of port and pin number does not exist for the Infineon CAT1B device.
 * \return NW_GPIO_SUCCESS - The provided value is written in the output register of the provided GPIO port.
 */
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Write(uint8 portNum, uint8 pinNum, nw_bool value);
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Toggle(uint8 portNum, uint8 pinNum);

NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Register_EXTI(uint8 portNum, uint8 pinNum, NexaWattGPIOInterruptEdgeEXTI intrEdge, void (*isrHandlerPtr)(void));
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Trigger_Sw_EXTI(uint8 portNum, uint8 pinNum);

/*******************************************************************************
* Function Definitions
*******************************************************************************/

//#endif
#endif
