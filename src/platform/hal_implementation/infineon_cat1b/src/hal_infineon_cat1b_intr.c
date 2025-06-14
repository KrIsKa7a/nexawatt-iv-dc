/*******************************************************************************
* File Name:   hal_infineon_cat1b_intr.c
*
* Description: This is the source file containing the implementation of the HAL
* for the System Interrupts initialization of the Infineon CAT1B devices.
* The NexaWatt-IV.DC framework offers custom implemented HAL for several Infineon devices.
* The implementation of the current HAL is dependent on the PDL, provided by Infineon Technologies.
*
* Related Document: See README.md
*
*******************************************************************************/

// TODO: Uncomment the pre-processor defence after development
// Prevents the compilation of the HAL Implementation in case of missing PDL
//#ifdef CY_SYSINT_H
/*******************************************************************************
* Header Files
*******************************************************************************/
#include "hal_infineon_cat1b_intr.h"
#include "cy_sysint.h"

/*******************************************************************************
* Macros
*******************************************************************************/
/**
 * \brief The minimum Interrupt Source number for the Infineon CAT1B devices.
 */
#define NW_HAL_INFINEON_CAT1B_INTR_SOURCE_MIN_NUM       (0u)

/**
 * \brief The maximum Interrupt Source number for the Infineon CAT1B devices.
 */
#define NW_HAL_INFINEON_CAT1B_INTR_SOURCE_MAX_NUM       (139u)

/**
 * \brief Special number indicating unconnected Interrupt Source.
 */
#define NW_HAL_INFINEON_CAT1B_INTR_UNCONNECTED          (240u)

/**
 * \brief Number corresponding to the maximum IRQ priority for the Infineon CAT1B devices.
 * Valid for all Armv8-M based MCUs.
 */
#define NW_HAL_INFINEON_CAT1B_INTR_HIGHEST_PRIO         (0u)

/**
 * \brief Number corresponding to the minimum IRQ priority for the Infineon CAT1B devices.
 * Valid for all Armv8-M based MCUs.
 */
#define NW_HAL_INFINEON_CAT1B_INTR_LOWEST_PRIO          (7u)
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
 * \brief Simple helper function that validates the provided NexaWattIntrInitConfig System Interrupt configuration
 * by the HAL user. The HAL will be used by the HAL Wrappers, hence the user of the HAL implementation will be NexaWatt-IV.DC framework.
 * The validation is performed in case the user decides to use the HAL implementation for other purposes.
 * \param intrConfig - A pointer, containing the framework's standardized System Interrupt configuration structure.
 * \return nwFalse - The provided Interrupt Source configuration is not valid. Please make sure that a corresponding ISR pointer is provided
 * and that the provided Interrupt Source Number and Priority are valid up to the defined limits for Infineon CAT1B devices.
 * \return nwTrue - The provided Interrupt Source configuration is valid.
 */
NW_LOCAL_INLINE nw_bool ValidateInterruptConfiguration(NexaWattIntrInitConfig* intrConfig);

/*******************************************************************************
* Function Definitions
*******************************************************************************/
NexaWattIntrInitStatus NexaWatt_Hal_Infineon_Cat1B_Intr_Init(NexaWattIntrInitConfig* intrConfig)
{
    NexaWattIntrInitStatus retRes = NW_HAL_INTR_INIT_FAILED;
    cy_en_sysint_status_t intrInitResult = CY_SYSINT_BAD_PARAM;
    cy_stc_sysint_t userIntrConfig;

    nw_bool intrConfigValidationResult = ValidateInterruptConfiguration(intrConfig);
    if (intrConfigValidationResult == nwTrue)
    {
        userIntrConfig.intrSrc = intrConfig->intrSource;
        userIntrConfig.intrPriority = intrConfig->intrPriority;

        intrInitResult = Cy_SysInt_Init(&userIntrConfig, intrConfig->intrHandlerPtr);
        if (intrInitResult == CY_SYSINT_SUCCESS)
        {
            if (intrConfig->intrSource)
            retRes = NW_HAL_INTR_INIT_SUCCESS;
        }
    }

    return retRes;
}

void NexaWatt_Hal_Infineon_Cat1B_Intr_Enable(NexaWattIntrInitConfig* intrConfig)
{
    nw_bool intrConfigValidationResult = ValidateInterruptConfiguration(intrConfig);
    if (intrConfigValidationResult == nwTrue)
    {
        NVIC_EnableIRQ(intrConfig->intrSource);
    }
}

void NexaWatt_Hal_Infineon_Cat1B_Intr_Disable(NexaWattIntrInitConfig* intrConfig)
{
    nw_bool intrConfigValidationResult = ValidateInterruptConfiguration(intrConfig);
    if (intrConfigValidationResult == nwTrue)
    {
        NVIC_DisableIRQ(intrConfig->intrSource);
    }
}

NW_LOCAL_INLINE nw_bool ValidateInterruptConfiguration(NexaWattIntrInitConfig* intrConfig)
{
    nw_bool validationResult = nwTrue;
    if (intrConfig == NULL)
    {
        // Interrupt configuration must be provided
        validationResult = nwFalse;
    }
    else if (intrConfig->intrHandlerPtr == NULL)
    {
        // Interrupt can't be initialized without pointer to the corresponding user-defined ISR
        validationResult = nwFalse;
    }
    else if ((intrConfig->intrSource < NW_HAL_INFINEON_CAT1B_INTR_SOURCE_MIN_NUM) ||
             ((intrConfig->intrSource > NW_HAL_INFINEON_CAT1B_INTR_SOURCE_MAX_NUM) &&
              (intrConfig->intrSource != NW_HAL_INFINEON_CAT1B_INTR_UNCONNECTED)))
    {
        // The provided Interrupt Source number is not a valid interrupt source
        validationResult = nwFalse;
    }
    else if ((intrConfig->intrPriority < NW_HAL_INFINEON_CAT1B_INTR_HIGHEST_PRIO) ||
             (intrConfig->intrPriority > NW_HAL_INFINEON_CAT1B_INTR_LOWEST_PRIO))
    {
        // The provided Interrupt Priority is not a valid interrupt priority
        // The interrupt priority on the Armv8-M devices is inverted:
        // 0 - Highest priority
        // 7 - Lowest priority
        validationResult = nwFalse;
    }

    return validationResult;
}