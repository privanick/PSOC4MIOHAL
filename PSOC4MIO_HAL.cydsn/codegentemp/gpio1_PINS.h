/***************************************************************************//**
* \file gpio1_PINS.h
* \version 3.20
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_gpio1_H)
#define CY_SCB_PINS_gpio1_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define gpio1_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define gpio1_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define gpio1_REMOVE_TX_SDA_MISO_PIN      (1u)
#define gpio1_REMOVE_CTS_SCLK_PIN      (1u)
#define gpio1_REMOVE_RTS_SS0_PIN      (1u)
#define gpio1_REMOVE_SS1_PIN                 (1u)
#define gpio1_REMOVE_SS2_PIN                 (1u)
#define gpio1_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define gpio1_REMOVE_I2C_PINS                (0u)
#define gpio1_REMOVE_SPI_MASTER_PINS         (1u)
#define gpio1_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define gpio1_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define gpio1_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define gpio1_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define gpio1_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define gpio1_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define gpio1_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define gpio1_REMOVE_SPI_SLAVE_PINS          (1u)
#define gpio1_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define gpio1_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define gpio1_REMOVE_UART_TX_PIN             (1u)
#define gpio1_REMOVE_UART_RX_TX_PIN          (1u)
#define gpio1_REMOVE_UART_RX_PIN             (1u)
#define gpio1_REMOVE_UART_RX_WAKE_PIN        (1u)
#define gpio1_REMOVE_UART_RTS_PIN            (1u)
#define gpio1_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define gpio1_RX_WAKE_SCL_MOSI_PIN (0u == gpio1_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define gpio1_RX_SCL_MOSI_PIN     (0u == gpio1_REMOVE_RX_SCL_MOSI_PIN)
#define gpio1_TX_SDA_MISO_PIN     (0u == gpio1_REMOVE_TX_SDA_MISO_PIN)
#define gpio1_CTS_SCLK_PIN     (0u == gpio1_REMOVE_CTS_SCLK_PIN)
#define gpio1_RTS_SS0_PIN     (0u == gpio1_REMOVE_RTS_SS0_PIN)
#define gpio1_SS1_PIN                (0u == gpio1_REMOVE_SS1_PIN)
#define gpio1_SS2_PIN                (0u == gpio1_REMOVE_SS2_PIN)
#define gpio1_SS3_PIN                (0u == gpio1_REMOVE_SS3_PIN)

/* Mode defined pins */
#define gpio1_I2C_PINS               (0u == gpio1_REMOVE_I2C_PINS)
#define gpio1_SPI_MASTER_PINS        (0u == gpio1_REMOVE_SPI_MASTER_PINS)
#define gpio1_SPI_MASTER_SCLK_PIN    (0u == gpio1_REMOVE_SPI_MASTER_SCLK_PIN)
#define gpio1_SPI_MASTER_MOSI_PIN    (0u == gpio1_REMOVE_SPI_MASTER_MOSI_PIN)
#define gpio1_SPI_MASTER_MISO_PIN    (0u == gpio1_REMOVE_SPI_MASTER_MISO_PIN)
#define gpio1_SPI_MASTER_SS0_PIN     (0u == gpio1_REMOVE_SPI_MASTER_SS0_PIN)
#define gpio1_SPI_MASTER_SS1_PIN     (0u == gpio1_REMOVE_SPI_MASTER_SS1_PIN)
#define gpio1_SPI_MASTER_SS2_PIN     (0u == gpio1_REMOVE_SPI_MASTER_SS2_PIN)
#define gpio1_SPI_MASTER_SS3_PIN     (0u == gpio1_REMOVE_SPI_MASTER_SS3_PIN)
#define gpio1_SPI_SLAVE_PINS         (0u == gpio1_REMOVE_SPI_SLAVE_PINS)
#define gpio1_SPI_SLAVE_MOSI_PIN     (0u == gpio1_REMOVE_SPI_SLAVE_MOSI_PIN)
#define gpio1_SPI_SLAVE_MISO_PIN     (0u == gpio1_REMOVE_SPI_SLAVE_MISO_PIN)
#define gpio1_UART_TX_PIN            (0u == gpio1_REMOVE_UART_TX_PIN)
#define gpio1_UART_RX_TX_PIN         (0u == gpio1_REMOVE_UART_RX_TX_PIN)
#define gpio1_UART_RX_PIN            (0u == gpio1_REMOVE_UART_RX_PIN)
#define gpio1_UART_RX_WAKE_PIN       (0u == gpio1_REMOVE_UART_RX_WAKE_PIN)
#define gpio1_UART_RTS_PIN           (0u == gpio1_REMOVE_UART_RTS_PIN)
#define gpio1_UART_CTS_PIN           (0u == gpio1_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (gpio1_RX_WAKE_SCL_MOSI_PIN)
    #include "gpio1_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (gpio1_RX_SCL_MOSI) */

#if (gpio1_RX_SCL_MOSI_PIN)
    #include "gpio1_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (gpio1_RX_SCL_MOSI) */

#if (gpio1_TX_SDA_MISO_PIN)
    #include "gpio1_uart_tx_i2c_sda_spi_miso.h"
#endif /* (gpio1_TX_SDA_MISO) */

#if (gpio1_CTS_SCLK_PIN)
    #include "gpio1_uart_cts_spi_sclk.h"
#endif /* (gpio1_CTS_SCLK) */

#if (gpio1_RTS_SS0_PIN)
    #include "gpio1_uart_rts_spi_ss0.h"
#endif /* (gpio1_RTS_SS0_PIN) */

#if (gpio1_SS1_PIN)
    #include "gpio1_spi_ss1.h"
#endif /* (gpio1_SS1_PIN) */

#if (gpio1_SS2_PIN)
    #include "gpio1_spi_ss2.h"
#endif /* (gpio1_SS2_PIN) */

#if (gpio1_SS3_PIN)
    #include "gpio1_spi_ss3.h"
#endif /* (gpio1_SS3_PIN) */

#if (gpio1_I2C_PINS)
    #include "gpio1_scl.h"
    #include "gpio1_sda.h"
#endif /* (gpio1_I2C_PINS) */

#if (gpio1_SPI_MASTER_PINS)
#if (gpio1_SPI_MASTER_SCLK_PIN)
    #include "gpio1_sclk_m.h"
#endif /* (gpio1_SPI_MASTER_SCLK_PIN) */

#if (gpio1_SPI_MASTER_MOSI_PIN)
    #include "gpio1_mosi_m.h"
#endif /* (gpio1_SPI_MASTER_MOSI_PIN) */

#if (gpio1_SPI_MASTER_MISO_PIN)
    #include "gpio1_miso_m.h"
#endif /*(gpio1_SPI_MASTER_MISO_PIN) */
#endif /* (gpio1_SPI_MASTER_PINS) */

#if (gpio1_SPI_SLAVE_PINS)
    #include "gpio1_sclk_s.h"
    #include "gpio1_ss_s.h"

#if (gpio1_SPI_SLAVE_MOSI_PIN)
    #include "gpio1_mosi_s.h"
#endif /* (gpio1_SPI_SLAVE_MOSI_PIN) */

#if (gpio1_SPI_SLAVE_MISO_PIN)
    #include "gpio1_miso_s.h"
#endif /*(gpio1_SPI_SLAVE_MISO_PIN) */
#endif /* (gpio1_SPI_SLAVE_PINS) */

#if (gpio1_SPI_MASTER_SS0_PIN)
    #include "gpio1_ss0_m.h"
#endif /* (gpio1_SPI_MASTER_SS0_PIN) */

#if (gpio1_SPI_MASTER_SS1_PIN)
    #include "gpio1_ss1_m.h"
#endif /* (gpio1_SPI_MASTER_SS1_PIN) */

#if (gpio1_SPI_MASTER_SS2_PIN)
    #include "gpio1_ss2_m.h"
#endif /* (gpio1_SPI_MASTER_SS2_PIN) */

#if (gpio1_SPI_MASTER_SS3_PIN)
    #include "gpio1_ss3_m.h"
#endif /* (gpio1_SPI_MASTER_SS3_PIN) */

#if (gpio1_UART_TX_PIN)
    #include "gpio1_tx.h"
#endif /* (gpio1_UART_TX_PIN) */

#if (gpio1_UART_RX_TX_PIN)
    #include "gpio1_rx_tx.h"
#endif /* (gpio1_UART_RX_TX_PIN) */

#if (gpio1_UART_RX_PIN)
    #include "gpio1_rx.h"
#endif /* (gpio1_UART_RX_PIN) */

#if (gpio1_UART_RX_WAKE_PIN)
    #include "gpio1_rx_wake.h"
#endif /* (gpio1_UART_RX_WAKE_PIN) */

#if (gpio1_UART_RTS_PIN)
    #include "gpio1_rts.h"
#endif /* (gpio1_UART_RTS_PIN) */

#if (gpio1_UART_CTS_PIN)
    #include "gpio1_cts.h"
#endif /* (gpio1_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (gpio1_RX_SCL_MOSI_PIN)
    #define gpio1_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) gpio1_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define gpio1_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) gpio1_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define gpio1_RX_SCL_MOSI_HSIOM_MASK      (gpio1_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define gpio1_RX_SCL_MOSI_HSIOM_POS       (gpio1_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define gpio1_RX_SCL_MOSI_HSIOM_SEL_GPIO  (gpio1_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define gpio1_RX_SCL_MOSI_HSIOM_SEL_I2C   (gpio1_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define gpio1_RX_SCL_MOSI_HSIOM_SEL_SPI   (gpio1_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define gpio1_RX_SCL_MOSI_HSIOM_SEL_UART  (gpio1_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (gpio1_RX_WAKE_SCL_MOSI_PIN)
    #define gpio1_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) gpio1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define gpio1_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) gpio1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define gpio1_RX_WAKE_SCL_MOSI_HSIOM_MASK      (gpio1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define gpio1_RX_WAKE_SCL_MOSI_HSIOM_POS       (gpio1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define gpio1_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (gpio1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define gpio1_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (gpio1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define gpio1_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (gpio1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define gpio1_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (gpio1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define gpio1_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) gpio1_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define gpio1_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) gpio1_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define gpio1_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (gpio1_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define gpio1_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) gpio1_INTCFG_TYPE_MASK << \
                                                                           gpio1_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins gpio1_RX_SCL_MOSI_PIN or gpio1_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (gpio1_RX_SCL_MOSI_PIN) */

#if (gpio1_TX_SDA_MISO_PIN)
    #define gpio1_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) gpio1_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define gpio1_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) gpio1_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define gpio1_TX_SDA_MISO_HSIOM_MASK      (gpio1_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define gpio1_TX_SDA_MISO_HSIOM_POS       (gpio1_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define gpio1_TX_SDA_MISO_HSIOM_SEL_GPIO  (gpio1_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define gpio1_TX_SDA_MISO_HSIOM_SEL_I2C   (gpio1_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define gpio1_TX_SDA_MISO_HSIOM_SEL_SPI   (gpio1_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define gpio1_TX_SDA_MISO_HSIOM_SEL_UART  (gpio1_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (gpio1_TX_SDA_MISO_PIN) */

#if (gpio1_CTS_SCLK_PIN)
    #define gpio1_CTS_SCLK_HSIOM_REG   (*(reg32 *) gpio1_uart_cts_spi_sclk__0__HSIOM)
    #define gpio1_CTS_SCLK_HSIOM_PTR   ( (reg32 *) gpio1_uart_cts_spi_sclk__0__HSIOM)
    
    #define gpio1_CTS_SCLK_HSIOM_MASK      (gpio1_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define gpio1_CTS_SCLK_HSIOM_POS       (gpio1_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define gpio1_CTS_SCLK_HSIOM_SEL_GPIO  (gpio1_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define gpio1_CTS_SCLK_HSIOM_SEL_I2C   (gpio1_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define gpio1_CTS_SCLK_HSIOM_SEL_SPI   (gpio1_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define gpio1_CTS_SCLK_HSIOM_SEL_UART  (gpio1_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (gpio1_CTS_SCLK_PIN) */

#if (gpio1_RTS_SS0_PIN)
    #define gpio1_RTS_SS0_HSIOM_REG   (*(reg32 *) gpio1_uart_rts_spi_ss0__0__HSIOM)
    #define gpio1_RTS_SS0_HSIOM_PTR   ( (reg32 *) gpio1_uart_rts_spi_ss0__0__HSIOM)
    
    #define gpio1_RTS_SS0_HSIOM_MASK      (gpio1_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define gpio1_RTS_SS0_HSIOM_POS       (gpio1_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define gpio1_RTS_SS0_HSIOM_SEL_GPIO  (gpio1_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define gpio1_RTS_SS0_HSIOM_SEL_I2C   (gpio1_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define gpio1_RTS_SS0_HSIOM_SEL_SPI   (gpio1_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(gpio1_CY_SCBIP_V0 || gpio1_CY_SCBIP_V1)
    #define gpio1_RTS_SS0_HSIOM_SEL_UART  (gpio1_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(gpio1_CY_SCBIP_V0 || gpio1_CY_SCBIP_V1) */
#endif /* (gpio1_RTS_SS0_PIN) */

#if (gpio1_SS1_PIN)
    #define gpio1_SS1_HSIOM_REG  (*(reg32 *) gpio1_spi_ss1__0__HSIOM)
    #define gpio1_SS1_HSIOM_PTR  ( (reg32 *) gpio1_spi_ss1__0__HSIOM)
    
    #define gpio1_SS1_HSIOM_MASK     (gpio1_spi_ss1__0__HSIOM_MASK)
    #define gpio1_SS1_HSIOM_POS      (gpio1_spi_ss1__0__HSIOM_SHIFT)
    #define gpio1_SS1_HSIOM_SEL_GPIO (gpio1_spi_ss1__0__HSIOM_GPIO)
    #define gpio1_SS1_HSIOM_SEL_I2C  (gpio1_spi_ss1__0__HSIOM_I2C)
    #define gpio1_SS1_HSIOM_SEL_SPI  (gpio1_spi_ss1__0__HSIOM_SPI)
#endif /* (gpio1_SS1_PIN) */

#if (gpio1_SS2_PIN)
    #define gpio1_SS2_HSIOM_REG     (*(reg32 *) gpio1_spi_ss2__0__HSIOM)
    #define gpio1_SS2_HSIOM_PTR     ( (reg32 *) gpio1_spi_ss2__0__HSIOM)
    
    #define gpio1_SS2_HSIOM_MASK     (gpio1_spi_ss2__0__HSIOM_MASK)
    #define gpio1_SS2_HSIOM_POS      (gpio1_spi_ss2__0__HSIOM_SHIFT)
    #define gpio1_SS2_HSIOM_SEL_GPIO (gpio1_spi_ss2__0__HSIOM_GPIO)
    #define gpio1_SS2_HSIOM_SEL_I2C  (gpio1_spi_ss2__0__HSIOM_I2C)
    #define gpio1_SS2_HSIOM_SEL_SPI  (gpio1_spi_ss2__0__HSIOM_SPI)
#endif /* (gpio1_SS2_PIN) */

#if (gpio1_SS3_PIN)
    #define gpio1_SS3_HSIOM_REG     (*(reg32 *) gpio1_spi_ss3__0__HSIOM)
    #define gpio1_SS3_HSIOM_PTR     ( (reg32 *) gpio1_spi_ss3__0__HSIOM)
    
    #define gpio1_SS3_HSIOM_MASK     (gpio1_spi_ss3__0__HSIOM_MASK)
    #define gpio1_SS3_HSIOM_POS      (gpio1_spi_ss3__0__HSIOM_SHIFT)
    #define gpio1_SS3_HSIOM_SEL_GPIO (gpio1_spi_ss3__0__HSIOM_GPIO)
    #define gpio1_SS3_HSIOM_SEL_I2C  (gpio1_spi_ss3__0__HSIOM_I2C)
    #define gpio1_SS3_HSIOM_SEL_SPI  (gpio1_spi_ss3__0__HSIOM_SPI)
#endif /* (gpio1_SS3_PIN) */

#if (gpio1_I2C_PINS)
    #define gpio1_SCL_HSIOM_REG  (*(reg32 *) gpio1_scl__0__HSIOM)
    #define gpio1_SCL_HSIOM_PTR  ( (reg32 *) gpio1_scl__0__HSIOM)
    
    #define gpio1_SCL_HSIOM_MASK     (gpio1_scl__0__HSIOM_MASK)
    #define gpio1_SCL_HSIOM_POS      (gpio1_scl__0__HSIOM_SHIFT)
    #define gpio1_SCL_HSIOM_SEL_GPIO (gpio1_sda__0__HSIOM_GPIO)
    #define gpio1_SCL_HSIOM_SEL_I2C  (gpio1_sda__0__HSIOM_I2C)
    
    #define gpio1_SDA_HSIOM_REG  (*(reg32 *) gpio1_sda__0__HSIOM)
    #define gpio1_SDA_HSIOM_PTR  ( (reg32 *) gpio1_sda__0__HSIOM)
    
    #define gpio1_SDA_HSIOM_MASK     (gpio1_sda__0__HSIOM_MASK)
    #define gpio1_SDA_HSIOM_POS      (gpio1_sda__0__HSIOM_SHIFT)
    #define gpio1_SDA_HSIOM_SEL_GPIO (gpio1_sda__0__HSIOM_GPIO)
    #define gpio1_SDA_HSIOM_SEL_I2C  (gpio1_sda__0__HSIOM_I2C)
#endif /* (gpio1_I2C_PINS) */

#if (gpio1_SPI_SLAVE_PINS)
    #define gpio1_SCLK_S_HSIOM_REG   (*(reg32 *) gpio1_sclk_s__0__HSIOM)
    #define gpio1_SCLK_S_HSIOM_PTR   ( (reg32 *) gpio1_sclk_s__0__HSIOM)
    
    #define gpio1_SCLK_S_HSIOM_MASK      (gpio1_sclk_s__0__HSIOM_MASK)
    #define gpio1_SCLK_S_HSIOM_POS       (gpio1_sclk_s__0__HSIOM_SHIFT)
    #define gpio1_SCLK_S_HSIOM_SEL_GPIO  (gpio1_sclk_s__0__HSIOM_GPIO)
    #define gpio1_SCLK_S_HSIOM_SEL_SPI   (gpio1_sclk_s__0__HSIOM_SPI)
    
    #define gpio1_SS0_S_HSIOM_REG    (*(reg32 *) gpio1_ss0_s__0__HSIOM)
    #define gpio1_SS0_S_HSIOM_PTR    ( (reg32 *) gpio1_ss0_s__0__HSIOM)
    
    #define gpio1_SS0_S_HSIOM_MASK       (gpio1_ss0_s__0__HSIOM_MASK)
    #define gpio1_SS0_S_HSIOM_POS        (gpio1_ss0_s__0__HSIOM_SHIFT)
    #define gpio1_SS0_S_HSIOM_SEL_GPIO   (gpio1_ss0_s__0__HSIOM_GPIO)  
    #define gpio1_SS0_S_HSIOM_SEL_SPI    (gpio1_ss0_s__0__HSIOM_SPI)
#endif /* (gpio1_SPI_SLAVE_PINS) */

#if (gpio1_SPI_SLAVE_MOSI_PIN)
    #define gpio1_MOSI_S_HSIOM_REG   (*(reg32 *) gpio1_mosi_s__0__HSIOM)
    #define gpio1_MOSI_S_HSIOM_PTR   ( (reg32 *) gpio1_mosi_s__0__HSIOM)
    
    #define gpio1_MOSI_S_HSIOM_MASK      (gpio1_mosi_s__0__HSIOM_MASK)
    #define gpio1_MOSI_S_HSIOM_POS       (gpio1_mosi_s__0__HSIOM_SHIFT)
    #define gpio1_MOSI_S_HSIOM_SEL_GPIO  (gpio1_mosi_s__0__HSIOM_GPIO)
    #define gpio1_MOSI_S_HSIOM_SEL_SPI   (gpio1_mosi_s__0__HSIOM_SPI)
#endif /* (gpio1_SPI_SLAVE_MOSI_PIN) */

#if (gpio1_SPI_SLAVE_MISO_PIN)
    #define gpio1_MISO_S_HSIOM_REG   (*(reg32 *) gpio1_miso_s__0__HSIOM)
    #define gpio1_MISO_S_HSIOM_PTR   ( (reg32 *) gpio1_miso_s__0__HSIOM)
    
    #define gpio1_MISO_S_HSIOM_MASK      (gpio1_miso_s__0__HSIOM_MASK)
    #define gpio1_MISO_S_HSIOM_POS       (gpio1_miso_s__0__HSIOM_SHIFT)
    #define gpio1_MISO_S_HSIOM_SEL_GPIO  (gpio1_miso_s__0__HSIOM_GPIO)
    #define gpio1_MISO_S_HSIOM_SEL_SPI   (gpio1_miso_s__0__HSIOM_SPI)
#endif /* (gpio1_SPI_SLAVE_MISO_PIN) */

#if (gpio1_SPI_MASTER_MISO_PIN)
    #define gpio1_MISO_M_HSIOM_REG   (*(reg32 *) gpio1_miso_m__0__HSIOM)
    #define gpio1_MISO_M_HSIOM_PTR   ( (reg32 *) gpio1_miso_m__0__HSIOM)
    
    #define gpio1_MISO_M_HSIOM_MASK      (gpio1_miso_m__0__HSIOM_MASK)
    #define gpio1_MISO_M_HSIOM_POS       (gpio1_miso_m__0__HSIOM_SHIFT)
    #define gpio1_MISO_M_HSIOM_SEL_GPIO  (gpio1_miso_m__0__HSIOM_GPIO)
    #define gpio1_MISO_M_HSIOM_SEL_SPI   (gpio1_miso_m__0__HSIOM_SPI)
#endif /* (gpio1_SPI_MASTER_MISO_PIN) */

#if (gpio1_SPI_MASTER_MOSI_PIN)
    #define gpio1_MOSI_M_HSIOM_REG   (*(reg32 *) gpio1_mosi_m__0__HSIOM)
    #define gpio1_MOSI_M_HSIOM_PTR   ( (reg32 *) gpio1_mosi_m__0__HSIOM)
    
    #define gpio1_MOSI_M_HSIOM_MASK      (gpio1_mosi_m__0__HSIOM_MASK)
    #define gpio1_MOSI_M_HSIOM_POS       (gpio1_mosi_m__0__HSIOM_SHIFT)
    #define gpio1_MOSI_M_HSIOM_SEL_GPIO  (gpio1_mosi_m__0__HSIOM_GPIO)
    #define gpio1_MOSI_M_HSIOM_SEL_SPI   (gpio1_mosi_m__0__HSIOM_SPI)
#endif /* (gpio1_SPI_MASTER_MOSI_PIN) */

#if (gpio1_SPI_MASTER_SCLK_PIN)
    #define gpio1_SCLK_M_HSIOM_REG   (*(reg32 *) gpio1_sclk_m__0__HSIOM)
    #define gpio1_SCLK_M_HSIOM_PTR   ( (reg32 *) gpio1_sclk_m__0__HSIOM)
    
    #define gpio1_SCLK_M_HSIOM_MASK      (gpio1_sclk_m__0__HSIOM_MASK)
    #define gpio1_SCLK_M_HSIOM_POS       (gpio1_sclk_m__0__HSIOM_SHIFT)
    #define gpio1_SCLK_M_HSIOM_SEL_GPIO  (gpio1_sclk_m__0__HSIOM_GPIO)
    #define gpio1_SCLK_M_HSIOM_SEL_SPI   (gpio1_sclk_m__0__HSIOM_SPI)
#endif /* (gpio1_SPI_MASTER_SCLK_PIN) */

#if (gpio1_SPI_MASTER_SS0_PIN)
    #define gpio1_SS0_M_HSIOM_REG    (*(reg32 *) gpio1_ss0_m__0__HSIOM)
    #define gpio1_SS0_M_HSIOM_PTR    ( (reg32 *) gpio1_ss0_m__0__HSIOM)
    
    #define gpio1_SS0_M_HSIOM_MASK       (gpio1_ss0_m__0__HSIOM_MASK)
    #define gpio1_SS0_M_HSIOM_POS        (gpio1_ss0_m__0__HSIOM_SHIFT)
    #define gpio1_SS0_M_HSIOM_SEL_GPIO   (gpio1_ss0_m__0__HSIOM_GPIO)
    #define gpio1_SS0_M_HSIOM_SEL_SPI    (gpio1_ss0_m__0__HSIOM_SPI)
#endif /* (gpio1_SPI_MASTER_SS0_PIN) */

#if (gpio1_SPI_MASTER_SS1_PIN)
    #define gpio1_SS1_M_HSIOM_REG    (*(reg32 *) gpio1_ss1_m__0__HSIOM)
    #define gpio1_SS1_M_HSIOM_PTR    ( (reg32 *) gpio1_ss1_m__0__HSIOM)
    
    #define gpio1_SS1_M_HSIOM_MASK       (gpio1_ss1_m__0__HSIOM_MASK)
    #define gpio1_SS1_M_HSIOM_POS        (gpio1_ss1_m__0__HSIOM_SHIFT)
    #define gpio1_SS1_M_HSIOM_SEL_GPIO   (gpio1_ss1_m__0__HSIOM_GPIO)
    #define gpio1_SS1_M_HSIOM_SEL_SPI    (gpio1_ss1_m__0__HSIOM_SPI)
#endif /* (gpio1_SPI_MASTER_SS1_PIN) */

#if (gpio1_SPI_MASTER_SS2_PIN)
    #define gpio1_SS2_M_HSIOM_REG    (*(reg32 *) gpio1_ss2_m__0__HSIOM)
    #define gpio1_SS2_M_HSIOM_PTR    ( (reg32 *) gpio1_ss2_m__0__HSIOM)
    
    #define gpio1_SS2_M_HSIOM_MASK       (gpio1_ss2_m__0__HSIOM_MASK)
    #define gpio1_SS2_M_HSIOM_POS        (gpio1_ss2_m__0__HSIOM_SHIFT)
    #define gpio1_SS2_M_HSIOM_SEL_GPIO   (gpio1_ss2_m__0__HSIOM_GPIO)
    #define gpio1_SS2_M_HSIOM_SEL_SPI    (gpio1_ss2_m__0__HSIOM_SPI)
#endif /* (gpio1_SPI_MASTER_SS2_PIN) */

#if (gpio1_SPI_MASTER_SS3_PIN)
    #define gpio1_SS3_M_HSIOM_REG    (*(reg32 *) gpio1_ss3_m__0__HSIOM)
    #define gpio1_SS3_M_HSIOM_PTR    ( (reg32 *) gpio1_ss3_m__0__HSIOM)
    
    #define gpio1_SS3_M_HSIOM_MASK      (gpio1_ss3_m__0__HSIOM_MASK)
    #define gpio1_SS3_M_HSIOM_POS       (gpio1_ss3_m__0__HSIOM_SHIFT)
    #define gpio1_SS3_M_HSIOM_SEL_GPIO  (gpio1_ss3_m__0__HSIOM_GPIO)
    #define gpio1_SS3_M_HSIOM_SEL_SPI   (gpio1_ss3_m__0__HSIOM_SPI)
#endif /* (gpio1_SPI_MASTER_SS3_PIN) */

#if (gpio1_UART_RX_PIN)
    #define gpio1_RX_HSIOM_REG   (*(reg32 *) gpio1_rx__0__HSIOM)
    #define gpio1_RX_HSIOM_PTR   ( (reg32 *) gpio1_rx__0__HSIOM)
    
    #define gpio1_RX_HSIOM_MASK      (gpio1_rx__0__HSIOM_MASK)
    #define gpio1_RX_HSIOM_POS       (gpio1_rx__0__HSIOM_SHIFT)
    #define gpio1_RX_HSIOM_SEL_GPIO  (gpio1_rx__0__HSIOM_GPIO)
    #define gpio1_RX_HSIOM_SEL_UART  (gpio1_rx__0__HSIOM_UART)
#endif /* (gpio1_UART_RX_PIN) */

#if (gpio1_UART_RX_WAKE_PIN)
    #define gpio1_RX_WAKE_HSIOM_REG   (*(reg32 *) gpio1_rx_wake__0__HSIOM)
    #define gpio1_RX_WAKE_HSIOM_PTR   ( (reg32 *) gpio1_rx_wake__0__HSIOM)
    
    #define gpio1_RX_WAKE_HSIOM_MASK      (gpio1_rx_wake__0__HSIOM_MASK)
    #define gpio1_RX_WAKE_HSIOM_POS       (gpio1_rx_wake__0__HSIOM_SHIFT)
    #define gpio1_RX_WAKE_HSIOM_SEL_GPIO  (gpio1_rx_wake__0__HSIOM_GPIO)
    #define gpio1_RX_WAKE_HSIOM_SEL_UART  (gpio1_rx_wake__0__HSIOM_UART)
#endif /* (gpio1_UART_WAKE_RX_PIN) */

#if (gpio1_UART_CTS_PIN)
    #define gpio1_CTS_HSIOM_REG   (*(reg32 *) gpio1_cts__0__HSIOM)
    #define gpio1_CTS_HSIOM_PTR   ( (reg32 *) gpio1_cts__0__HSIOM)
    
    #define gpio1_CTS_HSIOM_MASK      (gpio1_cts__0__HSIOM_MASK)
    #define gpio1_CTS_HSIOM_POS       (gpio1_cts__0__HSIOM_SHIFT)
    #define gpio1_CTS_HSIOM_SEL_GPIO  (gpio1_cts__0__HSIOM_GPIO)
    #define gpio1_CTS_HSIOM_SEL_UART  (gpio1_cts__0__HSIOM_UART)
#endif /* (gpio1_UART_CTS_PIN) */

#if (gpio1_UART_TX_PIN)
    #define gpio1_TX_HSIOM_REG   (*(reg32 *) gpio1_tx__0__HSIOM)
    #define gpio1_TX_HSIOM_PTR   ( (reg32 *) gpio1_tx__0__HSIOM)
    
    #define gpio1_TX_HSIOM_MASK      (gpio1_tx__0__HSIOM_MASK)
    #define gpio1_TX_HSIOM_POS       (gpio1_tx__0__HSIOM_SHIFT)
    #define gpio1_TX_HSIOM_SEL_GPIO  (gpio1_tx__0__HSIOM_GPIO)
    #define gpio1_TX_HSIOM_SEL_UART  (gpio1_tx__0__HSIOM_UART)
#endif /* (gpio1_UART_TX_PIN) */

#if (gpio1_UART_RX_TX_PIN)
    #define gpio1_RX_TX_HSIOM_REG   (*(reg32 *) gpio1_rx_tx__0__HSIOM)
    #define gpio1_RX_TX_HSIOM_PTR   ( (reg32 *) gpio1_rx_tx__0__HSIOM)
    
    #define gpio1_RX_TX_HSIOM_MASK      (gpio1_rx_tx__0__HSIOM_MASK)
    #define gpio1_RX_TX_HSIOM_POS       (gpio1_rx_tx__0__HSIOM_SHIFT)
    #define gpio1_RX_TX_HSIOM_SEL_GPIO  (gpio1_rx_tx__0__HSIOM_GPIO)
    #define gpio1_RX_TX_HSIOM_SEL_UART  (gpio1_rx_tx__0__HSIOM_UART)
#endif /* (gpio1_UART_RX_TX_PIN) */

#if (gpio1_UART_RTS_PIN)
    #define gpio1_RTS_HSIOM_REG      (*(reg32 *) gpio1_rts__0__HSIOM)
    #define gpio1_RTS_HSIOM_PTR      ( (reg32 *) gpio1_rts__0__HSIOM)
    
    #define gpio1_RTS_HSIOM_MASK     (gpio1_rts__0__HSIOM_MASK)
    #define gpio1_RTS_HSIOM_POS      (gpio1_rts__0__HSIOM_SHIFT)    
    #define gpio1_RTS_HSIOM_SEL_GPIO (gpio1_rts__0__HSIOM_GPIO)
    #define gpio1_RTS_HSIOM_SEL_UART (gpio1_rts__0__HSIOM_UART)    
#endif /* (gpio1_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define gpio1_HSIOM_DEF_SEL      (0x00u)
#define gpio1_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for gpio1_CY_SCBIP_V0 
* and gpio1_CY_SCBIP_V1. It is not recommended to use them for 
* gpio1_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define gpio1_HSIOM_UART_SEL     (0x09u)
#define gpio1_HSIOM_I2C_SEL      (0x0Eu)
#define gpio1_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define gpio1_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define gpio1_RX_SCL_MOSI_PIN_INDEX       (0u)
#define gpio1_TX_SDA_MISO_PIN_INDEX       (1u)
#define gpio1_CTS_SCLK_PIN_INDEX       (2u)
#define gpio1_RTS_SS0_PIN_INDEX       (3u)
#define gpio1_SS1_PIN_INDEX                  (4u)
#define gpio1_SS2_PIN_INDEX                  (5u)
#define gpio1_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define gpio1_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << gpio1_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define gpio1_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << gpio1_RX_SCL_MOSI_PIN_INDEX)
#define gpio1_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << gpio1_TX_SDA_MISO_PIN_INDEX)
#define gpio1_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << gpio1_CTS_SCLK_PIN_INDEX)
#define gpio1_RTS_SS0_PIN_MASK     ((uint32) 0x01u << gpio1_RTS_SS0_PIN_INDEX)
#define gpio1_SS1_PIN_MASK                ((uint32) 0x01u << gpio1_SS1_PIN_INDEX)
#define gpio1_SS2_PIN_MASK                ((uint32) 0x01u << gpio1_SS2_PIN_INDEX)
#define gpio1_SS3_PIN_MASK                ((uint32) 0x01u << gpio1_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define gpio1_INTCFG_TYPE_MASK           (0x03u)
#define gpio1_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define gpio1_PIN_DM_ALG_HIZ  (0u)
#define gpio1_PIN_DM_DIG_HIZ  (1u)
#define gpio1_PIN_DM_OD_LO    (4u)
#define gpio1_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define gpio1_DM_MASK    (0x7u)
#define gpio1_DM_SIZE    (3u)
#define gpio1_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) gpio1_DM_MASK << (gpio1_DM_SIZE * (pos)))) >> \
                                                              (gpio1_DM_SIZE * (pos)) )

#if (gpio1_TX_SDA_MISO_PIN)
    #define gpio1_CHECK_TX_SDA_MISO_PIN_USED \
                (gpio1_PIN_DM_ALG_HIZ != \
                    gpio1_GET_P4_PIN_DM(gpio1_uart_tx_i2c_sda_spi_miso_PC, \
                                                   gpio1_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (gpio1_TX_SDA_MISO_PIN) */

#if (gpio1_RTS_SS0_PIN)
    #define gpio1_CHECK_RTS_SS0_PIN_USED \
                (gpio1_PIN_DM_ALG_HIZ != \
                    gpio1_GET_P4_PIN_DM(gpio1_uart_rts_spi_ss0_PC, \
                                                   gpio1_uart_rts_spi_ss0_SHIFT))
#endif /* (gpio1_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define gpio1_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define gpio1_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define gpio1_SET_HSIOM_SEL(reg, mask, pos, sel) gpio1_SET_REGISTER_BITS(reg, mask, pos, sel)
#define gpio1_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        gpio1_SET_REGISTER_BITS(reg, mask, pos, intType)
#define gpio1_SET_INP_DIS(reg, mask, val) gpio1_SET_REGISTER_BIT(reg, mask, val)

/* gpio1_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  gpio1_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (gpio1_CY_SCBIP_V0)
#if (gpio1_I2C_PINS)
    #define gpio1_SET_I2C_SCL_DR(val) gpio1_scl_Write(val)

    #define gpio1_SET_I2C_SCL_HSIOM_SEL(sel) \
                          gpio1_SET_HSIOM_SEL(gpio1_SCL_HSIOM_REG,  \
                                                         gpio1_SCL_HSIOM_MASK, \
                                                         gpio1_SCL_HSIOM_POS,  \
                                                         (sel))
    #define gpio1_WAIT_SCL_SET_HIGH  (0u == gpio1_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (gpio1_RX_WAKE_SCL_MOSI_PIN)
    #define gpio1_SET_I2C_SCL_DR(val) \
                            gpio1_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define gpio1_SET_I2C_SCL_HSIOM_SEL(sel) \
                    gpio1_SET_HSIOM_SEL(gpio1_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   gpio1_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   gpio1_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define gpio1_WAIT_SCL_SET_HIGH  (0u == gpio1_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (gpio1_RX_SCL_MOSI_PIN)
    #define gpio1_SET_I2C_SCL_DR(val) \
                            gpio1_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define gpio1_SET_I2C_SCL_HSIOM_SEL(sel) \
                            gpio1_SET_HSIOM_SEL(gpio1_RX_SCL_MOSI_HSIOM_REG,  \
                                                           gpio1_RX_SCL_MOSI_HSIOM_MASK, \
                                                           gpio1_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define gpio1_WAIT_SCL_SET_HIGH  (0u == gpio1_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define gpio1_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define gpio1_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define gpio1_WAIT_SCL_SET_HIGH  (0u)
#endif /* (gpio1_I2C_PINS) */

/* SCB I2C: sda signal */
#if (gpio1_I2C_PINS)
    #define gpio1_WAIT_SDA_SET_HIGH  (0u == gpio1_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (gpio1_TX_SDA_MISO_PIN)
    #define gpio1_WAIT_SDA_SET_HIGH  (0u == gpio1_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define gpio1_WAIT_SDA_SET_HIGH  (0u)
#endif /* (gpio1_MOSI_SCL_RX_PIN) */
#endif /* (gpio1_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (gpio1_RX_SCL_MOSI_PIN)
    #define gpio1_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (gpio1_RX_WAKE_SCL_MOSI_PIN)
    #define gpio1_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) gpio1_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(gpio1_UART_RX_WAKE_PIN)
    #define gpio1_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) gpio1_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (gpio1_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define gpio1_REMOVE_MOSI_SCL_RX_WAKE_PIN    gpio1_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define gpio1_REMOVE_MOSI_SCL_RX_PIN         gpio1_REMOVE_RX_SCL_MOSI_PIN
#define gpio1_REMOVE_MISO_SDA_TX_PIN         gpio1_REMOVE_TX_SDA_MISO_PIN
#ifndef gpio1_REMOVE_SCLK_PIN
#define gpio1_REMOVE_SCLK_PIN                gpio1_REMOVE_CTS_SCLK_PIN
#endif /* gpio1_REMOVE_SCLK_PIN */
#ifndef gpio1_REMOVE_SS0_PIN
#define gpio1_REMOVE_SS0_PIN                 gpio1_REMOVE_RTS_SS0_PIN
#endif /* gpio1_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define gpio1_MOSI_SCL_RX_WAKE_PIN   gpio1_RX_WAKE_SCL_MOSI_PIN
#define gpio1_MOSI_SCL_RX_PIN        gpio1_RX_SCL_MOSI_PIN
#define gpio1_MISO_SDA_TX_PIN        gpio1_TX_SDA_MISO_PIN
#ifndef gpio1_SCLK_PIN
#define gpio1_SCLK_PIN               gpio1_CTS_SCLK_PIN
#endif /* gpio1_SCLK_PIN */
#ifndef gpio1_SS0_PIN
#define gpio1_SS0_PIN                gpio1_RTS_SS0_PIN
#endif /* gpio1_SS0_PIN */

#if (gpio1_MOSI_SCL_RX_WAKE_PIN)
    #define gpio1_MOSI_SCL_RX_WAKE_HSIOM_REG     gpio1_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define gpio1_MOSI_SCL_RX_WAKE_HSIOM_PTR     gpio1_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define gpio1_MOSI_SCL_RX_WAKE_HSIOM_MASK    gpio1_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define gpio1_MOSI_SCL_RX_WAKE_HSIOM_POS     gpio1_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define gpio1_MOSI_SCL_RX_WAKE_INTCFG_REG    gpio1_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define gpio1_MOSI_SCL_RX_WAKE_INTCFG_PTR    gpio1_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define gpio1_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   gpio1_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define gpio1_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  gpio1_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (gpio1_RX_WAKE_SCL_MOSI_PIN) */

#if (gpio1_MOSI_SCL_RX_PIN)
    #define gpio1_MOSI_SCL_RX_HSIOM_REG      gpio1_RX_SCL_MOSI_HSIOM_REG
    #define gpio1_MOSI_SCL_RX_HSIOM_PTR      gpio1_RX_SCL_MOSI_HSIOM_PTR
    #define gpio1_MOSI_SCL_RX_HSIOM_MASK     gpio1_RX_SCL_MOSI_HSIOM_MASK
    #define gpio1_MOSI_SCL_RX_HSIOM_POS      gpio1_RX_SCL_MOSI_HSIOM_POS
#endif /* (gpio1_MOSI_SCL_RX_PIN) */

#if (gpio1_MISO_SDA_TX_PIN)
    #define gpio1_MISO_SDA_TX_HSIOM_REG      gpio1_TX_SDA_MISO_HSIOM_REG
    #define gpio1_MISO_SDA_TX_HSIOM_PTR      gpio1_TX_SDA_MISO_HSIOM_REG
    #define gpio1_MISO_SDA_TX_HSIOM_MASK     gpio1_TX_SDA_MISO_HSIOM_REG
    #define gpio1_MISO_SDA_TX_HSIOM_POS      gpio1_TX_SDA_MISO_HSIOM_REG
#endif /* (gpio1_MISO_SDA_TX_PIN_PIN) */

#if (gpio1_SCLK_PIN)
    #ifndef gpio1_SCLK_HSIOM_REG
    #define gpio1_SCLK_HSIOM_REG     gpio1_CTS_SCLK_HSIOM_REG
    #define gpio1_SCLK_HSIOM_PTR     gpio1_CTS_SCLK_HSIOM_PTR
    #define gpio1_SCLK_HSIOM_MASK    gpio1_CTS_SCLK_HSIOM_MASK
    #define gpio1_SCLK_HSIOM_POS     gpio1_CTS_SCLK_HSIOM_POS
    #endif /* gpio1_SCLK_HSIOM_REG */
#endif /* (gpio1_SCLK_PIN) */

#if (gpio1_SS0_PIN)
    #ifndef gpio1_SS0_HSIOM_REG
    #define gpio1_SS0_HSIOM_REG      gpio1_RTS_SS0_HSIOM_REG
    #define gpio1_SS0_HSIOM_PTR      gpio1_RTS_SS0_HSIOM_PTR
    #define gpio1_SS0_HSIOM_MASK     gpio1_RTS_SS0_HSIOM_MASK
    #define gpio1_SS0_HSIOM_POS      gpio1_RTS_SS0_HSIOM_POS
    #endif /* gpio1_SS0_HSIOM_REG */
#endif /* (gpio1_SS0_PIN) */

#define gpio1_MOSI_SCL_RX_WAKE_PIN_INDEX gpio1_RX_WAKE_SCL_MOSI_PIN_INDEX
#define gpio1_MOSI_SCL_RX_PIN_INDEX      gpio1_RX_SCL_MOSI_PIN_INDEX
#define gpio1_MISO_SDA_TX_PIN_INDEX      gpio1_TX_SDA_MISO_PIN_INDEX
#ifndef gpio1_SCLK_PIN_INDEX
#define gpio1_SCLK_PIN_INDEX             gpio1_CTS_SCLK_PIN_INDEX
#endif /* gpio1_SCLK_PIN_INDEX */
#ifndef gpio1_SS0_PIN_INDEX
#define gpio1_SS0_PIN_INDEX              gpio1_RTS_SS0_PIN_INDEX
#endif /* gpio1_SS0_PIN_INDEX */

#define gpio1_MOSI_SCL_RX_WAKE_PIN_MASK gpio1_RX_WAKE_SCL_MOSI_PIN_MASK
#define gpio1_MOSI_SCL_RX_PIN_MASK      gpio1_RX_SCL_MOSI_PIN_MASK
#define gpio1_MISO_SDA_TX_PIN_MASK      gpio1_TX_SDA_MISO_PIN_MASK
#ifndef gpio1_SCLK_PIN_MASK
#define gpio1_SCLK_PIN_MASK             gpio1_CTS_SCLK_PIN_MASK
#endif /* gpio1_SCLK_PIN_MASK */
#ifndef gpio1_SS0_PIN_MASK
#define gpio1_SS0_PIN_MASK              gpio1_RTS_SS0_PIN_MASK
#endif /* gpio1_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_gpio1_H) */


/* [] END OF FILE */
