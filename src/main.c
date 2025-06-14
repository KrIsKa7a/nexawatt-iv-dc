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
* Function Prototypes - Demo applications for using HAL
*******************************************************************************/
NW_LOCAL_INLINE void ToggleLedHalfHertz(void);
NW_LOCAL_INLINE void ToggleLedOnUserBtnInputPolling(void);
NW_LOCAL_INLINE void ToggleLedOnUserBtnExti(void);

/*******************************************************************************
* Function Definitions
*******************************************************************************/
static uint8 btnPressed = 0u;
void GPIO_P5_Isr(void)
{
	NwGpioExtiStatus intrOnBtn = NexaWatt_Hal_Infineon_Cat1B_Gpio_Get_EXTI_Status_Unsafe(5u, 0u);
	if (intrOnBtn == nwTrue)
	{
		btnPressed = 1u;
	}

	NexaWatt_Hal_Infineon_Cat1B_Gpio_Clear_EXTI_Status_Unsafe(5u, 0u);
}

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
    const NexaWattGPIOPinConfig nwBtnPinConfig =
	{
		.direction = NW_GPIO_INPUT,
		.altFunction = P5_0_GPIO,
		.driveMode = NW_GPIO_DM_OPEN_DRAIN_DL,
		.driveStrength = NW_GPIO_DSTR_FULL,
		.driveSpeed = NW_GPIO_DS_FAST,
		.initVal = 0x1u
	};
    const NexaWattGPIOExtIRQConfig nwBtnExtiConfig =
    {
		.intrPriority = 5u,
		.intrEdge = NW_EXTI_RISING_EDGE,
		.isrHandlerPtr = GPIO_P5_Isr,
    };

    NexaWattGPIOStatusResult gpioStatus;

    // Initialize the device and board peripherals
    result = cybsp_init();
    gpioStatus = NexaWatt_Hal_Infineon_Cat1B_Gpio_Init_Digital_Pin(8u, 4u, &nwLedPinConfig);
    gpioStatus |= NexaWatt_Hal_Infineon_Cat1B_Gpio_Init_Digital_Pin(5u, 0u, &nwBtnPinConfig);
    gpioStatus |= NexaWatt_Hal_Infineon_Cat1B_Gpio_Register_EXTI(5u, 0u, &nwBtnExtiConfig);

    // Board init failed. Stop program execution
    if (result != CY_RSLT_SUCCESS || gpioStatus != NW_GPIO_SUCCESS)
    {
        CY_ASSERT(0);
    }

    // Enable global interrupts
    __enable_irq();

    while (nwTrue)
    {
        ToggleLedOnUserBtnExti();
    }

    return 0;
}

NW_LOCAL_INLINE void ToggleLedHalfHertz(void)
{
    NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Write(8u, 4u, nwFalse);

    mtb_hal_system_delay_ms(1000u);

    NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Write(8u, 4u, nwTrue);

    mtb_hal_system_delay_ms(1000u);
}

NW_LOCAL_INLINE void ToggleLedOnUserBtnInputPolling(void)
{
    NwGpioPinResult btnPinInput = NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Read(5u, 0u);
    if (btnPinInput == nwFalse)
    {
        NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Toggle(8u, 4u);
    }

    mtb_hal_system_delay_ms(2500u);
}

NW_LOCAL_INLINE void ToggleLedOnUserBtnExti(void)
{
    if (btnPressed == 1u)
    {
        NexaWatt_Hal_Infineon_Cat1B_Gpio_Pin_Toggle(8u, 4u);
        btnPressed = 0u;
    }

    mtb_hal_system_delay_ms(500u);
}
