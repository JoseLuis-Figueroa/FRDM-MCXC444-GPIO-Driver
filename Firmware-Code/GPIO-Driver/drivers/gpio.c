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

/* Define an array of pointers to the port data direction register */
static uint32_t volatile * const portDataDirectionRegisters[NUMBER_OF_PORTS] = 
{
    (uint32_t*)&GPIOA->PDDR,  /**< Pointer to the port data direction register of PORTA */
    (uint32_t*)&GPIOB->PDDR,  /**< Pointer to the port data direction register of PORTB */
    (uint32_t*)&GPIOC->PDDR,  /**< Pointer to the port data direction register of PORTC */
    (uint32_t*)&GPIOD->PDDR,  /**< Pointer to the port data direction register of PORTD */
    (uint32_t*)&GPIOE->PDDR   /**< Pointer to the port data direction register of PORTE */
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
 * PRE-CONDITION: The GPIO port clock must be enabled in the SIM module. <br>
 * PRE-CONDITION: Configuration table needs to be populated (sizeof > 0) <br>
 * PRE-CONDITION: NUMBER_OF_PORTS > 0 <br>
 * PRE-CONDITION: The setting is within the maximum values (GPIO_MAX). <br>
 * 
 * POST-CONDITION: The GPIO peripheral is set up with the configuration 
 * settings.
 * 
 * @param[in]   GPIO_Config is a pointer to the configuration table that 
 *              contains the initialization for the peripheral.
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
        
        /* Set the function of the GPIO pin and set the pin as input or
         * output if the function is GPIO.
        */
        if(ConfigTable[i].Function < GPIO_MAX_FUNCTION)
        {
            /* Set the pin function */
            *pcr = (*pcr & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(ConfigTable[i].Function);
            
            if(ConfigTable[i].Function == GPIO_AF1)
            {
                switch(ConfigTable[i].Mode)
                {
                    case GPIO_INPUT:
                        /* Set the pin as input */
                        *portDataDirectionRegisters[ConfigTable[i].Port] &=~ (1UL << ConfigTable[i].Pin);
                    break;
                    case GPIO_OUTPUT:
                        /* Set the pin as output */
                        *portDataDirectionRegisters[ConfigTable[i].Port] |= (1UL << ConfigTable[i].Pin);
                    break;
                    default:
                        assert(ConfigTable[i].Mode < GPIO_MODE_MAX);
                    break;
                }
            }    
        }
        else
        {
            assert(ConfigTable[i].Function < GPIO_MAX_FUNCTION);
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

/*****************************************************************************
 * Function: GPIO_pinRead()
*//**
 *\b Description:
 * This function is used to reads the state of a specified pin.
 * This function reads the state of a digital input/output pin specified by
 * the GPIO_PinConfig_t structure, which contains the port and pin 
 * information.
 * 
 * PRE-CONDITION: The pin is configured as INPUT <br>
 * PRE-CONDITION: The pin is configured as GPIO <br>
 * PRE-CONDITION: DioPinConfig_t needs to be populated (sizeof > 0) <br>
 * PRE-CONDITION: The Port is within the maximum DioPort_t. <br>
 * PRE-CONDITION: The Pin is within the maximum DioPin_t. 
 * definition. <br>
 * 
 * POST-CONDITION: The channel state is returned. <br>
 * 
 * @param[in] PinConfig A pointer to a structure containing the port and pin 
 * to be read.
 * 
 * @return    DioPinState_t The state of the pin (high or low).
 * 
 * \b Example:
 * @code
 * const DioPinConfig_t  UserButton1= 
 * {
 *      .Port = DIO_PC, 
 *      .Pin = DIO_PC13
 * };
 *  bool pin = DIO_pinRead(&UserButton1);
 * @endcode
 * 
 * @see DIO_ConfigGet
 * @see DIO_configSizeGet
 * @see DIO_init
 * @see DIO_pinRead
 * @see DIO_pinWrite
 * @see DIO_pinToggle
 * @see DIO_registerWrite
 * @see DIO_registerRead
 * 
**********************************************************************/