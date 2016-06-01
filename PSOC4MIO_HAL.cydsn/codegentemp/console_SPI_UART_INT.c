/*******************************************************************************
* File Name: console_SPI_UART_INT.c
* Version 3.10
*
* Description:
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "console_PVT.h"
#include "console_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (console_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: console_SPI_UART_ISR
********************************************************************************
*
* Summary:
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(console_SPI_UART_ISR)
{
#if (console_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (console_INTERNAL_RX_SW_BUFFER_CONST) */

#if (console_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (console_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef console_SPI_UART_ISR_ENTRY_CALLBACK
    console_SPI_UART_ISR_EntryCallback();
#endif /* console_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != console_customIntrHandler)
    {
        console_customIntrHandler();
    }

    #if (console_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        console_ClearSpiExtClkInterruptSource(console_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (console_CHECK_RX_SW_BUFFER)
    {
        if (console_CHECK_INTR_RX_MASKED(console_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (console_rxBufferHead + 1u);

                /* Adjust local head index */
                if (console_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == console_rxBufferTail)
                {
                    #if (console_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        console_INTR_RX_MASK_REG &= ~console_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) console_RX_FIFO_RD_REG;
                        console_rxBufferOverflow = (uint8) console_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    console_PutWordInRxBuffer(locHead, console_RX_FIFO_RD_REG);

                    /* Move head index */
                    console_rxBufferHead = locHead;
                }
            }
            while(0u != console_GET_RX_FIFO_ENTRIES);

            console_ClearRxInterruptSource(console_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (console_CHECK_TX_SW_BUFFER)
    {
        if (console_CHECK_INTR_TX_MASKED(console_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (console_txBufferHead != console_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (console_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (console_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    console_TX_FIFO_WR_REG = console_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    console_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    console_DISABLE_INTR_TX(console_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (console_SPI_UART_FIFO_SIZE != console_GET_TX_FIFO_ENTRIES);

            console_ClearTxInterruptSource(console_INTR_TX_NOT_FULL);
        }
    }
    #endif
    
#ifdef console_SPI_UART_ISR_EXIT_CALLBACK
    console_SPI_UART_ISR_ExitCallback();
#endif /* console_SPI_UART_ISR_EXIT_CALLBACK */
    
}

#endif /* (console_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
