/*******************************************************************************
* File Name:   hal_context.c
*
* Description: This is the source file containing definitions,
* related to the HAL Context, used by the HAL Wrappers and HAL Manager.
* This context aims to implement an export-bind pattern for the HAL functions,
* used by the HAL Wrappers. This provides high level of abstraction and possibility
* to support multiple MCUs with different HALs.
*
* Related Document: See README.md
*
*******************************************************************************/

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
* Local Variables
*******************************************************************************/
static NexaWattHalContextFunction initFunctionsStore[NW_HAL_CONTEXT_MAX_INIT_FUNCTIONS];
static NexaWattHalContextFunction halFunctionsStore[NW_HAL_CONTEXT_MAX_FUNCTIONS];

/*******************************************************************************
* Local Function Prototypes
*******************************************************************************/
static NexaWattHalContextStatusResult NexaWatt_HalContext_Store_Bindable_Function(uint8 functionTypeIdx, const NexaWattHalContextFunction* halContextFncPtr,
    uint8 halContextStorageCapacity, NexaWattHalContextFunction* functionStorage);
static NexaWattHalContextStatusResult NexaWatt_HalContext_Export_Bind_Function(uint8 functionTypeIdx, NexaWattHalContextFunction* halContextFncPtr,
    uint8 halContextStorageCapacity, const NexaWattHalContextFunction* functionStorage);

/*******************************************************************************
* Function Definitions
*******************************************************************************/
/**
 * \brief Initialization function that must be invoked before using the HAL Context component.
 * It ensures that all of the HAL Context stores are initialized with default data.
 */
void NexaWatt_HalContext_Init(void)
{
    uint8 storesIdx = 0u;
    for (storesIdx = 0u; storesIdx < NW_HAL_CONTEXT_MAX_INIT_FUNCTIONS; storesIdx++)
    {
        initFunctionsStore[storesIdx].fncCallout = NULL;
        initFunctionsStore[storesIdx].fncCallback = NULL;
        initFunctionsStore[storesIdx].fncPtr = NULL;
    }

    for (storesIdx = 0u; storesIdx < NW_HAL_CONTEXT_MAX_FUNCTIONS; storesIdx++)
    {
        halFunctionsStore[storesIdx].fncCallout = NULL;
        halFunctionsStore[storesIdx].fncCallback = NULL;
        halFunctionsStore[storesIdx].fncPtr = NULL;
    }
}

/**
 * \brief The function performs a check of the provided parameters and
 * exports the HAL Init function user data, that was already stored in the internal context storage
 * by the previous execution of the NexaWatt_HalContext_Bind_Init_Function() function.
 * The passed HAL Init function type should be a valid and supported function type by the framework.
 * The passed HAL Init function struct should not be equal to NULL and will be used by the user of the function to access the exported data.
 * The function is used by the HAL Wrappers to obtain the registered HAL Init functions, independently of the used MCU and HAL.
 * \param initFunctionType - The type of the HAL Init function registered.
 * \param halContextFncPtr - A pointer, containing the exported HAL Init function information. The user should pass a valid pointer that will be populated by the function.
 * \return NW_HAL_CONTEXT_BAD_PARAM - One of the provided parameters have wrong value. Possibly the HAL Init function type is not supported or the passed function pointer is NULL.
 * \return NW_HAL_CONTEXT_NOT_FOUND - There is not data stored for the corresponding HAL Init function type in the HAL Context. Please bind the function first.
 * \return NW_HAL_CONTEXT_OK - The HAL Init function was successfully found and exported.
 */
NexaWattHalContextStatusResult NexaWatt_HalContext_Export_Init_Function(NexaWattHalContextInitFunctionTypes initFunctionType, NexaWattHalContextFunction* const halContextFncPtr)
{
    uint8 initFunctionTypeIdx = (uint8)initFunctionType;
    NexaWattHalContextStatusResult retRes =
            NexaWatt_HalContext_Export_Bind_Function(initFunctionTypeIdx, halContextFncPtr, NW_HAL_CONTEXT_MAX_INIT_FUNCTIONS, initFunctionsStore);

    return retRes;
}

/**
 * \brief The function performs a check of the provided parameters and
 * exports the HAL function user data, that was already stored in the internal context storage
 * by the previous execution of the NexaWatt_HalContext_Bind_Function() function.
 * The passed HAL function type should be a valid and supported function type by the framework.
 * The passed HAL function struct should not be equal to NULL and will be used by the user of the function to access the exported data.
 * The function is used by the HAL Wrappers to obtain the registered HAL functions, independently of the used MCU and HAL.
 * \param initFunctionType - The type of the HAL function registered.
 * \param halContextFncPtr - A pointer, containing the exported HAL function information. The user should pass a valid pointer that will be populated by the function.
 * \return NW_HAL_CONTEXT_BAD_PARAM - One of the provided parameters have wrong value. Possibly the HAL function type is not supported or the passed function pointer is NULL.
 * \return NW_HAL_CONTEXT_NOT_FOUND - There is not data stored for the corresponding HAL function type in the HAL Context. Please bind the function first.
 * \return NW_HAL_CONTEXT_OK - The HAL function was successfully found and exported.
 */
NexaWattHalContextStatusResult NexaWatt_HalContext_Export_Function(NexaWattHalContextFunctionTypes functionType, NexaWattHalContextFunction* const halContextFncPtr)
{
    uint8 halFunctionTypeIdx = (uint8)functionType;
    NexaWattHalContextStatusResult retRes =
            NexaWatt_HalContext_Export_Bind_Function(halFunctionTypeIdx, halContextFncPtr, NW_HAL_CONTEXT_MAX_FUNCTIONS, halFunctionsStore);

    return retRes;
}

/**
 * \brief The function performs a check of the provided parameters and
 * stores the HAL Init function user data in the internal context storage for init functions.
 * The passed HAL Init function type should be a valid and supported function type by the framework.
 * The passed HAL Init function struct should contain at least the pointer to the function.
 * \param initFunctionType - The type of the HAL Init function registered.
 * \param halContextFncPtr - The user-defined information about the HAL Init function. It may contain function callout, callback and pointer.
 * \return NW_HAL_CONTEXT_BAD_PARAM - One of the provided parameters have wrong value. Possibly the HAL Init function type is not supported or the passed function pointer is NULL.
 * \return NW_HAL_CONTEXT_OK - The HAL Init function was successfully registered.
 */
NexaWattHalContextStatusResult NexaWatt_HalContext_Bind_Init_Function(NexaWattHalContextInitFunctionTypes initFunctionType, const NexaWattHalContextFunction* const halContextFncPtr)
{
    uint8 initFunctionTypeIdx = (uint8)initFunctionType;
    NexaWattHalContextStatusResult retRes =
            NexaWatt_HalContext_Store_Bindable_Function(initFunctionTypeIdx, halContextFncPtr, NW_HAL_CONTEXT_MAX_INIT_FUNCTIONS, initFunctionsStore);

    return retRes;
}

/**
 * \brief The function performs a check of the provided parameters and
 * stores the HAL function user data in the internal context storage for HAL functions.
 * The passed HAL function type should be a valid and supported function type by the framework.
 * The passed HAL function struct should contain at least the pointer to the function.
 * \param functionType - The type of the HAL function registered.
 * \param halContextFncPtr - The user-defined information about the HAL function. It may contain function callout, callback and pointer.
 * \return NW_HAL_CONTEXT_BAD_PARAM - One of the provided parameters have wrong value. Possibly the HAL function type is not supported or the passed function pointer is NULL.
 * \return NW_HAL_CONTEXT_OK - The HAL function was successfully registered.
 */
NexaWattHalContextStatusResult NexaWatt_HalContext_Bind_Function(NexaWattHalContextFunctionTypes functionType, const NexaWattHalContextFunction* const halContextFncPtr)
{
    uint8 functionTypeIdx = (uint8)functionType;
    NexaWattHalContextStatusResult retRes =
            NexaWatt_HalContext_Store_Bindable_Function(functionTypeIdx, halContextFncPtr, NW_HAL_CONTEXT_MAX_FUNCTIONS, halFunctionsStore);

    return retRes;
}

/**
 * \brief Helper function to reuse the logic of the bindable function validation for both
 * HAL Init functions and HAL functions. The function performs validation of the provided parameter values
 * and stores the user-defined HAL Context function data to the corresponding HAL Context storage.
 * The function returns status result as indication of the operation status.
 * \param functionTypeIdx - The index at which the function should be stored in the HAL Context storage.
 * \param halContextFncPtr - The user-defined information about the HAL function. It may contain function callout, callback and pointer.
 * \param halContextStorageCapacity - The maximum capacity of the corresponding HAL Context storage.
 * \param functionStorage - A pointer to the corresponding HAL Context storage that should be used for the function data storage.
 * \return NW_HAL_CONTEXT_BAD_PARAM - One of the provided parameters have wrong value. Possibly the HAL function type is not supported or the passed function pointer is NULL.
 * \return NW_HAL_CONTEXT_OK - The HAL function was successfully registered.
 */
static NexaWattHalContextStatusResult NexaWatt_HalContext_Store_Bindable_Function(uint8 functionTypeIdx, const NexaWattHalContextFunction* const halContextFncPtr,
    uint8 halContextStorageCapacity, NexaWattHalContextFunction* const functionStorage)
{
    NexaWattHalContextStatusResult retRes = NW_HAL_CONTEXT_BAD_PARAM;

    if ((halContextFncPtr != NULL) &&
        (functionTypeIdx < halContextStorageCapacity) &&
        (halContextFncPtr->fncPtr != NULL))
    {
        functionStorage[functionTypeIdx].fncCallout = halContextFncPtr->fncCallout;
        functionStorage[functionTypeIdx].fncCallback = halContextFncPtr->fncCallback;
        functionStorage[functionTypeIdx].fncPtr = halContextFncPtr->fncPtr;

        retRes = NW_HAL_CONTEXT_OK;
    }

    return retRes;
}

/**
 * \brief Helper function to reuse the logic of the bind function export for both of the
 * HAL Init functions and HAL functions. The function performs validation of the provided parameter values
 * and exports the copies the stored HAL Context function data to the provided NexaWattHalContextFunction pointer.
 * The function returns status result as indication of the operation status.
 * \param functionTypeIdx - The index from which the function should be obtained from the internal HAL Context storage.
 * \param halContextFncPtr - A pointer, where the stored information about the HAL function will be copied to. The user obtains the data through this pointer parameter's argument.
 * \param halContextStorageCapacity - The maximum capacity of the corresponding HAL Context storage.
 * \param functionStorage - A pointer to the corresponding HAL Context storage that should be used for the function export.
 * \return NW_HAL_CONTEXT_BAD_PARAM - One of the provided parameters have wrong value. Possibly the HAL function type is not supported or the passed function pointer is NULL.
 * \return NW_HAL_CONTEXT_NOT_FOUND - There is not data stored for the corresponding HAL function type in the HAL Context. Please bind the function first.
 * \return NW_HAL_CONTEXT_OK - The HAL function was successfully found and exported.
 */
static NexaWattHalContextStatusResult NexaWatt_HalContext_Export_Bind_Function(uint8 functionTypeIdx, NexaWattHalContextFunction* const halContextFncPtr,
                                                                               uint8 halContextStorageCapacity, const NexaWattHalContextFunction* const functionStorage)
{
    NexaWattHalContextStatusResult retRes = NW_HAL_CONTEXT_BAD_PARAM;
    NexaWattHalContextFunction halContextFunctionEntry;

    if ((halContextFncPtr != NULL) &&
        (functionTypeIdx < halContextStorageCapacity))
    {
        halContextFunctionEntry = functionStorage[functionTypeIdx];

        if (halContextFunctionEntry.fncPtr != NULL)
        {
            halContextFncPtr->fncPtr = halContextFunctionEntry.fncPtr;
            halContextFncPtr->fncCallout = halContextFunctionEntry.fncCallout;
            halContextFncPtr->fncCallback = halContextFunctionEntry.fncCallback;

            retRes = NW_HAL_CONTEXT_OK;
        }
        else
        {
            retRes = NW_HAL_CONTEXT_NOT_FOUND;
        }
    }

    return retRes;
}