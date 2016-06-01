/***************************************************************************//**
* \file LCD_SPI_UART_INT.c
* \version 3.20
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
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

#include "LCD_PVT.h"
#include "LCD_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (LCD_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: LCD_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(LCD_SPI_UART_ISR)
{
#if (LCD_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (LCD_INTERNAL_RX_SW_BUFFER_CONST) */

#if (LCD_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (LCD_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef LCD_SPI_UART_ISR_ENTRY_CALLBACK
    LCD_SPI_UART_ISR_EntryCallback();
#endif /* LCD_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != LCD_customIntrHandler)
    {
        LCD_customIntrHandler();
    }

    #if(LCD_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        LCD_ClearSpiExtClkInterruptSource(LCD_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (LCD_CHECK_RX_SW_BUFFER)
    {
        if (LCD_CHECK_INTR_RX_MASKED(LCD_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (LCD_rxBufferHead + 1u);

                /* Adjust local head index */
                if (LCD_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == LCD_rxBufferTail)
                {
                    #if (LCD_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        LCD_INTR_RX_MASK_REG &= ~LCD_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) LCD_RX_FIFO_RD_REG;
                        LCD_rxBufferOverflow = (uint8) LCD_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    LCD_PutWordInRxBuffer(locHead, LCD_RX_FIFO_RD_REG);

                    /* Move head index */
                    LCD_rxBufferHead = locHead;
                }
            }
            while(0u != LCD_GET_RX_FIFO_ENTRIES);

            LCD_ClearRxInterruptSource(LCD_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (LCD_CHECK_TX_SW_BUFFER)
    {
        if (LCD_CHECK_INTR_TX_MASKED(LCD_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (LCD_txBufferHead != LCD_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (LCD_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (LCD_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    LCD_TX_FIFO_WR_REG = LCD_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    LCD_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    LCD_DISABLE_INTR_TX(LCD_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (LCD_SPI_UART_FIFO_SIZE != LCD_GET_TX_FIFO_ENTRIES);

            LCD_ClearTxInterruptSource(LCD_INTR_TX_NOT_FULL);
        }
    }
    #endif

#ifdef LCD_SPI_UART_ISR_EXIT_CALLBACK
    LCD_SPI_UART_ISR_ExitCallback();
#endif /* LCD_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (LCD_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
