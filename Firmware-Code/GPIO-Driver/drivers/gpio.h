/**
 * @file gpio.h
 * @author Jose Luis Figueroa
 * @brief The interface definition for the GPIO. This is the header file for 
 * the definition of the interface for a general-purpose input/output peripheral
 * on a standard microcontroller.
 * @version 0.0
 * @date 2023-25-08
 * 
 * @copyright Copyright (c) 2025 Jose Luis Figueroa. MIT License.
 * 
 */
#ifndef GPIO_H
#define GPIO_H

/*****************************************************************************
* Includes
*****************************************************************************/
#include <stdint.h>
#include <stdio.h>
//#define NDEBUG          /*To disable assert function*/  
#include <assert.h>
#include "gpio_cfg.h"     /*For gpio configuration*/
#include "MCXC444.h"      /*For peripheral register definition*/

/*****************************************************************************
* Preprocessor Constants
*****************************************************************************/

/*****************************************************************************
* Configuration Constants
*****************************************************************************/

/*****************************************************************************
* Macros
*****************************************************************************/

/*****************************************************************************
* Typedefs
*****************************************************************************/
typedef struct
{
    DioPort_t Port;             /**< The I/O port */
    DioPin_t Pin;               /**< The I/O pin */
}GPIO_PinConfig_t;

/*****************************************************************************
* Variables
*****************************************************************************/

/*****************************************************************************
* Function Prototypes
*****************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void GPIO_init(const GPIO_Config_t * const ConfigTable, size_t size);
GPIO_PinState_t GPIO_pinRead(const GPIO_PinConfig_t * const PinConfig);
void GPIO_pinWrite(const GPIO_PinConfig_t * const PinConfig, GPIO_PinState_t state);
void GPIO_pinToggle(const GPIO_PinConfig_t * const PinConfig);
void GPIO_registerWrite(uint32_t address, uint32_t value);
uint32_t GPIO_registerRead(uint32_t address);

#ifdef _cplusplus
} // extern "C"
#endif

#endif /* GPIO_H */