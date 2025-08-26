/**
 * @file gpio.c
 * @author Jose Luis Figueroa
 * @brief The implementation code for the GPIO driver.
 * @version 0.0
 * @date 2025-25-08
 * 
 * @copyright Copyright (c) 2025 Jose Luis Figueroa. MIT License.
 * 
 */
/*****************************************************************************
* Module Includes
*****************************************************************************/
#include "gpio.h"        /*For this modules definitions*/  

/*****************************************************************************
* Module Preprocessor Constants
*****************************************************************************/

/*****************************************************************************
* Module Preprocessor Macros
*****************************************************************************/

/*****************************************************************************
* Module Typedefs
*****************************************************************************/

/*****************************************************************************
* Module Variable Definitions
*****************************************************************************/
/* Define an array of pointers to the pin control register */
static uint32_t volatile * const pinControlRegisters[NUMBER_OF_PORTS] = 
{
    (uint32_t*)&PORTA->PCR[0],  /**< Pointer to the first pin control register of PORTA */
    (uint32_t*)&PORTB->PCR[0],  /**< Pointer to the first pin control register of PORTB */
    (uint32_t*)&PORTC->PCR[0],  /**< Pointer to the first pin control register of PORTC */
    (uint32_t*)&PORTD->PCR[0],  /**< Pointer to the first pin control register of PORTD */
    (uint32_t*)&PORTE->PCR[0]   /**< Pointer to the first pin control register of PORTE */
};

/* Define an array of pointers to the port data output register */
static uint32_t volatile * const portDataOutputRegisters[NUMBER_OF_PORTS] = 
{
    (uint32_t*)&GPIOA->PDOR,  /**< Pointer to the port data output register of PORTA */
    (uint32_t*)&GPIOB->PDOR,  /**< Pointer to the port data output register of PORTB */
    (uint32_t*)&GPIOC->PDOR,  /**< Pointer to the port data output register of PORTC */
    (uint32_t*)&GPIOD->PDOR,  /**< Pointer to the port data output register of PORTD */
    (uint32_t*)&GPIOE->PDOR   /**< Pointer to the port data output register of PORTE */
};

/* Define an array of pointers to the port data input register */
static uint32_t volatile * const portDataInputRegisters[NUMBER_OF_PORTS] = 
{
    (uint32_t*)&GPIOA->PDIR,  /**< Pointer to the port data input register of PORTA */
    (uint32_t*)&GPIOB->PDIR,  /**< Pointer to the port data input register of PORTB */
    (uint32_t*)&GPIOC->PDIR,  /**< Pointer to the port data input register of PORTC */
    (uint32_t*)&GPIOD->PDIR,  /**< Pointer to the port data input register of PORTD */
    (uint32_t*)&GPIOE->PDIR   /**< Pointer to the port data input register of PORTE */
};

/*****************************************************************************
* Function Prototypes
*****************************************************************************/

/*****************************************************************************
* Function Definitions
*****************************************************************************/
/*****************************************************************************
 * Function: GPIO_init()
*//**
*\b Description: 
 * This function is used to initialize the GPIO based on the configuration  
 * table defined in gpio_cfg module.
 * 
 * PRE-CONDITION: The MCU clocks must be configured and enabled. <br>
 * PRE-CONDITION: Configuration table needs to be populated (sizeof > 0) <br>
 * PRE-CONDITION: NUMBER_OF_PORTS > 0 <br>
 * PRE-CONDITION: The setting is within the maximum values (GPIO_MAX). <br>
 * 
 * POST-CONDITION: The GPIO peripheral is set up with the configuration 
 * settings.
 * 
 * @param[in]   GPIO_Config is a pointer to the configuration table that contains 
 *               the initialization for the peripheral.
 * @param[in]   configSizeGpio is the size of the configuration table.
 * 
 * @return  void
 * 
 * \b Example:
 * @code
 * const GPIO_Config_t * const GPIO_Config = GPIO_getConfigTable();
 * size_t configSizeGpio = GPIO_getConfigTableSize();
 * 
 * GPIO_init(GPIO_Config, configSizeGpio);
 * 
 * @endcode
 * 
 * @see GPIO_getConfigTable
 * @see GPIO_getConfigTableSize
 * @see GPIO_init
 * @see GPIO_channelRead
 * @see GPIO_channelWrite
 * @see GPIO_channelToggle
 * @see GPIO_registerWrite
 * @see GPIO_registerRead
 * 
*****************************************************************************/
void GPIO_init(const GPIO_Config_t * const ConfigTable, size_t size)
{
    /* 
     * Prevent initialization if the configuration table or size is not 
     * assigned.
    */
    assert(ConfigTable != NULL);
    assert(size > 0);

    /* Loop through all the elements of the configuration table. */
    for(uint8_t i = 0; i < size; i++)
    {
        /* Prevent to assign a value out of the range of the port and pin.
         * The registers arrays are limited to the NUMBER_OF_PORTS, higher 
         * value can cause a memory violation.
        */
        assert(ConfigTable[i].Port < GPIO_MAX_PORT);
        assert(ConfigTable[i].Pin < GPIO_MAX_PIN);

        /* Get a pointer to the pin control register to be configured */
        uint32_t volatile * const pcr = &pinControlRegisters[ConfigTable[i].Port][ConfigTable[i].Pin];

        /* Set the mode/function of the GPIO pin on the pin control register*/
        if(ConfigTable[i].Function >= GPIO_MAX_FUNCTION)
        {
            assert(ConfigTable[i].Function < GPIO_MAX_FUNCTION);
        }
        else 
        {
            *pcr = (*pcr & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(ConfigTable[i].Function);
        }

        /* Set the slew rate of the GPIO pin on the pin control register*/
        if(ConfigTable[i].SlewRate >= GPIO_MAX_SPEED)
        {
            assert(ConfigTable[i].SlewRate < GPIO_MAX_SPEED);
        }
        else 
        {
            *pcr = (*pcr & ~PORT_PCR_SRE_MASK) | PORT_PCR_SRE(ConfigTable[i].SlewRate);
        }

        /* Set the internal resistor of the GPIO pin on the pin control register*/
        switch(ConfigTable[i].Resistor)
        {
            case GPIO_NO_RESISTOR:
                /* Disable the internal resistor */
                *pcr = (*pcr & ~PORT_PCR_PE_MASK);
                break;
            case GPIO_PULLUP:
                /* Enable the internal pull-up resistor */
                *pcr = (*pcr & ~PORT_PCR_PE_MASK) | PORT_PCR_PE(1);
                *pcr = (*pcr & ~PORT_PCR_PS_MASK) | PORT_PCR_PS(1);
                break;
            case GPIO_PULLDOWN:
                /* Enable the internal pull-down resistor*/
                *pcr = (*pcr & ~PORT_PCR_PE_MASK) | PORT_PCR_PE(1);
                *pcr = (*pcr & ~PORT_PCR_PS_MASK) | PORT_PCR_PS(0);
                break;
            default:
                assert(ConfigTable[i].Resistor < GPIO_MAX_RESISTOR);
                break;
        }
    }
}
