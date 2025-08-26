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
static uint32_t * volatile const pinControlRegisters[NUMBER_OF_PORTS] = 
{
    (uint32_t*)&PORTA->PCR[0],  /**< Pointer to the first pin control register of PORTA */
    (uint32_t*)&PORTB->PCR[0],  /**< Pointer to the first pin control register of PORTB */
    (uint32_t*)&PORTC->PCR[0],  /**< Pointer to the first pin control register of PORTC */
    (uint32_t*)&PORTD->PCR[0],  /**< Pointer to the first pin control register of PORTD */
    (uint32_t*)&PORTE->PCR[0]   /**< Pointer to the first pin control register of PORTE */
};

/* Define an array of pointers to the port data output register */
static uint32_t * volatile const portDataOutputRegisters[NUMBER_OF_PORTS] = 
{
    (uint32_t*)&GPIOA->PDOR,  /**< Pointer to the port data output register of PORTA */
    (uint32_t*)&GPIOB->PDOR,  /**< Pointer to the port data output register of PORTB */
    (uint32_t*)&GPIOC->PDOR,  /**< Pointer to the port data output register of PORTC */
    (uint32_t*)&GPIOD->PDOR,  /**< Pointer to the port data output register of PORTD */
    (uint32_t*)&GPIOE->PDOR   /**< Pointer to the port data output register of PORTE */
};

/* Define an array of pointers to the port data input register */
static uint32_t * volatile const portDataInputRegisters[NUMBER_OF_PORTS] = 
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
