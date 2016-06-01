/*******************************************************************************
* File Name: console_SPI_UART_PVT.h
* Version 3.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_console_H)
#define CY_SCB_SPI_UART_PVT_console_H

#include "console_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (console_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  console_rxBufferHead;
    extern volatile uint32  console_rxBufferTail;
    extern volatile uint8   console_rxBufferOverflow;
#endif /* (console_INTERNAL_RX_SW_BUFFER_CONST) */

#if (console_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  console_txBufferHead;
    extern volatile uint32  console_txBufferTail;
#endif /* (console_INTERNAL_TX_SW_BUFFER_CONST) */

#if (console_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 console_rxBufferInternal[console_INTERNAL_RX_BUFFER_SIZE];
#endif /* (console_INTERNAL_RX_SW_BUFFER) */

#if (console_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 console_txBufferInternal[console_TX_BUFFER_SIZE];
#endif /* (console_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void console_SpiPostEnable(void);
void console_SpiStop(void);

#if (console_SCB_MODE_SPI_CONST_CFG)
    void console_SpiInit(void);
#endif /* (console_SCB_MODE_SPI_CONST_CFG) */

#if (console_SPI_WAKE_ENABLE_CONST)
    void console_SpiSaveConfig(void);
    void console_SpiRestoreConfig(void);
#endif /* (console_SPI_WAKE_ENABLE_CONST) */

void console_UartPostEnable(void);
void console_UartStop(void);

#if (console_SCB_MODE_UART_CONST_CFG)
    void console_UartInit(void);
#endif /* (console_SCB_MODE_UART_CONST_CFG) */

#if (console_UART_WAKE_ENABLE_CONST)
    void console_UartSaveConfig(void);
    void console_UartRestoreConfig(void);
#endif /* (console_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in console_SetPins() */
#define console_UART_RX_PIN_ENABLE    (console_UART_RX)
#define console_UART_TX_PIN_ENABLE    (console_UART_TX)

/* UART RTS and CTS position to be used in  console_SetPins() */
#define console_UART_RTS_PIN_ENABLE    (0x10u)
#define console_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define console_SpiUartEnableIntRx(intSourceMask)  console_SetRxInterruptMode(intSourceMask)
#define console_SpiUartEnableIntTx(intSourceMask)  console_SetTxInterruptMode(intSourceMask)
uint32  console_SpiUartDisableIntRx(void);
uint32  console_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_console_H) */


/* [] END OF FILE */
