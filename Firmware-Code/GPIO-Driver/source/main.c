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
#include "MCXC444.h"

int main(void)
{
    /* Enable clock access to GPIOD and GPIOC*/
    SIM->SCGC5 |= SIM_SCGC5_PORTD(1);
    SIM->SCGC5 |= SIM_SCGC5_PORTE(1);


    return 0 ;
}
