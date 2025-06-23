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
/**
 * \brief Wrapper function used to initialize a GPIO digital pin with the specified configuration.
 *
 * This function uses the HAL Context to obtain the appropriate implementation for GPIO pin initialization.
 * It is called by the framework to configure the pin's direction, pull settings, drive mode, and other digital characteristics.
 * If the selected MCU is not supported and no user-defined initialization function has been registered, the function will assert and cause a fault.
 *
 * \param portNum - The number of the configured GPIO port.
 * \param pinNum - The number of the configured GPIO port pin.
 * \param pinConfig - A pointer, containing the framework's standardized GPIO pin configuration structure.
 *
 * \return NW_GPIO_BAD_PARAM - The validation of the provided pin configuration failed.
 * Please make sure that the provided port and pin numbers are existing for the Infineon CAT1B devices and use the provided enumerated types by the framework.
 * \return NW_GPIO_SUCCESS - The validation of the provided pin configuration was successful. The pin is configured and ready for use.
 */
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Init_Digital_Pin(uint8 portNum, uint8 pinNum, const NexaWattGPIOPinConfig* pinConfig);

/**
 * \brief Wrapper function used to assign an alternate function to a GPIO pin.
 *
 * This function configures the alternate function (such as peripheral I/O mapping) for the specified GPIO pin
 * using the appropriate HAL implementation. It is used when the pin must be repurposed for non-GPIO functionality
 * (e.g., UART, SPI, PWM). If the MCU does not support the operation and no override is registered, the function will assert and fault.
 *
 * \param portNum - The number of the configured GPIO port.
 * \param pinNum - The number of the configured GPIO port pin.
 * \param altFunction - The number of the desired Alternate Function. Please consult with the device datasheet for more details.
 *
 * \return NW_GPIO_BAD_PARAM - The provided combination of port and pin number does not exist for the Infineon CAT1B device.
 * \return NW_GPIO_SUCCESS - The alternate function is set to the corresponding register, if no assertions occurred.
 */
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Set_Pin_Alt_Functions(uint8 portNum, uint8 pinNum, NwGpioPinAltFunction altFunction);

/**
 * \brief Wrapper function used to de-initialize all pins on a specific GPIO port.
 *
 * This function releases the configuration and state of all pins on the specified GPIO port using the HAL layer.
 * It is intended to be used by the framework during shutdown, reconfiguration, or power-saving procedures.
 * If the selected MCU is not supported and no user-registered de-initialization function exists, the function will assert and lead to a fault.
 *
 * \param portNum - The number of the GPIO port to be de-initialized.
 *
 * \return NW_GPIO_BAD_PARAM - The provided port number does not exist for the Infineon CAT1B device.
 * \return NW_GPIO_SUCCESS - The GPIO port is de-initialized and ready to be re-initialized.
 */
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_DeInit_Port(uint8 portNum);

/**
 * \brief Wrapper function used to read the current logical value of a GPIO pin.
 *
 * This function uses the HAL Context to access the value currently present on the specified GPIO pin.
 * It is typically used by the framework when reading from input pins or digital states.
 * If the MCU does not support reading and no user-defined function has been registered, the function will assert and fault.
 *
 * \param portNum - The number of the desired GPIO port for the write.
 * \param pinNum - The number of the desired GPIO pin for the write.
 *
 * \return nwFalse - The value in the input register corresponding to the provided pin number is 0.
 * Note that this value is also returned in case of non-existing combination of port and pin numbers or improperly configured input pin.
 * \return nwTrue - The value in the input register corresponding to the provided pin number is 1.
 */
NwGpioPinResult NexaWatt_HalWrapperGpio_Pin_Read(uint8 portNum, uint8 pinNum);

/**
 * \brief Wrapper function used for writing a logical value to a GPIO pin.
 *
 * This function is used by the framework when a GPIO pin must be set to a specified output level.
 * It retrieves the relevant HAL implementation from the HAL Context. If the current MCU is not supported and
 * no user-defined implementation is registered, the function will assert and lead to a system fault.
 *
 * \param portNum - The number of the desired GPIO port for the write.
 * \param pinNum - The number of the desired GPIO pin for the write.
 * \param value - The value to be written to the output register.
 *
 * \return NW_GPIO_BAD_PARAM - The provided combination of port and pin number does not exist for the Infineon CAT1B device.
 * \return NW_GPIO_SUCCESS - The provided value is written in the output register of the provided GPIO port.
 */
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Pin_Write(uint8 portNum, uint8 pinNum, nw_bool value);

/**
 * \brief Wrapper function used to toggle the state of a specified GPIO pin.
 *
 * This function obtains the required HAL implementation for toggling the GPIO pin from the HAL Context component.
 * It is intended to be used by the framework when the logical value of a GPIO output pin needs to be inverted.
 * The function will assert and cause a fault if the current MCU is not supported by the framework's HAL, and the user has not registered a custom implementation
 * of the GPIO Pin Toggle functionality.
 *
 * \param portNum - The number of the desired GPIO port for the operation.
 * \param pinNum - The number of the desired GPIO pin to be toggled.
 *
 * \return NW_GPIO_BAD_PARAM - The provided combination of port and pin number does not exist for the Infineon CAT1B device.
 * \return NW_GPIO_SUCCESS - The GPIO pin output is toggled.
 */
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Pin_Toggle(uint8 portNum, uint8 pinNum);

/**
 * \brief Wrapper function used to register an external interrupt (EXTI) configuration for a GPIO pin.
 *
 * This function accesses the HAL Context to retrieve the appropriate implementation for EXTI configuration
 * and applies the user-provided settings to the designated GPIO pin. It is used by the framework when a pin-based
 * external interrupt must be configured. If the target MCU is unsupported and the user has not registered a custom
 * EXTI configuration function, the function will assert and lead to a system fault.
 *
 * \param portNum - The number of the desired GPIO port for the operation.
 * \param pinNum - The number of the desired GPIO pin to be configured as External IRQ source.
 * \param extiConfig - A pointer, containing the framework's standardized GPIO External Interrupt Request configuration.
 *
 * \return NW_GPIO_BAD_PARAM - The validation of the provided configuration failed. Please make sure that the combination of the port and pin number represents existing pin of the Infineon CAT1B devices.
 * Validate that the provided GPIO External Interrupt Request configuration is valid.
 * \return NW_GPIO_SUCCESS - The provided External Interrupt Request source is initialized and enabled.
 */
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Register_EXTI(uint8 portNum, uint8 pinNum, const NexaWattGPIOExtIRQConfig* extiConfig);

/**
 * \brief Wrapper function used to disable the external interrupt (EXTI) functionality for a GPIO pin.
 *
 * This function disables the EXTI line associated with the specified GPIO pin using the registered HAL implementation.
 * It is invoked by the framework when an external interrupt source should be deactivated for the pin.
 * If the current MCU is not supported and no user-registered implementation is provided, the function will assert and lead to a system fault.
 *
 * \param portNum - The number of the desired GPIO port for the operation.
 * \param pinNum - The number of the desired GPIO pin to be disabled from the External IRQ sources.
 * \param extiConfig - A pointer, containing the framework's standardized GPIO External Interrupt Request configuration.
 *
 * \return NW_GPIO_BAD_PARAM - The validation of the provided configuration failed. Please make sure that the combination of the port and pin number represents existing pin of the Infineon CAT1B devices.
 * Validate that the provided GPIO External Interrupt Request configuration is valid.
 * \return NW_GPIO_SUCCESS - The provided External Interrupt Request source is disabled.
 */
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Disable_EXTI(uint8 portNum, uint8 pinNum, const NexaWattGPIOExtIRQConfig* extiConfig);

/**
 * \brief Wrapper function used to retrieve the status of a GPIO pin's external interrupt (EXTI).
 *
 * This function queries the HAL for the interrupt status of the specified GPIO pin.
 * It is typically used by the framework to determine whether an EXTI event has occurred for the pin.
 * If the HAL implementation for the current MCU is unavailable and no user override is registered, the function will assert and cause a fault.
 *
 * \param portNum - The number of the desired GPIO port for the operation.
 * \param pinNum - The number of the desired GPIO pin for which the EXTI request status will be returned.
 *
 * \return nwFalse - The EXTI request is not raised or the provided combination of GPIO port and pin is not existing.
 * \return nwTrue - The EXTI request is raised and waiting to be processed by application.
 */
NwGpioExtiStatus NexaWatt_HalWrapperGpio_Get_EXTI_Status(uint8 portNum, uint8 pinNum);

/**
 * \brief Wrapper function used to clear the external interrupt (EXTI) status for a GPIO pin.
 *
 * This function clears the interrupt pending flag associated with the EXTI line for the specified pin via the HAL.
 * It should be called after an EXTI event has been handled to prevent re-triggering.
 * If the MCU does not support the operation and no user-provided implementation is available, the function will assert and cause a fault.
 *
 * \param portNum - The number of the desired GPIO port for the operation.
 * \param pinNum - The number of the desired GPIO pin for which the EXTI request status will be cleared.
 */
void NexaWatt_HalWrapperGpio_Clear_EXTI_Status(uint8 portNum, uint8 pinNum);

/**
 * \brief Wrapper function used to trigger a software-generated external interrupt (EXTI) for a GPIO pin.
 *
 * This function invokes the registered HAL implementation to simulate an EXTI event via software for the specified GPIO pin.
 * It is typically used for testing or manual invocation of EXTI handlers.
 * The function asserts and causes a fault if the current MCU is unsupported and no user-defined implementation has been registered.
 *
 * \param portNum - The number of the desired GPIO port for the operation.
 * \param pinNum - The number of the GPIO pin, whose EXTI capabilities will be tested.
 *
 * \return NW_GPIO_BAD_PARAM - The provided combination of port and pin number does not exist for the Infineon CAT1B device or the configured interrupt mask of the GPIO port restricts the interrupt requests on the provided pin number. Please investigate the GPIO configuration.
 * \return NW_GPIO_SUCCESS - An IRQ is triggered for the provided pin number on the provided GPIO port number.
 */
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Trigger_Sw_EXTI(uint8 portNum, uint8 pinNum);

/*******************************************************************************
* Function Definitions
*******************************************************************************/

#endif
