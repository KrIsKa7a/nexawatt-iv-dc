/*******************************************************************************
* File Name:   hal_context_export.h
*
* Description: This is the header file containing declarations and definitions,
* related to the HAL Context Export contract of the NexaWatt-IV.DC framework.
* The context is responsible for the storage of framework pre-defined/user-defines HAL functions.
* This header file is intended to provide the Export contract of the HAL Context software component
* and limit the access to the export context for the corresponding software component users.
*
* Related Document: See README.md
*
*******************************************************************************/

#ifndef NEXAWATT_IV_DC_HAL_CONTEXT_EXPORT_H
#define NEXAWATT_IV_DC_HAL_CONTEXT_EXPORT_H

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "hal_context.h"

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
NexaWattHalContextStatusResult NexaWatt_HalContext_Export_Init_Function(NexaWattHalContextInitFunctionTypes initFunctionType, NexaWattHalContextFunction* halContextFncPtr);
NexaWattHalContextStatusResult NexaWatt_HalContext_Export_Function(NexaWattHalContextFunctionTypes functionType, NexaWattHalContextFunction* halContextFncPtr);

/*******************************************************************************
* Function Definitions
*******************************************************************************/

#endif