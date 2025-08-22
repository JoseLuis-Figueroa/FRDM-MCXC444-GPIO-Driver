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

/**
 * Define the ports contained on the MCU device. It is used to identify the
 * specific port GPIO to configure the register map.
 */
typedef enum
{
    GPIO_PTA,         /**< Port A*/
    GPIO_PTB,         /**< Port B*/
    GPIO_PTC,         /**< Port C*/
    GPIO_PTD,         /**< Port D*/
    GPIO_PTH,         /**< Port H*/
    GPIO_MAX_PORT     /**< Defines the maximum Port*/
}GPIO_Port_t;

/**
 * Defines all the pins contained on the MCU device. It is used to set a 
 * specific bit on the ports.
 */
typedef enum
{
    GPIO_PTA0,        /**< PTA0/SWD_CLK/TPM0_CH5 */
    GPIO_PTA1,        /**< PTA1/LPUART0_RX/TPM2_CH0 */
    GPIO_PTA2,        /**< PTA2/LPUART0_TX/TPM2_CH1*/
    GPIO_PTA3,        /**< PTA3/SWD_DIO/I2C1_SCL/TPM0_CH0 */
    GPIO_PTA4,        /**< PTA4/NMI/I2C1_SDA/TPM0_CH1 */
    GPIO_PTA5,        /**< PTA5/USB_CLKIN/TPM0_CH2/I2S0_TX_BCLK */
    GPIO_PTA12 = 12,  /**< PTA12/TPM1_CH0/I2S0_TXD0 */
    GPIO_PTA13,       /**< PTA13/TPM1_CH1/I2S0_TX_FS */
    GPIO_PTA18,       /**< PTA18/EXTAL0/LPUART1_RX/TPM_CLKIN0 */
    GPIO_PTA19,       /**< PTA19/XTAL0/LPUART1_TX/TPM_CLKIN1/LPTMR0_ALT1 */
    GPIO_PTA20,       /**< PTA20/RESET */
   
    GPIO_PTB0 = 0,    /**< PTB0/LLWU_P5/LCD_P0/ADC0_SE8/I2C0_SCL/TPM1_CH0 */
    GPIO_PTB1,        /**< PTB1/LCD_P1/ADC0_SE9/I2C0_SDA/TPM1_CH1 */
    GPIO_PTB2,        /**< PTB2/LCD_P2/ADC0_SE12/I2C0_SCL/TPM2_CH0 */
    GPIO_PTB3,        /**< PTB3/LCD_P3/ADC0_SE13/I2C0_SDA/TPM2_CH1 */
    GPIO_PTB16 = 16,  /**< PTB16/LCD_P12/SPI1_MOSI/LPUART0_RX/TPM_CLKIN0/SPI1_MISO */
    GPIO_PTB17,       /**< PTB17/LCD_P13/SPI1_MISO/LPUART0_TX/TPM_CLKIN1/SPI1_MOSI */
    GPIO_PTB18,       /**< PTB18/LCD_P14/TPM2_CH0/I2S0_TX_BCLK */
    GPIO_PTB19,       /**< PTB19/LCD_P15/TPM2_CH1/I2S0_TX_FS */

    GPIO_PTC0 = 0,    /**< PTC0/LCD_P20/ADC0_SE14/EXTRG_IN/AUDIOUSB_SOF_OUT/CMP0_OUT/I2S0_TXD0 */
    GPIO_PTC1,        /**< PTC1/LLWU_P6/RTC_CLKIN/LCD_P21/ADC0_SE15/I2C1_SCL/TPM0_CH0/I2S0_TXD0 */
    GPIO_PTC2,        /**< PTC2/LCD_P22/ADC0_SE11/I2C1_SDA/TPM0_CH1/I2S0_TX_FS */
    GPIO_PTC3,        /**< PTC3/LLWU_P7/LCD_P23/SPI1_SCK/LPUART1_RX/TPM0_CH2/CLKOUT/I2S0_TX_BCLK */
    GPIO_PTC4,        /**< PTC4/LLWU_P8/LCD_P24/SPI0_SS/LPUART1_TX/TPM0_CH3/I2S0_MCLK */
    GPIO_PTC5,        /**< PTC5/LLWU_P9/LCD_P25/SPI0_SCK/LPTMR0_ALT2/I2S0_RXD0/CMP0_OUT */
    GPIO_PTC6,        /**< PTC6/LLWU_P10/LCD_P26/CMP0_IN0/SPI0_MOSI/EXTRG_IN/I2S0_RX_BCLK/SPI0_MISO/I2S0_MCLK */
    GPIO_PTC7,        /**< PTC7/LCD_P27/CMP0_IN1/SPI0_MISO/AUDIOUSB_SOF_OUT/I2S0_RX_FS/SPI0_MOSI */

    GPIO_PTD0 = 0,    /**< PTD0/LCD_P40/SPI0_SS/TPM0_CH0/FXI00_D0 */
    GPIO_PTD1,        /**< PTD1/LCD_P41/ADC0_SE5b/SPI0_SCK/TPM0_CH1/FXIO0_D1 */
    GPIO_PTD2,        /**< PTD2/LCD_P42/SPI0_MOSI/UART2_RX/TPM0_CH2/SPI0_MISO/FXIO0_D2*/
    GPIO_PTD3,        /**< PTD3/LCD_P43/SPI0_MISO/UART2_TX/TPM0_CH3/SPI0_MOSI/FXIO0_D3 */
    GPIO_PTD4,        /**< PTD4/LLWU_P14/LCD_P44/SPI1_SS/UART2_RX/TPM0_CH5/FXIO0_D5 */   
    GPIO_PTD5,        /**< PTD5/LCD_P45/ADC0_SE6b/SPI1_SCK/UART2_TX/TPM0_CH5/FXIO0_D5 */
    GPIO_PTD6,        /**< PTD6/LLWU_P15/LCD_P46/ADC0_SE7b/SPI1_MOSI/LPUART0_RX/SPI1_MISO/FXIO0_D6 */
    GPIO_PTD7,        /**< PTD7/LCD_P47/SPI1_MISO/LPUART0_TX/SPI1_MOSI/FXIO0_D7 */

    GPIO_PTE0 = 0,    /**< TE0/LCD_P48/CLKOUT32K/SPI1_MISO/LPUART1_TX/RTC_CLKOUT/CMP0_OUT/I2C1_SDA */
    GPIO_PTE1,        /**< PTE1/LCD_P49/SPI1_MOSI/LPUART1_RX/SPI1_MISO/I2C1_SCL */
    GPIO_PTE20 = 20,  /**< PTE20/LCD_P59/ADC0_DP0/ADC0_SE0/TPM1_CH0/LPUART0_TX/FXI00_D4 */
    GPIO_PTE21,       /**< TE21/LCD_P60/ADC0_DM0/ADC0_SE4A/TPM1_CH1/LPUART0_RX/FXIO0_D5/LCD_P60 */
    GPIO_PTE22,       /**< PTE22/ADC0_DP3/ADC0_SE3/TPM2_CH0/UART2_TX/FXIO0_D6 */
    GPIO_PTE23,       /**< PTE23/ADC0_DM3/ADC0_SE7a/TPM2_CH1/UART2_RX/FXIO0_D7 */
    GPIO_PTE24,       /**< PTE24/TPM0_CH0/I2C0_SCL */
    GPIO_PTE25,       /**< PTE25/TPM0_CH1/I2C0_SDA */
    GPIO_PTE29 = 29,  /**< TE29/CMP0_IN5/ADC0_SE4b/TPM0_CH2/TPM_CLKIN0 */
    GPIO_PTE30,       /**< PTE30/DAC0_OUT/ADC0_SE23/CMP0_IN4/TPM0_CH3/TPM_CLKIN1/LPUART1_TX/LPTMR0_ALT1 */
    GPIO_PTE31,       /**< PTE31/TPM0_CH4 */

    GPIO_MAX_PIN = 32 /**< Defines the maximum pin value*/
}GPIO_Pin_t;

/**
 * Defines the GPIO alternate function. A multiplexer selects the mode 
 * to be configured on the pin.
 */
typedef enum
{
    GPIO_AF0,        /**< Alternate function 0: pin disabled/analog */
    GPIO_AF1,        /**< Alternate function 1: GPIO */
    GPIO_AF2,        /**< Alternate function 2: chip-specific */
    GPIO_AF3,        /**< Alternate function 3: chip-specific */
    GPIO_AF4,        /**< Alternate function 4: chip-specific */
    GPIO_AF5,        /**< Alternate function 5: chip-specific */
    GPIO_AF6,        /**< Alternate function 6: chip-specific */
    GPIO_AF7,        /**< Alternate function 7: chip-specific */
    GPIO_MAX_FUNCTION/**< Defines the maximum function value */
}GPIO_Function_t;

/**
 * Defines the slew rate settings available.
 */
typedef enum
{
    GPIO_FAST_SLEW,   /**< Fast slew rate is configured on the pin */
    GPIO_SLOW_SLEW,   /**< Slow slew rate is configured on the pin */
    GPIO_MAX_SPEED    /**< Defines the maximum slew rate */
}GPIO_SlewRate_t;

/**
 * Defines the possible states of the internal resistor.
 */
typedef enum
{
    GPIO_NO_RESISTOR,    /**< Used to disable the internal resistor */
    GPIO_PULLUP,         /**< Used to enable the internal pull-up resistor */
    GPIO_PULLDOWN,       /**< Used to enable the internal pull-down resistor*/
    GPIO_MAX_RESISTOR    /**< Defines the maximum resistor value */
}GPIO_Resistor_t;

/*****************************************************************************
* Function Prototypes
*****************************************************************************/


#endif /* GPIO_CFG_H */