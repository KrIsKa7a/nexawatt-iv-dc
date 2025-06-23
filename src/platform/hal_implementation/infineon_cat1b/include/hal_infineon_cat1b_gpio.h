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

/**
 * HAL function that can be used to read a digital value (true or false) from already configured
 * GPIO pin. The function performs a validation for the existence of the provided combination of GPIO port and pin numbers for Infineon CAT1B devices.
 * The input register of the GPIO port is being read and the value at the bit number, corresponding to the provided pin number is returned by the function.
 * \param portNum - The number of the desired GPIO port for the write.
 * \param pinNum - The number of the desired GPIO pin for the write.
 * \return nwFalse - The value in the input register corresponding to the provided pin number is 0.
 * Note that this value is also returned in case of non-existing combination of port and pin numbers or improperly configured input pin.
 * \return nwTrue - The value in the input register corresponding to the provided pin number is 1.
 */
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

/**
 * \brief HAL function that can be used to toggle an already configured
 * GPIO pin. The function performs a validation for the existence of the provided combination of GPIO port and pin numbers for Infineon CAT1B devices.
 * \param portNum - The number of the desired GPIO port for the operation.
 * \param pinNum - The number of the desired GPIO pin to be toggled.
 * \return NW_GPIO_BAD_PARAM - The provided combination of port and pin number does not exist for the Infineon CAT1B device.
 * \return NW_GPIO_SUCCESS - The GPIO pin output is toggled.
 */
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Toggle(uint8 portNum, uint8 pinNum);

/**
 * \brief HAL function that can be used to initialize and enable an External Interrupt Request from a GPIO input pin.
 * The function performs a validation for the existence of the provided combination of GPIO port and pin numbers for Infineon CAT1B devices.
 * Furthermore, the functions is also performing a validation of the provided NexaWattGPIOExtIRQConfig External IRQ Configuration.
 * If validation passes, the configured External IRQ is initialized and enabled automatically. In case the Interrupt Request needs to be disabled,
 * the user is free to use both CMSIS core function or the provided NexaWatt_Hal_Infineon_Cat1B_Gpio_Disable_EXTI() function.
 * \param portNum - The number of the desired GPIO port for the operation.
 * \param pinNum - The number of the desired GPIO pin to be configured as External IRQ source.
 * \param extiConfig - A pointer, containing the framework's standardized GPIO External Interrupt Request configuration.
 * \return NW_GPIO_BAD_PARAM - The validation of the provided configuration failed. Please make sure that the combination of the port and pin number represents existing pin of the Infineon CAT1B devices.
 * Validate that the provided GPIO External Interrupt Request configuration is valid.
 * \return NW_GPIO_SUCCESS - The provided External Interrupt Request source is initialized and enabled.
 */
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Register_EXTI(uint8 portNum, uint8 pinNum, const NexaWattGPIOExtIRQConfig* extiConfig);

/**
 * \brief HAL function that can be used to disable an already initialized and enabled External Interrupt Request from a GPIO input pin.
 * The function performs a validation for the existence of the provided combination of GPIO port and pin numbers for Infineon CAT1B devices.
 * Furthermore, the functions is also performing a validation of the provided NexaWattGPIOExtIRQConfig External IRQ Configuration.
 * If validation passes, the configured External IRQ is disabled.
 * Please make sure to provide the NexaWattGPIOExtIRQConfig used for the initialization of the External Interrupt Request
 * or equivalent copy.
 * \param portNum - The number of the desired GPIO port for the operation.
 * \param pinNum - The number of the desired GPIO pin to be disabled from the External IRQ sources.
 * \param extiConfig - A pointer, containing the framework's standardized GPIO External Interrupt Request configuration.
 * \return NW_GPIO_BAD_PARAM - The validation of the provided configuration failed. Please make sure that the combination of the port and pin number represents existing pin of the Infineon CAT1B devices.
 * Validate that the provided GPIO External Interrupt Request configuration is valid.
 * \return NW_GPIO_SUCCESS - The provided External Interrupt Request source is disabled.
 */
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Disable_EXTI(uint8 portNum, uint8 pinNum, const NexaWattGPIOExtIRQConfig* extiConfig);

/**
 * \brief HAL function that can be used to check the status of an External Interrupt Request.
 * Note that the provided GPIO pin must be configured as an EXTI request for this function to work.
 * The function is also performing a validation for the existence of the provided combination of GPIO port and pin number for Infineon CAT1B devices.
 * \Note In many cases, the System Interrupt needs to be serviced as fast as possible in the ISR.
 * In these cases, the validation of the provided GPIO port and pin numbers may introduce undesirable overhead and loss of performance.
 * To deal with such situations, unsafe version of this function is provided.
 * \param portNum - The number of the desired GPIO port for the operation.
 * \param pinNum - The number of the desired GPIO pin for which the EXTI request status will be returned.
 * \return nwFalse - The EXTI request is not raised or the provided combination of GPIO port and pin is not existing.
 * \return nwTrue - The EXTI request is raised and waiting to be processed by application.
 */
NwGpioExtiStatus NexaWatt_Hal_Infineon_Cat1B_Gpio_Get_EXTI_Status(uint8 portNum, uint8 pinNum);

/**
 * \brief HAL function that can be used to check the status of an External Interrupt Request.
 * Note that the provided GPIO pin must be configured as an EXTI request for this function to work.
 * \Note In many cases, the System Interrupt needs to be serviced as fast as possible in the ISR.
 * This function is not performing any validation of the provided GPIO port and pin numbers to reduce overhead in the ISRs.
 * \param portNum - The number of the desired GPIO port for the operation.
 * \param pinNum - The number of the desired GPIO pin for which the EXTI request status will be returned.
 * \return nwFalse - The EXTI request is not raised.
 * \return nwTrue - The EXTI request is raised and waiting to be processed by application.
 */
NwGpioExtiStatus NexaWatt_Hal_Infineon_Cat1B_Gpio_Get_EXTI_Status_Unsafe(uint8 portNum, uint8 pinNum);

/**
 * \brief HAL function that can be used to clear the status of an External Interrupt Request.
 * Note that the provided GPIO pin must be configured as an EXTI request for this function to work.
 * The function is also performing a validation for the existence of the provided combination of GPIO port and pin number for Infineon CAT1B devices.
 * \Note In many cases, the System Interrupt needs to be serviced as fast as possible in the ISR.
 * In these cases, the validation of the provided GPIO port and pin numbers may introduce undesirable overhead and loss of performance.
 * To deal with such situations, unsafe version of this function is provided.
 * \param portNum - The number of the desired GPIO port for the operation.
 * \param pinNum - The number of the desired GPIO pin for which the EXTI request status will be cleared.
 * \return NW_GPIO_BAD_PARAM - The provided combination of GPIO port and pin number is not existing for Infineon CAT1B devices.
 * \return NW_GPIO_SUCCESS - The EXTI request status is cleared.
 */
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Clear_EXTI_Status(uint8 portNum, uint8 pinNum);

/**
 * \brief HAL function that can be used to clear the status of an External Interrupt Request.
 * Note that the provided GPIO pin must be configured as an EXTI request for this function to work.
 * \Note In many cases, the System Interrupt needs to be serviced as fast as possible in the ISR.
 * This function is not performing any validation of the provided GPIO port and pin numbers to reduce overhead in the ISRs.
 * \param portNum - The number of the desired GPIO port for the operation.
 * \param pinNum - The number of the desired GPIO pin for which the EXTI request status will be cleared.
 */
void NexaWatt_Hal_Infineon_Cat1B_Gpio_Clear_EXTI_Status_Unsafe(uint8 portNum, uint8 pinNum);

/**
 * \brief HAL function that can be used to perform SW triggering of an already
 * configured EXTI (External Interrupt Request). The function performs a validation for the existence of the provided combination of GPIO port and pin numbers for Infineon CAT1B devices.
 * The correctness of the configured interrupt mask in the GPIO Interrupt Mask registers is also validated. If the combination of GPIO port and pin numbers exists
 * and the interrupt mask is allowing the interrupt request on the corresponding pin, then an interrupt request will be raised to test the implemented ISR.
 * \param portNum - The number of the desired GPIO port for the operation.
 * \param pinNum - The number of the GPIO pin, whose EXTI capabilities will be tested.
 * \return NW_GPIO_BAD_PARAM - The provided combination of port and pin number does not exist for the Infineon CAT1B device or the configured interrupt mask of the GPIO port restricts the interrupt requests on the provided pin number. Please investigate the GPIO configuration.
 * \return NW_GPIO_SUCCESS - An IRQ is triggered for the provided pin number on the provided GPIO port number.
 */
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Trigger_Sw_EXTI(uint8 portNum, uint8 pinNum);

/*******************************************************************************
* Function Definitions
*******************************************************************************/

//#endif
#endif
