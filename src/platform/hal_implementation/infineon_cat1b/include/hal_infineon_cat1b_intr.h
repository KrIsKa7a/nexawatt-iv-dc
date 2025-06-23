/*******************************************************************************
* File Name:   hal_infineon_cat1b_intr.h
*
* Description: This is the header file containing declarations and definitions,
* related to the HAL implementation for the configuration of the IRQs and ISRs for
* the Infineon CAT1B devices. The NexaWatt-IV.DC framework offers custom implemented
* HAL for several Infineon devices. The implementation of the current HAL is dependent
* on the PDL, provided by Infineon Technologies.
* Note: The HAL implementation of the System Interrupts will be reused by the HAL implementations
* of the rest MCU peripherals, used by the framework. The System Interrupts HAL implementation will not
* be exposed to the user, nor registered in the HAL Context.
*
* Related Document: See README.md
*
*******************************************************************************/

#ifndef NEXAWATT_IV_DC_HAL_INFINEON_CAT1B_INTR_H
#define NEXAWATT_IV_DC_HAL_INFINEON_CAT1B_INTR_H

// TODO: Uncomment the pre-processor defence after development
// Prevents the compilation of the HAL Implementation in case of missing PDL
//#ifdef CY_SYSINT_H
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
typedef enum eNexaWattIntrInitStatus
{
    NW_HAL_INTR_INIT_SUCCESS = 0x00u,
    NW_HAL_INTR_INIT_FAILED = 0x01u,
} NexaWattIntrInitStatus;

typedef struct sNexaWattIntrInitConfig
{
    uint32 intrSource;
    NwInterruptPriority intrPriority;
    NwIsrPointerType intrHandlerPtr;
} NexaWattIntrInitConfig;

/*******************************************************************************
* Global Variables
*******************************************************************************/


/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
 * \brief HAL function that provides System Interrupt initialization using the framework standardized
 * configuration structures and types. The function performs validation of the provided System Interrupt configuration
 * and initializes the System Interrupt according to the provided configuration, if validated successfully.
 * Keep in mind that the System Interrupt is initialized, but not enabled after the successful function execution!
 * \param intrConfig - A pointer, containing the framework's standardized System Interrupt configuration structure.
 * \return NW_HAL_INTR_INIT_FAILED - The initialization of the provided System Interrupt configuration failed.
 * Please make sure that the provided System Interrupt configuration contains both valid ISR pointer and Interrupt Source Number/Priority,
 * according to the defined limits for Infineon CAT1B devices (Armv8-M).
 * \return NW_HAL_INTR_INIT_SUCCESS - The provided System Interrupt initialization was successful. The System Interrupt can now safely be
 * enabled either using the CMSIS or the HAL enable functions.
 */
NexaWattIntrInitStatus NexaWatt_Hal_Infineon_Cat1B_Intr_Init(const NexaWattIntrInitConfig* intrConfig);

/**
 * \brief HAL function that provides enabling of the System Interrupt using the framework standardized
 * configuration structures and types. The function performs validation of the provided System Interrupt configuration
 * and enables the System Interrupt, if validated successfully.
 * Keep in mind that the System Interrupt must be initialized before its enabling! If the System Interrupt is not initialized properly,
 * the function will silently enable the System Interrupt Source, but the ISR handler will not be working properly!
 * \param intrConfig - A pointer, containing the framework's standardized System Interrupt configuration structure.
 */
void NexaWatt_Hal_Infineon_Cat1B_Intr_Enable(const NexaWattIntrInitConfig* intrConfig);

/**
 * \brief HAL function that provides disabling of the System Interrupt using the framework standardized
 * configuration structures and types. The function performs validation of the provided System Interrupt configuration
 * and disables the System Interrupt, if validated successfully.
 * Keep in mind that the System Interrupt must be initialized and enabled before its disabling! If the System Interrupt is not initialized properly,
 * the function will silently disable the System Interrupt Source.
 * \param intrConfig - A pointer, containing the framework's standardized System Interrupt configuration structure.
 */
void NexaWatt_Hal_Infineon_Cat1B_Intr_Disable(const NexaWattIntrInitConfig* intrConfig);

/*******************************************************************************
* Function Definitions
*******************************************************************************/
#endif