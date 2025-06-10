/*******************************************************************************
* File Name:   platform_types.h
*
* Description: This is the header file containing declarations and definitions
* of common type definitions that will be reused among the entire platform tier.
*
* Related Document: See README.md
*
*******************************************************************************/

#ifndef NEXAWATT_IV_DC_PLATFORM_TYPES_H
#define NEXAWATT_IV_DC_PLATFORM_TYPES_H

/*******************************************************************************
* Header Files
*******************************************************************************/
#include <stdint.h>
#include <stddef.h>

/*******************************************************************************
* Macros
*******************************************************************************/
#define NW_INLINE           inline
#define NW_LOCAL_INLINE     static inline

#define nwFalse             (0u != 0u)
#define nwTrue              (0u == 0u)

#define NwIsrPointerType(arg)    (void (*arg)(void))

/*******************************************************************************
* Type definitions
*******************************************************************************/
typedef uint8_t uint8;
typedef int8_t int8;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint32_t uint32;
typedef int32_t int32;
typedef uint64_t uint64;
typedef int64_t int64;

typedef uint8_t nw_bool;
typedef nw_bool NwGpioPinResult;
typedef uint16 NwGpioPinAltFunction;
typedef uint32 NwInterruptMask;

typedef enum eNexaWattGPIOPinDirection
{
    NW_GPIO_INPUT   = 0x01u,
    NW_GPIO_OUTPUT  = 0x02u,
} NexaWattGPIOPinDirection;

typedef enum eNexaWattGPIOPinDriveMode
{
    NW_GPIO_DM_STRONG_PP        = 0x00u,
    NW_GPIO_DM_PULL_UP          = 0x01u,
    NW_GPIO_DM_PULL_DOWN        = 0x02u,
    NW_GPIO_DM_OPEN_DRAIN_DL    = 0x03u,
    NW_GPIO_DM_OPEN_DRAIN_DH    = 0x04u,
    NW_GPIO_DM_HIGH_Z           = 0x05u,
    NW_GPIO_DM_ANALOG           = 0x06u,
} NexaWattGPIOPinDriveMode;

typedef enum eNexaWattGPIOPinDriveSpeed
{
    NW_GPIO_DS_FAST = 0x00u,
    NW_GPIO_DS_SLOW = 0x01u,
} NexaWattGPIOPinDriveSpeed;

typedef enum eNexaWattGPIOPinDriveStrength
{
    NW_GPIO_DSTR_FULL       = 0x00u,
    NW_GPIO_DSTR_HALF       = 0x01u,
    NW_GPIO_DSTR_QUARTER    = 0x02u,
} NexaWattGPIOPinDriveStrength;

typedef struct sNexaWattGPIOPinConfig
{
    nw_bool initVal;
    NwGpioPinAltFunction altFunction;
    NexaWattGPIOPinDirection direction;
    NexaWattGPIOPinDriveMode driveMode;
    NexaWattGPIOPinDriveSpeed driveSpeed;
    NexaWattGPIOPinDriveStrength driveStrength;
} NexaWattGPIOPinConfig;

typedef enum eNexaWattGPIOStatusResult
{
    NW_GPIO_SUCCESS     = 0u,
    NW_GPIO_BAD_PARAM   = 1u,
    NW_GPIO_FATAL_ERR   = 2u,
} NexaWattGPIOStatusResult;

typedef enum eNexaWattGPIOInterruptEdgeEXTI
{
    NW_EXTI_DISABLE         = 0x00u,
    NW_EXTI_RISING_EDGE     = 0x01u,
    NW_EXTI_FALLING_EDGE    = 0x02u,
    NW_EXTI_BOTH_EDGES      = 0x03u,
} NexaWattGPIOInterruptEdgeEXTI;

typedef enum eNexaWattHalContextInitFunctionTypes
{
    NW_HAL_BSP_INIT                     = 0u,
    NW_HAL_GPIO_DIGITAL_IO_PIN_INIT     = 1u,
    NW_HAL_GPIO_DIGITAL_IO_PIN_DEINIT   = 2u,
    NW_HAL_INIT_FUNC_INVALID            = 32u,
} NexaWattHalContextInitFunctionTypes;

typedef enum eNexaWattHalContextFunctionTypes
{
    NW_HAL_GPIO_PIN_READ        = 0u,
    NW_HAL_GPIO_PIN_WRITE       = 1u,
    NW_HAL_GPIO_PIN_TOGGLE      = 2u,
    NW_HAL_GPIO_REGISTER_EXTI   = 3u,
    NW_HAL_GPIO_TRIGGER_SW_INTR = 4u,
    NW_HAL_FUNC_INVALID         = 255u,
} NexaWattHalContextFunctionTypes;

typedef enum eNexaWattHalContextStatusResult
{
    NW_HAL_CONTEXT_OK,
    NW_HAL_CONTEXT_NOT_FOUND,
    NW_HAL_CONTEXT_BAD_PARAM,
} NexaWattHalContextStatusResult;

/*******************************************************************************
* Global Variables
*******************************************************************************/


/*******************************************************************************
* Function Prototypes
*******************************************************************************/


/*******************************************************************************
* Function Definitions
*******************************************************************************/

#endif
