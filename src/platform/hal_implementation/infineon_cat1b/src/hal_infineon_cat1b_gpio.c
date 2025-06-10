/*******************************************************************************
* File Name:   hal_infineon_cat1b_gpio.h
*
* Description: This is the source file containing the implementation of the HAL
* for the GPIO peripheral of the Infineon CAT1B devices.
* The NexaWatt-IV.DC framework offers custom implemented HAL for several Infineon devices.
* The implementation of the current HAL is dependent on the PDL, provided by Infineon Technologies.
*
* Related Document: See README.md
*
*******************************************************************************/

// TODO: Uncomment the pre-processor defence after development
// Prevents the compilation of the HAL Implementation in case of missing PDL
//#ifdef CY_GPIO_H
/*******************************************************************************
* Header Files
*******************************************************************************/
#include "hal_infineon_cat1b_gpio.h"
#include "cy_gpio.h"

/*******************************************************************************
* Macros
*******************************************************************************/
/**
 * \brief Maximum number of ports for Infineon CAT1B devices.
 */
#define NW_HAL_INFINEON_CAT1B_GPIO_PORT_CNT            (10u)

/**
 * \brief Maximum number of pins per port for Infineon CAT1B devices.
 */
#define NW_HAL_INFINEON_CAT1B_GPIO_PORT_PIN_CNT        (8u)

/**
 * \brief Default value for the unused SIO registers of the GPIO.
 */
#define NW_HAL_INFINEON_CAT1B_GPIO_SIO_REG_DEF_VAL     (0x00u)

/**
 * \brief Interrupt mask disabling all EXTI request on the GPIO port.
 */
#define NW_HAL_INFINEON_CAT1B_GPIO_INTR_DISABLED_MASK  (0x00u)

/**
 * \brief Macro returning the corresponding GPIO port base to a provided GPIO port number.
 */
#define NW_HAL_INFINEON_CAT1B_GPIO_GET_PORT_BASE(portNum) \
    (gpioPortBases[portNum])

/**
 * \brief Macro performing a calculation of the corresponding interrupt mask to a GPIO pin.
 */
#define NW_HAL_INFINEON_CAT1B_GPIO_GET_PIN_INTR_MASK(pinNum) \
    (0x01u << pinNum)
/*******************************************************************************
* Type definitions
*******************************************************************************/

/*******************************************************************************
* Local Variables
*******************************************************************************/
/**
 * \brief Array containing mapping between the port number (index) and the port
 * base in the GPIO peripheral address space.
 */
static GPIO_PRT_Type* gpioPortBases[] =
{
    P0_0_PORT,
    P1_0_PORT,
    P2_0_PORT,
    P3_0_PORT,
    P4_0_PORT,
    P5_0_PORT,
    P6_0_PORT,
    P7_0_PORT,
    P8_0_PORT,
    P9_0_PORT
};

/**
 * \brief Array containing mapping between the framework standardized NexaWattGPIOPinDriveMode
 * drive modes of GPIO pin and the allowed drive modes for the input pins of the Infineon CAT1B devices.
 */
static uint32 inputDriveModesMap[] =
{
    CY_GPIO_DM_STRONG,
    CY_GPIO_DM_PULLUP,
    CY_GPIO_DM_PULLDOWN,
    CY_GPIO_DM_OD_DRIVESLOW,
    CY_GPIO_DM_OD_DRIVESHIGH,
    CY_GPIO_DM_HIGHZ,
    CY_GPIO_DM_ANALOG,
};

/**
 * \brief Array containing mapping between the framework standardized NexaWattGPIOPinDriveMode
 * drive modes of GPIO pin and the allowed drive modes for the output pins of the Infineon CAT1B devices.
 */
static uint32 outputDriveModesMap[] =
{
    CY_GPIO_DM_STRONG_IN_OFF,
    CY_GPIO_DM_PULLUP_IN_OFF,
    CY_GPIO_DM_PULLDOWN_IN_OFF,
    CY_GPIO_DM_OD_DRIVESLOW_IN_OFF,
    CY_GPIO_DM_OD_DRIVESHIGH_IN_OFF,
    CY_GPIO_DM_HIGHZ,
};

/*******************************************************************************
* Local Function Prototypes
*******************************************************************************/
/**
 * \brief Simple helper function that validates the provided NexaWattGPIOPinConfig pin configuration
 * by the HAL user. The HAL will be used by the HAL Wrappers, hence the user of the HAL implementation will be NexaWatt-IV.DC framework.
 * The validation is performed in case the user decides to use the HAL implementation for other purposes.
 * \param portNum - The number of the configured GPIO port.
 * \param pinNum - The number of the configured GPIO port pin.
 * \param pinConfig - A pointer, containing the framework's standardized GPIO pin configuration structure.
 * \return nwTrue - Validation is performed and the configuration is correct.
 * \return nwFalse - Validation is performed, but the configuration contains incorrect data.
 * Please make sure to pass existing port/pin numbers and use the provided enumerations from the framework.
 */
NW_LOCAL_INLINE nw_bool NexaWatt_Hal_Infineon_Cat1B_Gpio_Validate_User_Pin_Config(uint8 portNum, uint8 pinNum, const NexaWattGPIOPinConfig* pinConfig);

/**
 * \brief Simple helper function that validates the provided port and pin numbers, according
 * to the Infineon CAT1B devices data. The HAL will be used by the HAL Wrappers,
 * hence the user of the HAL implementation will be NexaWatt-IV.DC framework.
 * The validation is performed in case the user decides to use the HAL implementation for other purposes.
 * \param portNum - The number of the validated GPIO port.
 * \param pinNum - The number of the validated GPIO port pin.
 * \return nwTrue - Validation is performed and the pin is existing.
 * \return nwFalse - Validation is performed, but the pin does not exist for the Infineon CAT1B devices.
 */
NW_LOCAL_INLINE nw_bool NexaWatt_Hal_Infineon_Cat1B_Gpio_Validate_Port_And_Pin(uint8 portNum, uint8 pinNum);

/*******************************************************************************
* Function Definitions
*******************************************************************************/
NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Init_Digital_Pin(const uint8 portNum, const uint8 pinNum, const NexaWattGPIOPinConfig* const pinConfig)
{
    // Variables are declared in the beginning of the function to ensure constant memory usage
    NexaWattGPIOStatusResult retRes = NW_GPIO_BAD_PARAM;
    cy_stc_gpio_pin_config_t userPinConfig;
    cy_en_gpio_status_t gpioInitRes;
    uint32 initVal = 0x00u;
    uint32 driveMode = 0x01u;

    nw_bool isUserConfigValid =
            NexaWatt_Hal_Infineon_Cat1B_Gpio_Validate_User_Pin_Config(portNum, pinNum, pinConfig);

    if (isUserConfigValid == nwTrue)
    {
        initVal = (pinConfig->initVal == nwFalse) ?
                  0u : 1u;
        driveMode = (pinConfig->direction == NW_GPIO_INPUT) ?
                    inputDriveModesMap[pinConfig->driveMode] : outputDriveModesMap[pinConfig->driveMode];

        userPinConfig.outVal = initVal;
        userPinConfig.driveMode = driveMode;
        userPinConfig.hsiom = pinConfig->altFunction;
        userPinConfig.intEdge = NW_HAL_INFINEON_CAT1B_GPIO_SIO_REG_DEF_VAL;
        userPinConfig.intMask = NW_HAL_INFINEON_CAT1B_GPIO_INTR_DISABLED_MASK;
        userPinConfig.vtrip = CY_GPIO_VTRIP_CMOS;
        userPinConfig.slewRate = pinConfig->driveSpeed;
        userPinConfig.driveSel = pinConfig->driveStrength;
        userPinConfig.vregEn = NW_HAL_INFINEON_CAT1B_GPIO_SIO_REG_DEF_VAL;
        userPinConfig.ibufMode = NW_HAL_INFINEON_CAT1B_GPIO_SIO_REG_DEF_VAL;
        userPinConfig.vtripSel = NW_HAL_INFINEON_CAT1B_GPIO_SIO_REG_DEF_VAL;
        userPinConfig.vrefSel = NW_HAL_INFINEON_CAT1B_GPIO_SIO_REG_DEF_VAL;
        userPinConfig.vohSel = NW_HAL_INFINEON_CAT1B_GPIO_SIO_REG_DEF_VAL;
        userPinConfig.nonSec = NW_HAL_INFINEON_CAT1B_GPIO_SIO_REG_DEF_VAL;

        gpioInitRes = Cy_GPIO_Pin_Init(NW_HAL_INFINEON_CAT1B_GPIO_GET_PORT_BASE(portNum), pinNum, &userPinConfig);
        if (gpioInitRes == CY_GPIO_SUCCESS)
        {
            retRes = NW_GPIO_SUCCESS;
        }
    }

    return retRes;
}

NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Set_Pin_Alt_Functions(const uint8 portNum, const uint8 pinNum, const NwGpioPinAltFunction altFunction)
{
    NexaWattGPIOStatusResult retRes = NW_GPIO_BAD_PARAM;

    nw_bool gpioPinExists =
            NexaWatt_Hal_Infineon_Cat1B_Gpio_Validate_Port_And_Pin(portNum, pinNum);
    if (gpioPinExists == nwTrue)
    {
        Cy_GPIO_SetHSIOM(NW_HAL_INFINEON_CAT1B_GPIO_GET_PORT_BASE(portNum), pinNum, altFunction);

        retRes = NW_GPIO_SUCCESS;
    }

    return retRes;
}

NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_DeInit_Port(const uint8 portNum)
{
    NexaWattGPIOStatusResult retRes = NW_GPIO_BAD_PARAM;

    nw_bool gpioPinExists =
            NexaWatt_Hal_Infineon_Cat1B_Gpio_Validate_Port_And_Pin(portNum, NW_HAL_INFINEON_CAT1B_GPIO_SIO_REG_DEF_VAL);
    if (gpioPinExists == nwTrue)
    {
        Cy_GPIO_Port_Deinit(NW_HAL_INFINEON_CAT1B_GPIO_GET_PORT_BASE(portNum));

        retRes = NW_GPIO_SUCCESS;
    }

    return retRes;
}

NwGpioPinResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Read(const uint8 portNum, const uint8 pinNum)
{
    NwGpioPinResult pinRes = nwFalse;
    uint32 gpioPinRegRes = 0u;

    nw_bool gpioPinExists =
            NexaWatt_Hal_Infineon_Cat1B_Gpio_Validate_Port_And_Pin(portNum, pinNum);
    if (gpioPinExists == nwTrue)
    {
        // Defensive programming in case the PDL returns unexpected value that can't be safely cast
        gpioPinRegRes = Cy_GPIO_Read(NW_HAL_INFINEON_CAT1B_GPIO_GET_PORT_BASE(portNum), pinNum);
        if (gpioPinRegRes == 1)
        {
            pinRes = nwTrue;
        }
    }

    return pinRes;
}

NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Write(const uint8 portNum, const uint8 pinNum, const nw_bool value)
{
    NexaWattGPIOStatusResult retRes = NW_GPIO_BAD_PARAM;

    nw_bool gpioPinExists =
            NexaWatt_Hal_Infineon_Cat1B_Gpio_Validate_Port_And_Pin(portNum, pinNum);
    if (gpioPinExists == nwTrue)
    {
        Cy_GPIO_Write(NW_HAL_INFINEON_CAT1B_GPIO_GET_PORT_BASE(portNum), pinNum, ((uint32)value));

        retRes = NW_GPIO_SUCCESS;
    }

    return retRes;
}

NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Toggle(const uint8 portNum, const uint8 pinNum)
{
    NexaWattGPIOStatusResult retRes = NW_GPIO_BAD_PARAM;

    nw_bool gpioPinExists =
            NexaWatt_Hal_Infineon_Cat1B_Gpio_Validate_Port_And_Pin(portNum, pinNum);
    if (gpioPinExists == nwTrue)
    {
        Cy_GPIO_Inv(NW_HAL_INFINEON_CAT1B_GPIO_GET_PORT_BASE(portNum), pinNum);

        retRes = NW_GPIO_SUCCESS;
    }

    return retRes;
}

NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Register_EXTI(const uint8 portNum, const uint8 pinNum, const NexaWattGPIOInterruptEdgeEXTI intrEdge, void (*const isrHandlerPtr)(void))
{
    return NW_GPIO_FATAL_ERR;
}

NexaWattGPIOStatusResult NexaWatt_Hal_Infineon_Cat1B_Gpio_Trigger_Sw_EXTI(const uint8 portNum, const uint8 pinNum)
{
    NexaWattGPIOStatusResult retRes = NW_GPIO_BAD_PARAM;
    NwInterruptMask gpioPortIntrMask = NW_HAL_INFINEON_CAT1B_GPIO_INTR_DISABLED_MASK;

    nw_bool gpioPinExists =
            NexaWatt_Hal_Infineon_Cat1B_Gpio_Validate_Port_And_Pin(portNum, pinNum);
    if (gpioPinExists == nwTrue)
    {
        gpioPortIntrMask = Cy_GPIO_GetInterruptMask(NW_HAL_INFINEON_CAT1B_GPIO_GET_PORT_BASE(portNum), pinNum);
        if ((gpioPortIntrMask & NW_HAL_INFINEON_CAT1B_GPIO_GET_PIN_INTR_MASK(pinNum)) != NW_HAL_INFINEON_CAT1B_GPIO_INTR_DISABLED_MASK)
        {
            Cy_GPIO_SetSwInterrupt(NW_HAL_INFINEON_CAT1B_GPIO_GET_PORT_BASE(portNum), pinNum);

            retRes = NW_GPIO_SUCCESS;
        }
    }

    return retRes;
}

NW_LOCAL_INLINE nw_bool NexaWatt_Hal_Infineon_Cat1B_Gpio_Validate_User_Pin_Config(const uint8 portNum, const uint8 pinNum, const NexaWattGPIOPinConfig* const pinConfig)
{
    // The validation is performed in several logical branches to increase the code readability
    // The compiler will optimize the below code
    nw_bool validationRes =
            NexaWatt_Hal_Infineon_Cat1B_Gpio_Validate_Port_And_Pin(portNum, pinNum);
    if (pinConfig == NULL)
    {
        // Pin configuration is not provided by the user
        validationRes = nwFalse;
    }
    else if ((pinConfig->direction > NW_GPIO_OUTPUT) ||
             (pinConfig->driveMode > NW_GPIO_DM_ANALOG) ||
             (pinConfig->driveSpeed > NW_GPIO_DS_SLOW) ||
             (pinConfig->driveStrength > NW_GPIO_DSTR_QUARTER))
    {
        // Invalid values for the pin configuration are provided
        validationRes = nwFalse;
    }
    else if ((pinConfig->direction == NW_GPIO_OUTPUT) &&
             (pinConfig->driveMode == NW_GPIO_DM_ANALOG))
    {
        // Incorrect configuration, as GPIO output pins cannot be analog
        validationRes = nwFalse;
    }

    return validationRes;
}

NW_LOCAL_INLINE nw_bool NexaWatt_Hal_Infineon_Cat1B_Gpio_Validate_Port_And_Pin(const uint8 portNum, const uint8 pinNum)
{
    nw_bool validationRes = nwTrue;
    if ((portNum >= NW_HAL_INFINEON_CAT1B_GPIO_PORT_CNT) ||
        (pinNum >= NW_HAL_INFINEON_CAT1B_GPIO_PORT_PIN_CNT))
    {
        // Invalid port or pin number provided for CAT1B device
        validationRes = nwFalse;
    }

    return validationRes;
}
//#endif
