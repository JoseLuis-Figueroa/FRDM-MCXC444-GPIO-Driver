/**
 * @file gpio_cfg.c
 * @author Jose Luis Figueroa
 * @brief This module contains the implementation for the general purpose
 * input/output configuration table. This is the source file for the 
 * definition of the interface for retrieving the general purpose input/output
 * configuration table.
 * @version 0.0
 * @date 2025-25-08
 * 
 * @copyright Copyright (c) 2025 Jose Luis Figueroa. MIT License.
 * 
*/

/*****************************************************************************
* Module Includes
*****************************************************************************/
#include "gpio_cfg.h"
 
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
/**
 * The following array contains the configuration data for each general-purpose
 * input/output peripheral channel (pin). Each row represent a single pin.
 * Each column is representing a member of the GPIO_Config_t structure. This 
 * table is read in by GPIO_Init, where each channel is then set up based on 
 * this table.
*/
const GPIO_Config_t gpioConfigTable[] = 
{
    /* {Port, Pin, Function, Slew Rate, Resistor} */
    {GPIO_PTD, GPIO_PTD5,  GPIO_AF1, GPIO_SLOW_SLEW, GPIO_NO_RESISTOR}, // GREEN LED
    {GPIO_PTE, GPIO_PTE29, GPIO_AF1, GPIO_SLOW_SLEW, GPIO_NO_RESISTOR}, // BLUE LED
    {GPIO_PTE, GPIO_PTE31, GPIO_AF1, GPIO_SLOW_SLEW, GPIO_NO_RESISTOR}  // RED LED
};

/*****************************************************************************
* Function Prototypes
*****************************************************************************/

/*****************************************************************************
* Function Definitions
*****************************************************************************/