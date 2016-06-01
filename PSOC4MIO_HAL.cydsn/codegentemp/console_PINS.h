/*******************************************************************************
* File Name: console_PINS.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_console_H)
#define CY_SCB_PINS_console_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define console_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define console_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define console_REMOVE_TX_SDA_MISO_PIN      (1u)
#define console_REMOVE_CTS_SCLK_PIN      (1u)
#define console_REMOVE_RTS_SS0_PIN      (1u)
#define console_REMOVE_SS1_PIN                 (1u)
#define console_REMOVE_SS2_PIN                 (1u)
#define console_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define console_REMOVE_I2C_PINS                (1u)
#define console_REMOVE_SPI_MASTER_PINS         (1u)
#define console_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define console_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define console_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define console_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define console_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define console_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define console_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define console_REMOVE_SPI_SLAVE_PINS          (1u)
#define console_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define console_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define console_REMOVE_UART_TX_PIN             (0u)
#define console_REMOVE_UART_RX_TX_PIN          (1u)
#define console_REMOVE_UART_RX_PIN             (0u)
#define console_REMOVE_UART_RX_WAKE_PIN        (1u)
#define console_REMOVE_UART_RTS_PIN            (1u)
#define console_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define console_RX_WAKE_SCL_MOSI_PIN (0u == console_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define console_RX_SCL_MOSI_PIN     (0u == console_REMOVE_RX_SCL_MOSI_PIN)
#define console_TX_SDA_MISO_PIN     (0u == console_REMOVE_TX_SDA_MISO_PIN)
#define console_CTS_SCLK_PIN     (0u == console_REMOVE_CTS_SCLK_PIN)
#define console_RTS_SS0_PIN     (0u == console_REMOVE_RTS_SS0_PIN)
#define console_SS1_PIN                (0u == console_REMOVE_SS1_PIN)
#define console_SS2_PIN                (0u == console_REMOVE_SS2_PIN)
#define console_SS3_PIN                (0u == console_REMOVE_SS3_PIN)

/* Mode defined pins */
#define console_I2C_PINS               (0u == console_REMOVE_I2C_PINS)
#define console_SPI_MASTER_PINS        (0u == console_REMOVE_SPI_MASTER_PINS)
#define console_SPI_MASTER_SCLK_PIN    (0u == console_REMOVE_SPI_MASTER_SCLK_PIN)
#define console_SPI_MASTER_MOSI_PIN    (0u == console_REMOVE_SPI_MASTER_MOSI_PIN)
#define console_SPI_MASTER_MISO_PIN    (0u == console_REMOVE_SPI_MASTER_MISO_PIN)
#define console_SPI_MASTER_SS0_PIN     (0u == console_REMOVE_SPI_MASTER_SS0_PIN)
#define console_SPI_MASTER_SS1_PIN     (0u == console_REMOVE_SPI_MASTER_SS1_PIN)
#define console_SPI_MASTER_SS2_PIN     (0u == console_REMOVE_SPI_MASTER_SS2_PIN)
#define console_SPI_MASTER_SS3_PIN     (0u == console_REMOVE_SPI_MASTER_SS3_PIN)
#define console_SPI_SLAVE_PINS         (0u == console_REMOVE_SPI_SLAVE_PINS)
#define console_SPI_SLAVE_MOSI_PIN     (0u == console_REMOVE_SPI_SLAVE_MOSI_PIN)
#define console_SPI_SLAVE_MISO_PIN     (0u == console_REMOVE_SPI_SLAVE_MISO_PIN)
#define console_UART_TX_PIN            (0u == console_REMOVE_UART_TX_PIN)
#define console_UART_RX_TX_PIN         (0u == console_REMOVE_UART_RX_TX_PIN)
#define console_UART_RX_PIN            (0u == console_REMOVE_UART_RX_PIN)
#define console_UART_RX_WAKE_PIN       (0u == console_REMOVE_UART_RX_WAKE_PIN)
#define console_UART_RTS_PIN           (0u == console_REMOVE_UART_RTS_PIN)
#define console_UART_CTS_PIN           (0u == console_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (console_RX_WAKE_SCL_MOSI_PIN)
    #include "console_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (console_RX_SCL_MOSI) */

#if (console_RX_SCL_MOSI_PIN)
    #include "console_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (console_RX_SCL_MOSI) */

#if (console_TX_SDA_MISO_PIN)
    #include "console_uart_tx_i2c_sda_spi_miso.h"
#endif /* (console_TX_SDA_MISO) */

#if (console_CTS_SCLK_PIN)
    #include "console_uart_cts_spi_sclk.h"
#endif /* (console_CTS_SCLK) */

#if (console_RTS_SS0_PIN)
    #include "console_uart_rts_spi_ss0.h"
#endif /* (console_RTS_SS0_PIN) */

#if (console_SS1_PIN)
    #include "console_spi_ss1.h"
#endif /* (console_SS1_PIN) */

#if (console_SS2_PIN)
    #include "console_spi_ss2.h"
#endif /* (console_SS2_PIN) */

#if (console_SS3_PIN)
    #include "console_spi_ss3.h"
#endif /* (console_SS3_PIN) */

#if (console_I2C_PINS)
    #include "console_scl.h"
    #include "console_sda.h"
#endif /* (console_I2C_PINS) */

#if (console_SPI_MASTER_PINS)
#if (console_SPI_MASTER_SCLK_PIN)
    #include "console_sclk_m.h"
#endif /* (console_SPI_MASTER_SCLK_PIN) */

#if (console_SPI_MASTER_MOSI_PIN)
    #include "console_mosi_m.h"
#endif /* (console_SPI_MASTER_MOSI_PIN) */

#if (console_SPI_MASTER_MISO_PIN)
    #include "console_miso_m.h"
#endif /*(console_SPI_MASTER_MISO_PIN) */
#endif /* (console_SPI_MASTER_PINS) */

#if (console_SPI_SLAVE_PINS)
    #include "console_sclk_s.h"
    #include "console_ss_s.h"

#if (console_SPI_SLAVE_MOSI_PIN)
    #include "console_mosi_s.h"
#endif /* (console_SPI_SLAVE_MOSI_PIN) */

#if (console_SPI_SLAVE_MISO_PIN)
    #include "console_miso_s.h"
#endif /*(console_SPI_SLAVE_MISO_PIN) */
#endif /* (console_SPI_SLAVE_PINS) */

#if (console_SPI_MASTER_SS0_PIN)
    #include "console_ss0_m.h"
#endif /* (console_SPI_MASTER_SS0_PIN) */

#if (console_SPI_MASTER_SS1_PIN)
    #include "console_ss1_m.h"
#endif /* (console_SPI_MASTER_SS1_PIN) */

#if (console_SPI_MASTER_SS2_PIN)
    #include "console_ss2_m.h"
#endif /* (console_SPI_MASTER_SS2_PIN) */

#if (console_SPI_MASTER_SS3_PIN)
    #include "console_ss3_m.h"
#endif /* (console_SPI_MASTER_SS3_PIN) */

#if (console_UART_TX_PIN)
    #include "console_tx.h"
#endif /* (console_UART_TX_PIN) */

#if (console_UART_RX_TX_PIN)
    #include "console_rx_tx.h"
#endif /* (console_UART_RX_TX_PIN) */

#if (console_UART_RX_PIN)
    #include "console_rx.h"
#endif /* (console_UART_RX_PIN) */

#if (console_UART_RX_WAKE_PIN)
    #include "console_rx_wake.h"
#endif /* (console_UART_RX_WAKE_PIN) */

#if (console_UART_RTS_PIN)
    #include "console_rts.h"
#endif /* (console_UART_RTS_PIN) */

#if (console_UART_CTS_PIN)
    #include "console_cts.h"
#endif /* (console_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (console_RX_WAKE_SCL_MOSI_PIN)
    #define console_RX_WAKE_SCL_MOSI_HSIOM_REG \
                            (*(reg32 *) console_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define console_RX_WAKE_SCL_MOSI_HSIOM_PTR \
                            ( (reg32 *) console_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define console_RX_WAKE_SCL_MOSI_HSIOM_MASK \
                            (console_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define console_RX_WAKE_SCL_MOSI_HSIOM_POS \
                            (console_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)

    #define console_RX_WAKE_SCL_MOSI_INTCFG_REG \
                            (*(reg32 *) console_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define console_RX_WAKE_SCL_MOSI_INTCFG_PTR \
                            ( (reg32 *) console_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define console_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (console_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define console_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK \
                            ((uint32) console_INTCFG_TYPE_MASK << \
                                      console_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#endif /* (console_RX_WAKE_SCL_MOSI_PIN) */

#if (console_RX_SCL_MOSI_PIN)
    #define console_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) console_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define console_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) console_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define console_RX_SCL_MOSI_HSIOM_MASK  (console_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define console_RX_SCL_MOSI_HSIOM_POS   (console_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
#endif /* (console_RX_SCL_MOSI_PIN) */

#if (console_TX_SDA_MISO_PIN)
    #define console_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) console_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define console_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) console_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define console_TX_SDA_MISO_HSIOM_MASK  (console_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define console_TX_SDA_MISO_HSIOM_POS   (console_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
#endif /* (console_TX_SDA_MISO_PIN) */

#if (console_CTS_SCLK_PIN)
    #define console_CTS_SCLK_HSIOM_REG   (*(reg32 *) console_uart_cts_spi_sclk__0__HSIOM)
    #define console_CTS_SCLK_HSIOM_PTR   ( (reg32 *) console_uart_cts_spi_sclk__0__HSIOM)
    #define console_CTS_SCLK_HSIOM_MASK  (console_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define console_CTS_SCLK_HSIOM_POS   (console_uart_cts_spi_sclk__0__HSIOM_SHIFT)
#endif /* (console_CTS_SCLK_PIN) */

#if (console_RTS_SS0_PIN)
    #define console_RTS_SS0_HSIOM_REG   (*(reg32 *) console_uart_rts_spi_ss0__0__HSIOM)
    #define console_RTS_SS0_HSIOM_PTR   ( (reg32 *) console_uart_rts_spi_ss0__0__HSIOM)
    #define console_RTS_SS0_HSIOM_MASK  (console_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define console_RTS_SS0_HSIOM_POS   (console_uart_rts_spi_ss0__0__HSIOM_SHIFT)
#endif /* (console_RTS_SS0_PIN) */

#if (console_SS1_PIN)
    #define console_SS1_HSIOM_REG      (*(reg32 *) console_spi_ss1__0__HSIOM)
    #define console_SS1_HSIOM_PTR      ( (reg32 *) console_spi_ss1__0__HSIOM)
    #define console_SS1_HSIOM_MASK     (console_spi_ss1__0__HSIOM_MASK)
    #define console_SS1_HSIOM_POS      (console_spi_ss1__0__HSIOM_SHIFT)
#endif /* (console_SS1_PIN) */

#if (console_SS2_PIN)
    #define console_SS2_HSIOM_REG     (*(reg32 *) console_spi_ss2__0__HSIOM)
    #define console_SS2_HSIOM_PTR     ( (reg32 *) console_spi_ss2__0__HSIOM)
    #define console_SS2_HSIOM_MASK    (console_spi_ss2__0__HSIOM_MASK)
    #define console_SS2_HSIOM_POS     (console_spi_ss2__0__HSIOM_SHIFT)
#endif /* (console_SS2_PIN) */

#if (console_SS3_PIN)
    #define console_SS3_HSIOM_REG     (*(reg32 *) console_spi_ss3__0__HSIOM)
    #define console_SS3_HSIOM_PTR     ( (reg32 *) console_spi_ss3__0__HSIOM)
    #define console_SS3_HSIOM_MASK    (console_spi_ss3__0__HSIOM_MASK)
    #define console_SS3_HSIOM_POS     (console_spi_ss3__0__HSIOM_SHIFT)
#endif /* (console_SS3_PIN) */

#if (console_I2C_PINS)
    #define console_SCL_HSIOM_REG     (*(reg32 *) console_scl__0__HSIOM)
    #define console_SCL_HSIOM_PTR     ( (reg32 *) console_scl__0__HSIOM)
    #define console_SCL_HSIOM_MASK    (console_scl__0__HSIOM_MASK)
    #define console_SCL_HSIOM_POS     (console_scl__0__HSIOM_SHIFT)

    #define console_SDA_HSIOM_REG     (*(reg32 *) console_sda__0__HSIOM)
    #define console_SDA_HSIOM_PTR     ( (reg32 *) console_sda__0__HSIOM)
    #define console_SDA_HSIOM_MASK    (console_sda__0__HSIOM_MASK)
    #define console_SDA_HSIOM_POS     (console_sda__0__HSIOM_SHIFT)
#endif /* (console_I2C_PINS) */

#if (console_SPI_MASTER_SCLK_PIN)
    #define console_SCLK_M_HSIOM_REG   (*(reg32 *) console_sclk_m__0__HSIOM)
    #define console_SCLK_M_HSIOM_PTR   ( (reg32 *) console_sclk_m__0__HSIOM)
    #define console_SCLK_M_HSIOM_MASK  (console_sclk_m__0__HSIOM_MASK)
    #define console_SCLK_M_HSIOM_POS   (console_sclk_m__0__HSIOM_SHIFT)
#endif /* (console_SPI_MASTER_SCLK_PIN) */

#if (console_SPI_MASTER_SS0_PIN)
    #define console_SS0_M_HSIOM_REG    (*(reg32 *) console_ss0_m__0__HSIOM)
    #define console_SS0_M_HSIOM_PTR    ( (reg32 *) console_ss0_m__0__HSIOM)
    #define console_SS0_M_HSIOM_MASK   (console_ss0_m__0__HSIOM_MASK)
    #define console_SS0_M_HSIOM_POS    (console_ss0_m__0__HSIOM_SHIFT)
#endif /* (console_SPI_MASTER_SS0_PIN) */

#if (console_SPI_MASTER_SS1_PIN)
    #define console_SS1_M_HSIOM_REG    (*(reg32 *) console_ss1_m__0__HSIOM)
    #define console_SS1_M_HSIOM_PTR    ( (reg32 *) console_ss1_m__0__HSIOM)
    #define console_SS1_M_HSIOM_MASK   (console_ss1_m__0__HSIOM_MASK)
    #define console_SS1_M_HSIOM_POS    (console_ss1_m__0__HSIOM_SHIFT)
#endif /* (console_SPI_MASTER_SS1_PIN) */

#if (console_SPI_MASTER_SS2_PIN)
    #define console_SS2_M_HSIOM_REG    (*(reg32 *) console_ss2_m__0__HSIOM)
    #define console_SS2_M_HSIOM_PTR    ( (reg32 *) console_ss2_m__0__HSIOM)
    #define console_SS2_M_HSIOM_MASK   (console_ss2_m__0__HSIOM_MASK)
    #define console_SS2_M_HSIOM_POS    (console_ss2_m__0__HSIOM_SHIFT)
#endif /* (console_SPI_MASTER_SS2_PIN) */

#if (console_SPI_MASTER_SS3_PIN)
    #define console_SS3_M_HSIOM_REG    (*(reg32 *) console_ss3_m__0__HSIOM)
    #define console_SS3_M_HSIOM_PTR    ( (reg32 *) console_ss3_m__0__HSIOM)
    #define console_SS3_M_HSIOM_MASK   (console_ss3_m__0__HSIOM_MASK)
    #define console_SS3_M_HSIOM_POS    (console_ss3_m__0__HSIOM_SHIFT)
#endif /* (console_SPI_MASTER_SS3_PIN) */

#if (console_UART_TX_PIN)
    #define console_TX_HSIOM_REG   (*(reg32 *) console_tx__0__HSIOM)
    #define console_TX_HSIOM_PTR   ( (reg32 *) console_tx_0__HSIOM)
    #define console_TX_HSIOM_MASK  (console_tx__0__HSIOM_MASK)
    #define console_TX_HSIOM_POS   (console_tx__0__HSIOM_SHIFT)
#endif /* (console_UART_TX_PIN) */

#if (console_UART_RTS_PIN)
    #define console_RTS_HSIOM_REG  (*(reg32 *) console_rts__0__HSIOM)
    #define console_RTS_HSIOM_PTR  ( (reg32 *) console_rts__0__HSIOM)
    #define console_RTS_HSIOM_MASK (console_rts__0__HSIOM_MASK)
    #define console_RTS_HSIOM_POS  (console_rts__0__HSIOM_SHIFT)
#endif /* (console_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define console_HSIOM_DEF_SEL      (0x00u)
#define console_HSIOM_GPIO_SEL     (0x00u)
#define console_HSIOM_UART_SEL     (0x09u)
#define console_HSIOM_I2C_SEL      (0x0Eu)
#define console_HSIOM_SPI_SEL      (0x0Fu)

#define console_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define console_RX_SCL_MOSI_PIN_INDEX       (0u)
#define console_TX_SDA_MISO_PIN_INDEX       (1u)
#define console_CTS_SCLK_PIN_INDEX       (2u)
#define console_RTS_SS0_PIN_INDEX       (3u)
#define console_SS1_PIN_INDEX                  (4u)
#define console_SS2_PIN_INDEX                  (5u)
#define console_SS3_PIN_INDEX                  (6u)

#define console_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << console_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define console_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << console_RX_SCL_MOSI_PIN_INDEX)
#define console_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << console_TX_SDA_MISO_PIN_INDEX)
#define console_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << console_CTS_SCLK_PIN_INDEX)
#define console_RTS_SS0_PIN_MASK     ((uint32) 0x01u << console_RTS_SS0_PIN_INDEX)
#define console_SS1_PIN_MASK                ((uint32) 0x01u << console_SS1_PIN_INDEX)
#define console_SS2_PIN_MASK                ((uint32) 0x01u << console_SS2_PIN_INDEX)
#define console_SS3_PIN_MASK                ((uint32) 0x01u << console_SS3_PIN_INDEX)

/* Pin interrupt constants */
#define console_INTCFG_TYPE_MASK           (0x03u)
#define console_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants */
#define console_PIN_DM_ALG_HIZ  (0u)
#define console_PIN_DM_DIG_HIZ  (1u)
#define console_PIN_DM_OD_LO    (4u)
#define console_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define console_DM_MASK    (0x7u)
#define console_DM_SIZE    (3)
#define console_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) console_DM_MASK << (console_DM_SIZE * (pos)))) >> \
                                                              (console_DM_SIZE * (pos)) )

#if (console_TX_SDA_MISO_PIN)
    #define console_CHECK_TX_SDA_MISO_PIN_USED \
                (console_PIN_DM_ALG_HIZ != \
                    console_GET_P4_PIN_DM(console_uart_tx_i2c_sda_spi_miso_PC, \
                                                   console_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (console_TX_SDA_MISO_PIN) */

#if (console_RTS_SS0_PIN)
    #define console_CHECK_RTS_SS0_PIN_USED \
                (console_PIN_DM_ALG_HIZ != \
                    console_GET_P4_PIN_DM(console_uart_rts_spi_ss0_PC, \
                                                   console_uart_rts_spi_ss0_SHIFT))
#endif /* (console_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define console_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define console_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define console_SET_HSIOM_SEL(reg, mask, pos, sel) console_SET_REGISTER_BITS(reg, mask, pos, sel)
#define console_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        console_SET_REGISTER_BITS(reg, mask, pos, intType)
#define console_SET_INP_DIS(reg, mask, val) console_SET_REGISTER_BIT(reg, mask, val)

/* console_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  console_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (console_CY_SCBIP_V0)
#if (console_I2C_PINS)
    #define console_SET_I2C_SCL_DR(val) console_scl_Write(val)

    #define console_SET_I2C_SCL_HSIOM_SEL(sel) \
                          console_SET_HSIOM_SEL(console_SCL_HSIOM_REG,  \
                                                         console_SCL_HSIOM_MASK, \
                                                         console_SCL_HSIOM_POS,  \
                                                         (sel))
    #define console_WAIT_SCL_SET_HIGH  (0u == console_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (console_RX_WAKE_SCL_MOSI_PIN)
    #define console_SET_I2C_SCL_DR(val) \
                            console_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define console_SET_I2C_SCL_HSIOM_SEL(sel) \
                    console_SET_HSIOM_SEL(console_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   console_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   console_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define console_WAIT_SCL_SET_HIGH  (0u == console_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (console_RX_SCL_MOSI_PIN)
    #define console_SET_I2C_SCL_DR(val) \
                            console_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define console_SET_I2C_SCL_HSIOM_SEL(sel) \
                            console_SET_HSIOM_SEL(console_RX_SCL_MOSI_HSIOM_REG,  \
                                                           console_RX_SCL_MOSI_HSIOM_MASK, \
                                                           console_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define console_WAIT_SCL_SET_HIGH  (0u == console_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define console_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define console_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define console_WAIT_SCL_SET_HIGH  (0u)
#endif /* (console_I2C_PINS) */

/* SCB I2C: sda signal */
#if (console_I2C_PINS)
    #define console_WAIT_SDA_SET_HIGH  (0u == console_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (console_TX_SDA_MISO_PIN)
    #define console_WAIT_SDA_SET_HIGH  (0u == console_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define console_WAIT_SDA_SET_HIGH  (0u)
#endif /* (console_MOSI_SCL_RX_PIN) */
#endif /* (console_CY_SCBIP_V0) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define console_REMOVE_MOSI_SCL_RX_WAKE_PIN    console_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define console_REMOVE_MOSI_SCL_RX_PIN         console_REMOVE_RX_SCL_MOSI_PIN
#define console_REMOVE_MISO_SDA_TX_PIN         console_REMOVE_TX_SDA_MISO_PIN
#ifndef console_REMOVE_SCLK_PIN
#define console_REMOVE_SCLK_PIN                console_REMOVE_CTS_SCLK_PIN
#endif /* console_REMOVE_SCLK_PIN */
#ifndef console_REMOVE_SS0_PIN
#define console_REMOVE_SS0_PIN                 console_REMOVE_RTS_SS0_PIN
#endif /* console_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define console_MOSI_SCL_RX_WAKE_PIN   console_RX_WAKE_SCL_MOSI_PIN
#define console_MOSI_SCL_RX_PIN        console_RX_SCL_MOSI_PIN
#define console_MISO_SDA_TX_PIN        console_TX_SDA_MISO_PIN
#ifndef console_SCLK_PIN
#define console_SCLK_PIN               console_CTS_SCLK_PIN
#endif /* console_SCLK_PIN */
#ifndef console_SS0_PIN
#define console_SS0_PIN                console_RTS_SS0_PIN
#endif /* console_SS0_PIN */

#if (console_MOSI_SCL_RX_WAKE_PIN)
    #define console_MOSI_SCL_RX_WAKE_HSIOM_REG     console_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define console_MOSI_SCL_RX_WAKE_HSIOM_PTR     console_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define console_MOSI_SCL_RX_WAKE_HSIOM_MASK    console_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define console_MOSI_SCL_RX_WAKE_HSIOM_POS     console_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define console_MOSI_SCL_RX_WAKE_INTCFG_REG    console_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define console_MOSI_SCL_RX_WAKE_INTCFG_PTR    console_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define console_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   console_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define console_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  console_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (console_RX_WAKE_SCL_MOSI_PIN) */

#if (console_MOSI_SCL_RX_PIN)
    #define console_MOSI_SCL_RX_HSIOM_REG      console_RX_SCL_MOSI_HSIOM_REG
    #define console_MOSI_SCL_RX_HSIOM_PTR      console_RX_SCL_MOSI_HSIOM_PTR
    #define console_MOSI_SCL_RX_HSIOM_MASK     console_RX_SCL_MOSI_HSIOM_MASK
    #define console_MOSI_SCL_RX_HSIOM_POS      console_RX_SCL_MOSI_HSIOM_POS
#endif /* (console_MOSI_SCL_RX_PIN) */

#if (console_MISO_SDA_TX_PIN)
    #define console_MISO_SDA_TX_HSIOM_REG      console_TX_SDA_MISO_HSIOM_REG
    #define console_MISO_SDA_TX_HSIOM_PTR      console_TX_SDA_MISO_HSIOM_REG
    #define console_MISO_SDA_TX_HSIOM_MASK     console_TX_SDA_MISO_HSIOM_REG
    #define console_MISO_SDA_TX_HSIOM_POS      console_TX_SDA_MISO_HSIOM_REG
#endif /* (console_MISO_SDA_TX_PIN_PIN) */

#if (console_SCLK_PIN)
    #ifndef console_SCLK_HSIOM_REG
    #define console_SCLK_HSIOM_REG     console_CTS_SCLK_HSIOM_REG
    #define console_SCLK_HSIOM_PTR     console_CTS_SCLK_HSIOM_PTR
    #define console_SCLK_HSIOM_MASK    console_CTS_SCLK_HSIOM_MASK
    #define console_SCLK_HSIOM_POS     console_CTS_SCLK_HSIOM_POS
    #endif /* console_SCLK_HSIOM_REG */
#endif /* (console_SCLK_PIN) */

#if (console_SS0_PIN)
    #ifndef console_SS0_HSIOM_REG
    #define console_SS0_HSIOM_REG      console_RTS_SS0_HSIOM_REG
    #define console_SS0_HSIOM_PTR      console_RTS_SS0_HSIOM_PTR
    #define console_SS0_HSIOM_MASK     console_RTS_SS0_HSIOM_MASK
    #define console_SS0_HSIOM_POS      console_RTS_SS0_HSIOM_POS
    #endif /* console_SS0_HSIOM_REG */
#endif /* (console_SS0_PIN) */

#define console_MOSI_SCL_RX_WAKE_PIN_INDEX console_RX_WAKE_SCL_MOSI_PIN_INDEX
#define console_MOSI_SCL_RX_PIN_INDEX      console_RX_SCL_MOSI_PIN_INDEX
#define console_MISO_SDA_TX_PIN_INDEX      console_TX_SDA_MISO_PIN_INDEX
#ifndef console_SCLK_PIN_INDEX
#define console_SCLK_PIN_INDEX             console_CTS_SCLK_PIN_INDEX
#endif /* console_SCLK_PIN_INDEX */
#ifndef console_SS0_PIN_INDEX
#define console_SS0_PIN_INDEX              console_RTS_SS0_PIN_INDEX
#endif /* console_SS0_PIN_INDEX */

#define console_MOSI_SCL_RX_WAKE_PIN_MASK console_RX_WAKE_SCL_MOSI_PIN_MASK
#define console_MOSI_SCL_RX_PIN_MASK      console_RX_SCL_MOSI_PIN_MASK
#define console_MISO_SDA_TX_PIN_MASK      console_TX_SDA_MISO_PIN_MASK
#ifndef console_SCLK_PIN_MASK
#define console_SCLK_PIN_MASK             console_CTS_SCLK_PIN_MASK
#endif /* console_SCLK_PIN_MASK */
#ifndef console_SS0_PIN_MASK
#define console_SS0_PIN_MASK              console_RTS_SS0_PIN_MASK
#endif /* console_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_console_H) */


/* [] END OF FILE */
