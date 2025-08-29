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
static uint32_t volatile * const pinControlRegister[NUMBER_OF_PORTS] = 
{
    (uint32_t*)&PORTA->PCR[0],  /**< Pointer to the first pin control register of PORTA */
    (uint32_t*)&PORTB->PCR[0],  /**< Pointer to the first pin control register of PORTB */
    (uint32_t*)&PORTC->PCR[0],  /**< Pointer to the first pin control register of PORTC */
    (uint32_t*)&PORTD->PCR[0],  /**< Pointer to the first pin control register of PORTD */
    (uint32_t*)&PORTE->PCR[0]   /**< Pointer to the first pin control register of PORTE */
};

/* Define an array of pointers to the port data output register */
static uint32_t volatile * const portDataOutputRegister[NUMBER_OF_PORTS] = 
{
    (uint32_t*)&GPIOA->PDOR,  /**< Pointer to the port data output register of PORTA */
    (uint32_t*)&GPIOB->PDOR,  /**< Pointer to the port data output register of PORTB */
    (uint32_t*)&GPIOC->PDOR,  /**< Pointer to the port data output register of PORTC */
    (uint32_t*)&GPIOD->PDOR,  /**< Pointer to the port data output register of PORTD */
    (uint32_t*)&GPIOE->PDOR   /**< Pointer to the port data output register of PORTE */
};

/* Define an array of pointers to the port data input register */
static uint32_t volatile * const portDataInputRegister[NUMBER_OF_PORTS] = 
{
    (uint32_t*)&GPIOA->PDIR,  /**< Pointer to the port data input register of PORTA */
    (uint32_t*)&GPIOB->PDIR,  /**< Pointer to the port data input register of PORTB */
    (uint32_t*)&GPIOC->PDIR,  /**< Pointer to the port data input register of PORTC */
    (uint32_t*)&GPIOD->PDIR,  /**< Pointer to the port data input register of PORTD */
    (uint32_t*)&GPIOE->PDIR   /**< Pointer to the port data input register of PORTE */
};

/* Define an array of pointers to the port data direction register */
static uint32_t volatile * const portDataDirectionRegister[NUMBER_OF_PORTS] = 
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
 * @param[in]   ConfigTable is a pointer to the configuration table that 
 *              contains the initialization for the peripheral.
 * @param[in]   size is the size of the configuration table.
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
 * @see GPIO_pinRead
 * @see GPIO_pinWrite
 * @see GPIO_pinToggle
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
        uint32_t volatile * const pcr = &pinControlRegister[ConfigTable[i].Port][ConfigTable[i].Pin];
        
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
                        *portDataDirectionRegister[ConfigTable[i].Port] &=~ (1UL << ConfigTable[i].Pin);
                    break;
                    case GPIO_OUTPUT:
                        /* Set the pin as output */
                        *portDataDirectionRegister[ConfigTable[i].Port] |= (1UL << ConfigTable[i].Pin);
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
 * PRE-CONDITION: The pin is configured as GPIO <br>
 * PRE-CONDITION: The pin is configured as INPUT <br>
 * PRE-CONDITION: GPIO_PinConfig_t needs to be populated (sizeof > 0) <br>
 * PRE-CONDITION: The Port is within the maximum GPIO_Port_t. <br>
 * PRE-CONDITION: The Pin is within the maximum GPIO_Pin_t. <br>
 * 
 * POST-CONDITION: The pin state is returned. <br>
 * 
 * @param[in] PinConfig A pointer to a structure containing the port and pin 
 * to be read.
 * 
 * @return GPIO_PinState_t The state of the pin (high or low).
 * 
 * \b Example:
 * @code
 * const GPIO_PinConfig_t  UserButton1= 
 * {
 *      .Port = GPIO_PTA, 
 *      .Pin = GPIO_PT13
 * };
 *  bool pin = GPIO_pinRead(&UserButton1);
 * @endcode
 * 
 * @see GPIO_getConfigTable
 * @see GPIO_getConfigTableSize
 * @see GPIO_init
 * @see GPIO_pinRead
 * @see GPIO_pinWrite
 * @see GPIO_pinToggle
 * @see GPIO_registerWrite
 * @see GPIO_registerRead 
 * 
**********************************************************************/
GPIO_PinState_t GPIO_pinRead(const GPIO_PinConfig_t * const PinConfig)
{
    /* Prevent to assign a value out of the range of the port and pin.
     * The registers arrays are limited to the NUMBER_OF_PORTS, higher 
     * value can cause a memory violation.
    */
    assert(PinConfig->Port < GPIO_MAX_PORT);
    assert(PinConfig->Pin < GPIO_MAX_PIN);

    /* Read the port associated with the desired pin */
    uint32_t portState = *portDataInputRegister[PinConfig->Port];
    /* Determinate the Port bit associated with this pin*/
    uint32_t pinMask = (1UL<<(PinConfig->Pin));

    return ((portState & pinMask) ? GPIO_HIGH : GPIO_LOW); 
}

/**********************************************************************
 * Function: GPIO_pinWrite()
*//**
 *\b Description:
 * This function is used to write the state of a pin as either logic 
 * high or low. it reads the state of a digital input/output pin 
 * specified by the GPIO_PinConfig_t structure and the GPIO_PinState_t to 
 * define the desired state, which contains the port and pin 
 * information.
 * 
 * PRE-CONDITION: The pin is configured as GPIO <br>
 * PRE-CONDITION: The pin is configured as OUTPUT <br>
 * PRE-CONDITION: GPIO_PinConfig_t needs to be populated (sizeof > 0) <br>
 * PRE-CONDITION: The Port is within the maximum GPIO_Port_t. <br>
 * PRE-CONDITION: The Pin is within the maximum GPIO_Pin_t. <br>
 * PRE-CONDITION: The State is within the maximum GPIO_PinState_t. <br>
 * 
 * POST-CONDITION: The pin state is stated. <br>
 * 
 * @param[in]   pinConfig A pointer to a structure containing the port 
 *              and pin to be written.
 * @param[in]   State is HIGH or LOW as defined in the GPIO_PinState_t 
 *              enum. 
 * 
 * @return      void
 * 
 * \b Example:
 * @code
 * const GPIO_PinConfig_t  UserLED1= 
 * {
 *      .Port = GPIO_PTE, 
 *      .Pin = GPIO_PTE29
 * };
 * const GPIO_PinConfig_t  UserLED2= 
 * {
 *      .Port = GPIO_PTE, 
 *      .Pin = GPIO_PTE31
 * };
 * GPIO_pinWrite(&UserLED1, GPIO_LOW);    //Set the pin low
 * GPIO_pinWrite(&UserLED2, GPIO_HIGH);   //Set the pin high
 * @endcode
 * 
 * @see GPIO_getConfigTable
 * @see GPIO_getConfigTableSize
 * @see GPIO_init
 * @see GPIO_pinRead
 * @see GPIO_pinWrite
 * @see GPIO_pinToggle
 * @see GPIO_registerWrite
 * @see GPIO_registerRead 
 * 
 **********************************************************************/
void GPIO_pinWrite(const GPIO_PinConfig_t * const PinConfig, GPIO_PinState_t State)
{
    /* Prevent to assign a value out of the range of the port and pin.
     * The registers arrays are limited to the NUMBER_OF_PORTS, higher 
     * value can cause a memory violation.
    */
    assert(PinConfig->Port < GPIO_MAX_PORT);
    assert(PinConfig->Pin < GPIO_MAX_PIN);

    if(State == GPIO_HIGH)
    {
        *portDataOutputRegister[PinConfig->Port] |= (1UL<<(PinConfig->Pin));
    }
    else if (State == GPIO_LOW)
    {
        *portDataOutputRegister[PinConfig->Port] &= ~(1UL<<(PinConfig->Pin));
    }
    else
    {
        assert(State < GPIO_PIN_STATE_MAX);
    }
}

/**********************************************************************
 * Function: GPIO_pinToggle()
*//**
 *\b Description:
 * This function is used to toggle the current state of a pin. 
 * This function reads the state of a digital input/output pin 
 * specified by the GPIO_PinConfig_t structure, which contains the port 
 * and pin information.
 * 
 * PRE-CONDITION: The channel is configured as GPIO <br>
 * PRE-CONDITION: The channel is configured as output <br>
 * PRE-CONDITION: GPIO_PinConfig_t needs to be populated (sizeof > 0) <br>
 * PRE-CONDITION: The Port is within the maximum GPIO_Port_t. <br>
 * PRE-CONDITION: The Pin is within the maximum GPIO_Pin_t. <br>
 *
 * POST-CONDITION: The pin state is toggled. <br>
 * 
 * @param[in]   pinConfig A pointer to a structure containing the port 
 *              and pin to be toggled.
 * 
 * @return  void
 * 
 * \b Example:
 * @code
 * const GPIO_PinConfig_t  UserLED1= 
 * {
 *      .Port = GPIO_PTA, 
 *      .Pin = GPIO_PTA5
 * };
 * GPIO_pinToggle(&UserLED1);
 * @endcode
 * 
 * @see GPIO_getConfigTable
 * @see GPIO_getConfigTableSize
 * @see GPIO_init
 * @see GPIO_pinRead
 * @see GPIO_pinWrite
 * @see GPIO_pinToggle
 * @see GPIO_registerWrite
 * @see GPIO_registerRead 
 * 
 **********************************************************************/
void GPIO_pinToggle(const GPIO_PinConfig_t * const PinConfig)
{
    /* Prevent to assign a value out of the range of the port and pin.
     * The registers arrays are limited to the NUMBER_OF_PORTS, higher 
     * value can cause a memory violation.
    */
    assert(PinConfig->Port < GPIO_MAX_PORT);
    assert(PinConfig->Pin < GPIO_MAX_PIN);

    *portDataOutputRegister[PinConfig->Port] ^= (1UL<<(PinConfig->Pin));
}

/**********************************************************************
 * Function: GPIO_registerWrite()
*//**
 *\b Description:
 * This function is used to directly address and modify a GPIO register.
 * The function should be used to access specialized functionality in 
 * the GPIO peripheral that is not exposed by any other function of the
 * interface.
 * 
 * PRE-CONDITION: Address is within the boundaries of the GPIO register
 * address space. <br>
 * 
 * POST-CONDITION: The register located at address with be updated with
 * value. <br>
 * 
 * @param[in]   address is a register address within the GPIO peripheral
 *              map.
 * @param[in]   value is the value to set the GPIO register. 
 * 
 * @return void
 * 
 * \b Example
 * @code
 *  GPIO_registerWrite(0x1000, 0x15);
 * @endcode
 * 
 * @see GPIO_getConfigTable
 * @see GPIO_getConfigTableSize
 * @see GPIO_init
 * @see GPIO_pinRead
 * @see GPIO_pinWrite
 * @see GPIO_pinToggle
 * @see GPIO_registerWrite
 * @see GPIO_registerRead 
 * 
**********************************************************************/ 
void GPIO_registerWrite(uint32_t address, uint32_t value)
{
    volatile uint32_t * const registerPointer = (uint32_t*)address;
    *registerPointer = value;
}