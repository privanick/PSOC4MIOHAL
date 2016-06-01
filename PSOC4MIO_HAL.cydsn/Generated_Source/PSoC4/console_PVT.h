/*******************************************************************************
* File Name: .h
* Version 3.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_console_H)
#define CY_SCB_PVT_console_H

#include "console.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define console_SetI2CExtClkInterruptMode(interruptMask) console_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define console_ClearI2CExtClkInterruptSource(interruptMask) console_CLEAR_INTR_I2C_EC(interruptMask)
#define console_GetI2CExtClkInterruptSource()                (console_INTR_I2C_EC_REG)
#define console_GetI2CExtClkInterruptMode()                  (console_INTR_I2C_EC_MASK_REG)
#define console_GetI2CExtClkInterruptSourceMasked()          (console_INTR_I2C_EC_MASKED_REG)

#if (!console_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define console_SetSpiExtClkInterruptMode(interruptMask) \
                                                                console_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define console_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                console_CLEAR_INTR_SPI_EC(interruptMask)
    #define console_GetExtSpiClkInterruptSource()                 (console_INTR_SPI_EC_REG)
    #define console_GetExtSpiClkInterruptMode()                   (console_INTR_SPI_EC_MASK_REG)
    #define console_GetExtSpiClkInterruptSourceMasked()           (console_INTR_SPI_EC_MASKED_REG)
#endif /* (!console_CY_SCBIP_V1) */

#if(console_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void console_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (console_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_console_CUSTOM_INTR_HANDLER)
    extern cyisraddress console_customIntrHandler;
#endif /* !defined (CY_REMOVE_console_CUSTOM_INTR_HANDLER) */
#endif /* (console_SCB_IRQ_INTERNAL) */

extern console_BACKUP_STRUCT console_backup;

#if(console_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 console_scbMode;
    extern uint8 console_scbEnableWake;
    extern uint8 console_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 console_mode;
    extern uint8 console_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * console_rxBuffer;
    extern uint8   console_rxDataBits;
    extern uint32  console_rxBufferSize;

    extern volatile uint8 * console_txBuffer;
    extern uint8   console_txDataBits;
    extern uint32  console_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 console_numberOfAddr;
    extern uint8 console_subAddrSize;
#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(console_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define console_SCB_MODE_I2C_RUNTM_CFG     (console_SCB_MODE_I2C      == console_scbMode)
    #define console_SCB_MODE_SPI_RUNTM_CFG     (console_SCB_MODE_SPI      == console_scbMode)
    #define console_SCB_MODE_UART_RUNTM_CFG    (console_SCB_MODE_UART     == console_scbMode)
    #define console_SCB_MODE_EZI2C_RUNTM_CFG   (console_SCB_MODE_EZI2C    == console_scbMode)
    #define console_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (console_SCB_MODE_UNCONFIG == console_scbMode)

    /* Defines wakeup enable */
    #define console_SCB_WAKE_ENABLE_CHECK       (0u != console_scbEnableWake)
#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!console_CY_SCBIP_V1)
    #define console_SCB_PINS_NUMBER    (7u)
#else
    #define console_SCB_PINS_NUMBER    (2u)
#endif /* (!console_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_console_H) */


/* [] END OF FILE */
