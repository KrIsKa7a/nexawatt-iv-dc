/*******************************************************************************
* File Name:   hal_context_bind.h
*
* Description: This is the header file containing declarations and definitions,
* related to the HAL Context Bind contract of the NexaWatt-IV.DC framework.
* The context is responsible for the storage of framework pre-defined/user-defines HAL functions.
* This header file is intended to provide the Bind contract of the HAL Context software component
* and limit the access to the bind context for the corresponding software component users.
*
* Related Document: See README.md
*
*******************************************************************************/

#ifndef NEXAWATT_IV_DC_HAL_CONTEXT_BIND_H
#define NEXAWATT_IV_DC_HAL_CONTEXT_BIND_H

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

NexaWattHalContextStatusResult NexaWatt_HalContext_Bind_Init_Function(NexaWattHalContextInitFunctionTypes initFunctionType, const NexaWattHalContextFunction* halContextFncPtr);
NexaWattHalContextStatusResult NexaWatt_HalContext_Bind_Function(NexaWattHalContextFunctionTypes functionType, const NexaWattHalContextFunction* halContextFncPtr);

/*******************************************************************************
* Function Definitions
*******************************************************************************/

#endif