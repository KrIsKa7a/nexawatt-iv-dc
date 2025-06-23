/*******************************************************************************
* File Name:   hal_wrapper_gpio.c
*
* Description: This is the source file containing definitions,
* related to the HAL Wrapper for the GPIO peripheral. This wrapper is directly
* used by the NexaWattIV.DC framework and aims to provide maximum level of
* abstraction on the used MCU.
*
* Note: This file contains generated source code. Use at own risk!
*
* Related Document: See README.md
*
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "hal_wrapper_gpio.h"
#include "hal_context_export.h"

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
/**
 * \brief Simple helper function, used to reduce the code duplication across the HAL Wrapper GPIO implementation.
 * The function performs an export of the bind HAL Init Function in the HAL Context component and validates the export result.
 * In case of successful export, the HAL Context Function Config Callout is being executed.
 * \param initFncType - An enumeration, representing the framework's standardized HAL Initialization functions supported.
 * \param halContextFncConfig - A pointer, containing the framework's standardized HAL Context Function configuration structure.
 * \return NW_HAL_CONTEXT_BAD_PARAM - The validation of the provided parameters failed. Please make sure to provide non NULL NexaWattHalContextFunction pointer and valid NexaWattHalContextInitFunctionType.
 * \return NW_HAL_CONTEXT_NOT_FOUND - The validation of the provided parameters was successful, but such Initialization function is not bind in the HAL Context component.
 * The user is responsible to make sure to bind the appropriate HAL function implementations in case of using device, whose HAL is not provided by the framework.
 * \return NW_HAL_CONTEXT_OK - The validation of the provided parameters was successful. The HAL Context Initialization function is exported. The configured callout function is executed.
 */
NW_LOCAL_INLINE NexaWattHalContextStatusResult NexaWatt_HalWrapperGpio_Handle_Common_Init_Fnc_Exec_Seq(NexaWattHalContextInitFunctionTypes initFncType, NexaWattHalContextFunction *halContextFncConfig);

/**
 * \brief Simple helper function, used to reduce the code duplication across the HAL Wrapper GPIO implementation.
 * The function performs an export of the bind HAL Function in the HAL Context component and validates the export result.
 * In case of successful export, the HAL Context Function Config Callout is being executed.
 * \param halFncType - An enumeration, representing the framework's standardized HAL Functions supported.
 * \param halContextFncConfig - A pointer, containing the framework's standardized HAL Context Function configuration structure.
 * \return NW_HAL_CONTEXT_BAD_PARAM - The validation of the provided parameters failed. Please make sure to provide non NULL NexaWattHalContextFunction pointer and valid NexaWattHalContextFunctionType.
 * \return NW_HAL_CONTEXT_NOT_FOUND - The validation of the provided parameters was successful, but such HAL function is not bind in the HAL Context component.
 * The user is responsible to make sure to bind the appropriate HAL function implementations in case of using device, whose HAL is not provided by the framework.
 * \return NW_HAL_CONTEXT_OK - The validation of the provided parameters was successful. The HAL Context function is exported. The configured callout function is executed.
 */
NW_LOCAL_INLINE NexaWattHalContextStatusResult NexaWatt_HalWrapperGpio_Handle_Common_Hal_Fnc_Exec_Seq(NexaWattHalContextFunctionTypes halFncType, NexaWattHalContextFunction *halContextFncConfig);

/*******************************************************************************
* Function Definitions
*******************************************************************************/
NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Init_Digital_Pin(const uint8 portNum, const uint8 pinNum, const NexaWattGPIOPinConfig* const pinConfig)
{
    NexaWattGPIOStatusResult retRes = NW_GPIO_BAD_PARAM;
    NexaWattHalContextFunction gpioPinInitFncConfig;
    NexaWattGPIOStatusResult (*gpioPinInitFncPtrCasted)(const uint8, const uint8, const NexaWattGPIOPinConfig* const);

    NexaWattHalContextStatusResult gpioPinInitFcnExportRes =
            NexaWatt_HalWrapperGpio_Handle_Common_Init_Fnc_Exec_Seq(NW_HAL_GPIO_DIGITAL_IO_PIN_INIT,
                                                                    &gpioPinInitFncConfig);
    if (gpioPinInitFcnExportRes == NW_HAL_CONTEXT_OK)
    {
        gpioPinInitFncPtrCasted = (NexaWattGPIOStatusResult (*)(const uint8, const uint8, const NexaWattGPIOPinConfig* const))gpioPinInitFncConfig.fncPtr;
        retRes = gpioPinInitFncPtrCasted(portNum, pinNum, pinConfig);

        if (gpioPinInitFncConfig.fncCallback != NULL)
        {
            gpioPinInitFncConfig.fncCallback();
        }
    }

    return retRes;
}

NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Set_Pin_Alt_Functions(const uint8 portNum, const uint8 pinNum, const NwGpioPinAltFunction altFunction)
{
    NexaWattGPIOStatusResult retRes = NW_GPIO_BAD_PARAM;
    NexaWattHalContextFunction gpioPinSetAltFuncFncConfig;
    NexaWattGPIOStatusResult (*gpioPinSetAltFuncFncPtrCasted)(const uint8, const uint8, const NwGpioPinAltFunction);

    NexaWattHalContextStatusResult gpioPinSetAltFuncExportRes =
            NexaWatt_HalWrapperGpio_Handle_Common_Hal_Fnc_Exec_Seq(NW_HAL_GPIO_PIN_SET_ALT_FNC, &gpioPinSetAltFuncFncConfig);
    if (gpioPinSetAltFuncExportRes == NW_HAL_CONTEXT_OK)
    {
        gpioPinSetAltFuncFncPtrCasted = (NexaWattGPIOStatusResult (*)(const uint8, const uint8, const NwGpioPinAltFunction))gpioPinSetAltFuncFncConfig.fncPtr;
        retRes = gpioPinSetAltFuncFncPtrCasted(portNum, pinNum, altFunction);

        if (gpioPinSetAltFuncFncConfig.fncCallback != NULL)
        {
            gpioPinSetAltFuncFncConfig.fncCallback();
        }
    }

    return retRes;
}

NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_DeInit_Port(const uint8 portNum)
{
    NexaWattGPIOStatusResult retRes = NW_GPIO_BAD_PARAM;
    NexaWattHalContextFunction gpioPinDeInitFncConfig;
    NexaWattGPIOStatusResult (*gpioPinDeInitFncPtrCasted)(const uint8);

    NexaWattHalContextStatusResult gpioPinDeInitExportRes =
            NexaWatt_HalWrapperGpio_Handle_Common_Init_Fnc_Exec_Seq(NW_HAL_GPIO_DIGITAL_IO_PIN_DEINIT,
                                                                    &gpioPinDeInitFncConfig);
    if (gpioPinDeInitExportRes == NW_HAL_CONTEXT_OK)
    {
        gpioPinDeInitFncPtrCasted = (NexaWattGPIOStatusResult (*)(const uint8))gpioPinDeInitFncConfig.fncPtr;
        retRes = gpioPinDeInitFncPtrCasted(portNum);

        if (gpioPinDeInitFncConfig.fncCallback != NULL)
        {
            gpioPinDeInitFncConfig.fncCallback();
        }
    }

    return retRes;
}

NwGpioPinResult NexaWatt_HalWrapperGpio_Pin_Read(const uint8 portNum, const uint8 pinNum)
{
    NwGpioPinResult retRes = nwFalse;
    NexaWattHalContextFunction gpioPinReadFncConfig;
    NwGpioPinResult (*gpioPinReadFncPtrCasted)(const uint8, const uint8);

    NexaWattHalContextStatusResult gpioPinReadExportRes =
            NexaWatt_HalWrapperGpio_Handle_Common_Hal_Fnc_Exec_Seq(NW_HAL_GPIO_PIN_READ, &gpioPinReadFncConfig);
    if (gpioPinReadExportRes == NW_HAL_CONTEXT_OK)
    {
        gpioPinReadFncPtrCasted = (NwGpioPinResult (*)(const uint8, const uint8))gpioPinReadFncConfig.fncPtr;
        retRes = gpioPinReadFncPtrCasted(portNum, pinNum);

        if (gpioPinReadFncConfig.fncCallback != NULL)
        {
            gpioPinReadFncConfig.fncCallback();
        }
    }

    return retRes;
}

NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Pin_Write(const uint8 portNum, const uint8 pinNum, const nw_bool value)
{
    NexaWattGPIOStatusResult retRes = NW_GPIO_BAD_PARAM;
    NexaWattHalContextFunction gpioPinWriteFncConfig;
    NexaWattGPIOStatusResult (*gpioPinWriteFncPtrCasted)(const uint8, const uint8, nw_bool);

    NexaWattHalContextStatusResult gpioPinWriteExportRes =
            NexaWatt_HalWrapperGpio_Handle_Common_Hal_Fnc_Exec_Seq(NW_HAL_GPIO_PIN_WRITE, &gpioPinWriteFncConfig);
    if (gpioPinWriteExportRes == NW_HAL_CONTEXT_OK)
    {
        gpioPinWriteFncPtrCasted = (NexaWattGPIOStatusResult (*)(const uint8, const uint8, nw_bool))gpioPinWriteFncConfig.fncPtr;
        retRes = gpioPinWriteFncPtrCasted(portNum, pinNum, value);

        if (gpioPinWriteFncConfig.fncCallback != NULL)
        {
            gpioPinWriteFncConfig.fncCallback();
        }
    }

    return retRes;
}

NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Pin_Toggle(const uint8 portNum, const uint8 pinNum)
{
    NexaWattGPIOStatusResult retRes = NW_GPIO_BAD_PARAM;
    NexaWattHalContextFunction gpioPinToggleFncConfig;
    NexaWattGPIOStatusResult (*gpioPinToggleFncPtrCasted)(const uint8, const uint8);

    NexaWattHalContextStatusResult gpioPinToggleExportRes =
            NexaWatt_HalWrapperGpio_Handle_Common_Hal_Fnc_Exec_Seq(NW_HAL_GPIO_PIN_TOGGLE, &gpioPinToggleFncConfig);
    if (gpioPinToggleExportRes == NW_HAL_CONTEXT_OK)
    {
        gpioPinToggleFncPtrCasted = (NexaWattGPIOStatusResult (*)(const uint8, const uint8))gpioPinToggleFncConfig.fncPtr;
        retRes = gpioPinToggleFncPtrCasted(portNum, pinNum);

        if (gpioPinToggleFncConfig.fncCallback != NULL)
        {
            gpioPinToggleFncConfig.fncCallback();
        }
    }

    return retRes;
}

NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Register_EXTI(const uint8 portNum, const uint8 pinNum, const NexaWattGPIOExtIRQConfig* const extiConfig)
{
    NexaWattGPIOStatusResult retRes = NW_GPIO_BAD_PARAM;
    NexaWattHalContextFunction gpioRegisterExtIrqFncConfig;
    NexaWattGPIOStatusResult (*gpioRegisterExtIrqFncPtrCasted)(const uint8, const uint8, const NexaWattGPIOExtIRQConfig* const);

    NexaWattHalContextStatusResult gpioRegisterExtIrqExportRes =
            NexaWatt_HalWrapperGpio_Handle_Common_Hal_Fnc_Exec_Seq(NW_HAL_GPIO_REGISTER_EXTI, &gpioRegisterExtIrqFncConfig);
    if (gpioRegisterExtIrqExportRes == NW_HAL_CONTEXT_OK)
    {
        gpioRegisterExtIrqFncPtrCasted = (NexaWattGPIOStatusResult (*)(const uint8, const uint8, const NexaWattGPIOExtIRQConfig* const))gpioRegisterExtIrqFncConfig.fncPtr;
        retRes = gpioRegisterExtIrqFncPtrCasted(portNum, pinNum, extiConfig);

        if (gpioRegisterExtIrqFncConfig.fncCallback != NULL)
        {
            gpioRegisterExtIrqFncConfig.fncCallback();
        }
    }

    return retRes;
}

NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Disable_EXTI(const uint8 portNum, const uint8 pinNum, const NexaWattGPIOExtIRQConfig* extiConfig)
{
    NexaWattGPIOStatusResult retRes = NW_GPIO_BAD_PARAM;
    NexaWattHalContextFunction gpioDisableExtIrqFncConfig;
    NexaWattGPIOStatusResult (*gpioDisableExtIrqFncPtrCasted)(const uint8, const uint8, const NexaWattGPIOExtIRQConfig* const);

    NexaWattHalContextStatusResult gpioDisableExtIrqExportRes =
            NexaWatt_HalWrapperGpio_Handle_Common_Hal_Fnc_Exec_Seq(NW_HAL_GPIO_DISABLE_EXTI, &gpioDisableExtIrqFncConfig);
    if (gpioDisableExtIrqExportRes == NW_HAL_CONTEXT_OK)
    {
        gpioDisableExtIrqFncPtrCasted = (NexaWattGPIOStatusResult (*)(const uint8, const uint8, const NexaWattGPIOExtIRQConfig* const))gpioDisableExtIrqFncConfig.fncPtr;
        retRes = gpioDisableExtIrqFncPtrCasted(portNum, pinNum, extiConfig);

        if (gpioDisableExtIrqFncConfig.fncCallback != NULL)
        {
            gpioDisableExtIrqFncConfig.fncCallback();
        }
    }

    return retRes;
}

NwGpioExtiStatus NexaWatt_HalWrapperGpio_Get_EXTI_Status(const uint8 portNum, const uint8 pinNum)
{
    NwGpioExtiStatus retRes = nwFalse;
    NexaWattHalContextFunction gpioGetExtIrqStatusFncConfig;
    NwGpioExtiStatus (*gpioGetExtIrqStatusFncPtrCasted)(const uint8, const uint8);

    NexaWattHalContextStatusResult gpioGetExtIrqStatusExportRes =
            NexaWatt_HalWrapperGpio_Handle_Common_Hal_Fnc_Exec_Seq(NW_HAL_GPIO_GET_EXTI_STAT, &gpioGetExtIrqStatusFncConfig);
    if (gpioGetExtIrqStatusExportRes == NW_HAL_CONTEXT_OK)
    {
        gpioGetExtIrqStatusFncPtrCasted = (NwGpioExtiStatus (*)(const uint8, const uint8))gpioGetExtIrqStatusFncConfig.fncPtr;
        retRes = gpioGetExtIrqStatusFncPtrCasted(portNum, pinNum);

        if (gpioGetExtIrqStatusFncConfig.fncCallback != NULL)
        {
            gpioGetExtIrqStatusFncConfig.fncCallback();
        }
    }

    return retRes;
}

void NexaWatt_HalWrapperGpio_Clear_EXTI_Status(uint8 portNum, uint8 pinNum)
{
    NexaWattHalContextFunction gpioClearExtIrqStatusFncConfig;
    void (*gpioClearExtIrqStatusFncPtrCasted)(const uint8, const uint8);

    NexaWattHalContextStatusResult gpioClearExtIrqStatusExportRes =
            NexaWatt_HalWrapperGpio_Handle_Common_Hal_Fnc_Exec_Seq(NW_HAL_GPIO_CLEAR_EXTI_STAT, &gpioClearExtIrqStatusFncConfig);
    if (gpioClearExtIrqStatusExportRes == NW_HAL_CONTEXT_OK)
    {
        gpioClearExtIrqStatusFncPtrCasted = (void (*)(const uint8, const uint8))gpioClearExtIrqStatusFncConfig.fncPtr;
        gpioClearExtIrqStatusFncPtrCasted(portNum, pinNum);

        if (gpioClearExtIrqStatusFncConfig.fncCallback != NULL)
        {
            gpioClearExtIrqStatusFncConfig.fncCallback();
        }
    }
}

NexaWattGPIOStatusResult NexaWatt_HalWrapperGpio_Trigger_Sw_EXTI(const uint8 portNum, const uint8 pinNum)
{
    NexaWattGPIOStatusResult retRes = NW_GPIO_BAD_PARAM;
    NexaWattHalContextFunction gpioTriggerSwExtiFncConfig;
    NexaWattGPIOStatusResult (*gpioTriggerSwExtiFncPtrCasted)(const uint8, const uint8);

    NexaWattHalContextStatusResult gpioTriggerSwExtiExportRes =
            NexaWatt_HalWrapperGpio_Handle_Common_Hal_Fnc_Exec_Seq(NW_HAL_GPIO_TRIGGER_SW_INTR, &gpioTriggerSwExtiFncConfig);
    if (gpioTriggerSwExtiExportRes == NW_HAL_CONTEXT_OK)
    {
        gpioTriggerSwExtiFncPtrCasted = (NexaWattGPIOStatusResult (*)(const uint8, const uint8))gpioTriggerSwExtiFncConfig.fncPtr;
        retRes = gpioTriggerSwExtiFncPtrCasted(portNum, pinNum);

        if (gpioTriggerSwExtiFncConfig.fncCallback != NULL)
        {
            gpioTriggerSwExtiFncConfig.fncCallback();
        }
    }

    return retRes;
}

NW_LOCAL_INLINE NexaWattHalContextStatusResult NexaWatt_HalWrapperGpio_Handle_Common_Init_Fnc_Exec_Seq(
        NexaWattHalContextInitFunctionTypes initFncType, NexaWattHalContextFunction *halContextFncConfig)
{
    NexaWattHalContextStatusResult retRes = NW_HAL_CONTEXT_BAD_PARAM;

    // Static analysis warning: Condition is always true
    // Justification: Defensive programming style in case of misuse by the framework user
    if (initFncType < NW_HAL_INIT_FUNC_INVALID)
    {
        retRes = NexaWatt_HalContext_Export_Init_Function(initFncType, halContextFncConfig);
        if (retRes == NW_HAL_CONTEXT_OK)
        {
            // Trigger fault in case the function is not bind
            NW_ASSERT(halContextFncConfig->fncPtr != NULL);

            if (halContextFncConfig->fncCallout != NULL)
            {
                halContextFncConfig->fncCallout();
            }
        }
    }

    return retRes;
}

NW_LOCAL_INLINE NexaWattHalContextStatusResult NexaWatt_HalWrapperGpio_Handle_Common_Hal_Fnc_Exec_Seq(
        NexaWattHalContextFunctionTypes halFncType, NexaWattHalContextFunction *halContextFncConfig)
{
    NexaWattHalContextStatusResult retRes = NW_HAL_CONTEXT_BAD_PARAM;

    // Static analysis warning: Condition is always true
    // Justification: Defensive programming style in case of misuse by the framework user
    if (halFncType < NW_HAL_FUNC_INVALID)
    {
        retRes = NexaWatt_HalContext_Export_Function(halFncType, halContextFncConfig);
        if (retRes == NW_HAL_CONTEXT_OK)
        {
            // Trigger fault in case the function is not bind
            NW_ASSERT(halContextFncConfig->fncPtr != NULL);

            if (halContextFncConfig->fncCallout != NULL)
            {
                halContextFncConfig->fncCallout();
            }
        }
    }

    return retRes;
}