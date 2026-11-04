#include "main.h"     // Required for HAL types, GPIO macros, and NVIC
#include "tusb.h"     // Required for tusb_init()
#include "usb_init.h" // Our own header

void USB_Hardware_Init(void)
{
    // 1. Enable the clock for the GPIO port containing the USB pins
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // 2. Configure PB14 (D-) and PB15 (D+) for USB OTG_HS internal FS PHY
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_OTG_HS_FS; 
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // 3. Now enable the USB peripheral clocks and interrupts
    __HAL_RCC_USB_OTG_HS_CLK_ENABLE();
    __HAL_RCC_USB_OTG_HS_ULPI_CLK_DISABLE();
    HAL_NVIC_SetPriority(OTG_HS_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(OTG_HS_IRQn);
    
    // 4. Initialize TinyUSB stack
    tusb_init();
}