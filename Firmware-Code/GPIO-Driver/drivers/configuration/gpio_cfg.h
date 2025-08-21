/**
 * @file gpio_cfg.h
 * @author Jose Luis Figueroa
 * @brief This module contains interface definitions for the GPIO driver
 * configuration. This is the header file for the definition of the
 * interface for retrieving the general porpuse input/output configuration
 * table.
 * @version 0.0
 * @date 2025-21-08
 * 
 * @copyright Copyright (c) 2025 Jose Luis Figueroa. MIT License.
 * 
 */

#ifndef GPIO_CFG_H
#define GPIO_CFG_H

/*****************************************************************************
* Includes
*****************************************************************************/
#include <stdio.h>

/*****************************************************************************
* Preprocessor Constants
*****************************************************************************/
/**
 * Defines the number of ports on the processor.
 */
#define NUMBER_OF_PORTS 5U

/*****************************************************************************
* Typedefs
*****************************************************************************/
/**
 * Defines the possible states for a digital output pin.
*/
typedef enum
{
    GPIO_LOW,            /**< Defines digital state ground*/
    GPIO_HIGH,           /**< Defines digital state power*/
    GPIO_PIN_STATE_MAX   /**< Defines the maximum digital state*/
}GPIO_PinState_t;

/*****************************************************************************
* Function Prototypes
*****************************************************************************/

#endif /* GPIO_CFG_H */