/***************************************************************************//**
* \file .h
* \version 3.20
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_gpio1_H)
#define CY_SCB_PVT_gpio1_H

#include "gpio1.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define gpio1_SetI2CExtClkInterruptMode(interruptMask) gpio1_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define gpio1_ClearI2CExtClkInterruptSource(interruptMask) gpio1_CLEAR_INTR_I2C_EC(interruptMask)
#define gpio1_GetI2CExtClkInterruptSource()                (gpio1_INTR_I2C_EC_REG)
#define gpio1_GetI2CExtClkInterruptMode()                  (gpio1_INTR_I2C_EC_MASK_REG)
#define gpio1_GetI2CExtClkInterruptSourceMasked()          (gpio1_INTR_I2C_EC_MASKED_REG)

#if (!gpio1_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define gpio1_SetSpiExtClkInterruptMode(interruptMask) \
                                                                gpio1_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define gpio1_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                gpio1_CLEAR_INTR_SPI_EC(interruptMask)
    #define gpio1_GetExtSpiClkInterruptSource()                 (gpio1_INTR_SPI_EC_REG)
    #define gpio1_GetExtSpiClkInterruptMode()                   (gpio1_INTR_SPI_EC_MASK_REG)
    #define gpio1_GetExtSpiClkInterruptSourceMasked()           (gpio1_INTR_SPI_EC_MASKED_REG)
#endif /* (!gpio1_CY_SCBIP_V1) */

#if(gpio1_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void gpio1_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (gpio1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (gpio1_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_gpio1_CUSTOM_INTR_HANDLER)
    extern cyisraddress gpio1_customIntrHandler;
#endif /* !defined (CY_REMOVE_gpio1_CUSTOM_INTR_HANDLER) */
#endif /* (gpio1_SCB_IRQ_INTERNAL) */

extern gpio1_BACKUP_STRUCT gpio1_backup;

#if(gpio1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 gpio1_scbMode;
    extern uint8 gpio1_scbEnableWake;
    extern uint8 gpio1_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 gpio1_mode;
    extern uint8 gpio1_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * gpio1_rxBuffer;
    extern uint8   gpio1_rxDataBits;
    extern uint32  gpio1_rxBufferSize;

    extern volatile uint8 * gpio1_txBuffer;
    extern uint8   gpio1_txDataBits;
    extern uint32  gpio1_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 gpio1_numberOfAddr;
    extern uint8 gpio1_subAddrSize;
#endif /* (gpio1_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (gpio1_SCB_MODE_I2C_CONST_CFG || \
        gpio1_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 gpio1_IntrTxMask;
#endif /* (! (gpio1_SCB_MODE_I2C_CONST_CFG || \
              gpio1_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(gpio1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define gpio1_SCB_MODE_I2C_RUNTM_CFG     (gpio1_SCB_MODE_I2C      == gpio1_scbMode)
    #define gpio1_SCB_MODE_SPI_RUNTM_CFG     (gpio1_SCB_MODE_SPI      == gpio1_scbMode)
    #define gpio1_SCB_MODE_UART_RUNTM_CFG    (gpio1_SCB_MODE_UART     == gpio1_scbMode)
    #define gpio1_SCB_MODE_EZI2C_RUNTM_CFG   (gpio1_SCB_MODE_EZI2C    == gpio1_scbMode)
    #define gpio1_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (gpio1_SCB_MODE_UNCONFIG == gpio1_scbMode)

    /* Defines wakeup enable */
    #define gpio1_SCB_WAKE_ENABLE_CHECK       (0u != gpio1_scbEnableWake)
#endif /* (gpio1_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!gpio1_CY_SCBIP_V1)
    #define gpio1_SCB_PINS_NUMBER    (7u)
#else
    #define gpio1_SCB_PINS_NUMBER    (2u)
#endif /* (!gpio1_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_gpio1_H) */


/* [] END OF FILE */
