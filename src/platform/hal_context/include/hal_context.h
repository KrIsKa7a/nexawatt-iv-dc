/*******************************************************************************
* File Name:   hal_context.h
*
* Description: This is the header file containing declarations and definitions,
* related to the HAL Context of the NexaWatt-IV.DC framework. The context is
* responsible for the storage of framework pre-defined/user-defines HAL functions.
*
* Related Document: See README.md
*
*******************************************************************************/

#ifndef NEXAWATT_IV_DC_HAL_CONTEXT_H
#define NEXAWATT_IV_DC_HAL_CONTEXT_H

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "platform_types.h"

/*******************************************************************************
* Macros
*******************************************************************************/
#define NW_HAL_CONTEXT_MAX_INIT_FUNCTIONS       (32u)
#define NW_HAL_CONTEXT_MAX_FUNCTIONS            (255u)

/*******************************************************************************
* Type definitions
*******************************************************************************/
typedef struct sNexaWattHalContextFunction
{
    void (*fncCallout)(void);
    void* fncPtr;
    void (*fncCallback)(void);
} NexaWattHalContextFunction;

/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
void NexaWatt_HalContext_Init(void);

/*******************************************************************************
* Function Definitions
*******************************************************************************/

#endif