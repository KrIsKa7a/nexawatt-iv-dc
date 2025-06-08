/*******************************************************************************
* File Name:   main.c
*
* Description: This is the entry point of the NexaWatt-IV.DC framework demo
* application.
*
* Related Document: See README.md
*
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "mtb_hal.h"
#include "cybsp.h"
#include "hal_context.h"
#include "hal_infineon_cat1b_gpio.h"

/*******************************************************************************
* Macros
*******************************************************************************/


/*******************************************************************************
* Global Variables
*******************************************************************************/


/*******************************************************************************
* Function Prototypes
*******************************************************************************/


/*******************************************************************************
* Function Definitions
*******************************************************************************/

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary: This is the entry point of the demo and testing application, provided
* with the NexaWatt.IV-DC framework.
*
* Parameters:
*  void
*
* Return:
*  int: Program status code
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;
    const NexaWattGPIOPinConfig nwLedPinConfig =
    {
        .direction = NW_GPIO_OUTPUT,
        .altFunction = P8_4_GPIO,
        .driveMode = NW_GPIO_DM_STRONG_PP,
        .driveStrength = NW_GPIO_DSTR_FULL,
        .driveSpeed = NW_GPIO_DS_FAST,
        .initVal = 0x1u
    };
    NexaWattGPIOStatusResult gpioStatus;

    // Initialize the device and board peripherals
    result = cybsp_init();
    gpioStatus = NexaWatt_Hal_Infineon_Cat1B_Gpio_Init_Digital_Pin(8u, 4u, &nwLedPinConfig);

    // Board init failed. Stop program execution
    if (result != CY_RSLT_SUCCESS || gpioStatus != NW_GPIO_SUCCESS)
    {
        CY_ASSERT(0);
    }

    // Enable global interrupts
    __enable_irq();

    while (nwTrue)
    {
        NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Write(8u, 4u, nwFalse);

        mtb_hal_system_delay_ms(1000u);

        NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Write(8u, 4u, nwTrue);

        mtb_hal_system_delay_ms(1000u);
    }

    return 0;
}
