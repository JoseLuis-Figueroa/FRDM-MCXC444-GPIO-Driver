/**
 * @file main.c
 * @author Jose Luis Figueroa
 * @brief Implement the GPIO driver. 
 * @version 0.0
 * @date 2025-21-08
 * @note 
 * 
 * @copyright Copyright (c) 2025 Jose Luis Figueroa. MIT License.
 * 
 */
/*****************************************************************************
* Includes
*****************************************************************************/
#include <stdio.h>
#include "gpio.h"
#include "MCXC444.h"

int main(void)
{
    /* Enable clock access to GPIOB, GPIOD and GPIOE*/
    SIM->SCGC5 |= SIM_SCGC5_PORTB(1);
    SIM->SCGC5 |= SIM_SCGC5_PORTD(1);
    SIM->SCGC5 |= SIM_SCGC5_PORTE(1);

    /* Retrieve the configuration table */
    const GPIO_Config_t * const GPIO_Config = GPIO_getConfigTable();
    /* Retrieve the size of the configuration table */
    size_t configSizeGpio = GPIO_getConfigTableSize();
    /* Initialize the GPIO peripheral */
    GPIO_init(GPIO_Config, configSizeGpio);

    /* Define pin configuration for the input (PTB16) */
    const GPIO_PinConfig_t InputPin = {GPIO_PTB, GPIO_PTB16};

    /* Define pin configuration for the GREEN LED (PTD5) */
    const GPIO_PinConfig_t GreenLed = {GPIO_PTD, GPIO_PTD5};
    /* Define pin configuration for the BLUE LED (PTE29) */
    const GPIO_PinConfig_t BlueLed = {GPIO_PTE, GPIO_PTE29};
    /* Define pin configuration for the RED LED (PTE31) */
    const GPIO_PinConfig_t RedLed = {GPIO_PTE, GPIO_PTE31};

    while(1)
    {
        /* Read the state of the input pin */
        if(GPIO_pinRead(&InputPin) == GPIO_LOW)
        {
            /* Turn off the RGB LED */
            GPIO_pinWrite(&GreenLed, GPIO_LOW);
            GPIO_pinWrite(&BlueLed, GPIO_LOW);
            GPIO_pinWrite(&RedLed, GPIO_LOW);
        }
        else
        {
            /* Turn on the RGB Led */
            GPIO_pinWrite(&GreenLed, GPIO_HIGH);
            GPIO_pinWrite(&BlueLed, GPIO_HIGH);
            GPIO_pinWrite(&RedLed, GPIO_HIGH);
        }

        /* Toggle the RGB LED */
        GPIO_pinToggle(&GreenLed);
        GPIO_pinToggle(&BlueLed);
        GPIO_pinToggle(&RedLed);

        /* Turn off the green light of RGB Led */
        /* Turn off the blue and red lights of RGB Led */
        GPIO_registerWrite(0x400FF0C0, 0x00000020);
        GPIO_registerWrite(0x400FF100, 0xA0000000);

        /* Read the GPIOE_PDOR register*/
        uint32_t regValue = GPIO_registerRead(0x400FF100);
    }
    
    return 0 ;
}
