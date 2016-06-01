/*******************************************************************************
* File Name: console_SPI_UART.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "console_PVT.h"
#include "console_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(console_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 console_rxBufferHead;
    volatile uint32 console_rxBufferTail;
    volatile uint8  console_rxBufferOverflow;
#endif /* (console_INTERNAL_RX_SW_BUFFER_CONST) */

#if(console_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 console_txBufferHead;
    volatile uint32 console_txBufferTail;
#endif /* (console_INTERNAL_TX_SW_BUFFER_CONST) */

#if(console_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 console_rxBufferInternal[console_INTERNAL_RX_BUFFER_SIZE];
#endif /* (console_INTERNAL_RX_SW_BUFFER) */

#if(console_INTERNAL_TX_SW_BUFFER)
    volatile uint8 console_txBufferInternal[console_TX_BUFFER_SIZE];
#endif /* (console_INTERNAL_TX_SW_BUFFER) */


#if(console_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: console_SpiUartReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *
    * Global Variables:
    *  Look into console_SpiInit for description.
    *
    *******************************************************************************/
    uint32 console_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (console_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (console_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (console_CHECK_RX_SW_BUFFER)
        {
            if (console_rxBufferHead != console_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (console_rxBufferTail + 1u);

                if (console_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = console_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                console_rxBufferTail = locTail;

                #if (console_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (console_INTR_RX_MASK_REG & console_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        console_INTR_RX_MASK_REG |= console_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = console_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: console_SpiUartGetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of received data elements
    *
    *******************************************************************************/
    uint32 console_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (console_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (console_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (console_CHECK_RX_SW_BUFFER)
        {
            locHead = console_rxBufferHead;

            if(locHead >= console_rxBufferTail)
            {
                size = (locHead - console_rxBufferTail);
            }
            else
            {
                size = (locHead + (console_INTERNAL_RX_BUFFER_SIZE - console_rxBufferTail));
            }
        }
        #else
        {
            size = console_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: console_SpiUartClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receive buffer and RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void console_SpiUartClearRxBuffer(void)
    {
        #if (console_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            console_DisableInt();

            /* Flush RX software buffer */
            console_rxBufferHead = console_rxBufferTail;
            console_rxBufferOverflow = 0u;

            console_CLEAR_RX_FIFO;
            console_ClearRxInterruptSource(console_INTR_RX_ALL);

            #if (console_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                console_INTR_RX_MASK_REG |= console_INTR_RX_NOT_EMPTY;
            }
            #endif

            /* Release lock */
            console_EnableInt();
        }
        #else
        {
            console_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (console_RX_DIRECTION) */


#if(console_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: console_SpiUartWriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    * Parameters:
    *  txDataByte: the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void console_SpiUartWriteTxData(uint32 txData)
    {
    #if (console_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (console_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (console_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((console_txBufferHead == console_txBufferTail) &&
                (console_SPI_UART_FIFO_SIZE != console_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                console_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (console_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (console_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == console_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                console_ClearTxInterruptSource(console_INTR_TX_NOT_FULL);

                console_PutWordInTxBuffer(locHead, txData);

                console_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (console_INTR_TX_MASK_REG & console_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    console_INTR_TX_MASK_REG |= (uint32) console_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (console_SPI_UART_FIFO_SIZE == console_GET_TX_FIFO_ENTRIES)
            {
            }

            console_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: console_SpiUartPutArray
    ********************************************************************************
    *
    * Summary:
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * Parameters:
    *  wrBuf:  pointer to an array with data to be placed in transmit buffer.
    *  count:  number of data elements to be placed in the transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void console_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            console_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: console_SpiUartGetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    * Returns the number of elements currently in the transmit buffer.
    *  - TX software buffer is disabled: returns the number of used entries in
    *    TX FIFO.
    *  - TX software buffer is enabled: returns the number of elements currently
    *    used in the transmit buffer. This number does not include used entries in
    *    the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *    not full.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of data elements ready to transmit.
    *
    *******************************************************************************/
    uint32 console_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (console_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (console_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (console_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = console_txBufferTail;

            if (console_txBufferHead >= locTail)
            {
                size = (console_txBufferHead - locTail);
            }
            else
            {
                size = (console_txBufferHead + (console_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = console_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: console_SpiUartClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the transmit buffer and TX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void console_SpiUartClearTxBuffer(void)
    {
        #if (console_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            console_DisableInt();

            /* Flush TX software buffer */
            console_txBufferHead = console_txBufferTail;

            console_INTR_TX_MASK_REG &= (uint32) ~console_INTR_TX_NOT_FULL;
            console_CLEAR_TX_FIFO;
            console_ClearTxInterruptSource(console_INTR_TX_ALL);

            /* Release lock */
            console_EnableInt();
        }
        #else
        {
            console_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (console_TX_DIRECTION) */


/*******************************************************************************
* Function Name: console_SpiUartDisableIntRx
********************************************************************************
*
* Summary:
*  Disables the RX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 console_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = console_GetRxInterruptMode();

    console_SetRxInterruptMode(console_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: console_SpiUartDisableIntTx
********************************************************************************
*
* Summary:
*  Disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 console_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = console_GetTxInterruptMode();

    console_SetTxInterruptMode(console_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(console_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: console_PutWordInRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  index:      index to store data byte/word in the RX buffer.
    *  rxDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void console_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (console_ONE_BYTE_WIDTH == console_rxDataBits)
        {
            console_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            console_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            console_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: console_GetWordFromRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 console_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (console_ONE_BYTE_WIDTH == console_rxDataBits)
        {
            value = console_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) console_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)console_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: console_PutWordInTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx:        index to store data byte/word in the TX buffer.
    *  txDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void console_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (console_ONE_BYTE_WIDTH == console_txDataBits)
        {
            console_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            console_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            console_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: console_GetWordFromTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx: index to get data byte/word from the TX buffer.
    *
    * Return:
    *  Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 console_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (console_ONE_BYTE_WIDTH == console_txDataBits)
        {
            value = (uint32) console_txBuffer[idx];
        }
        else
        {
            value  = (uint32) console_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) console_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
