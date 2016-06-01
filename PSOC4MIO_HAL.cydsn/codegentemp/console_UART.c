/*******************************************************************************
* File Name: console_UART.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
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
#include "cyapicallbacks.h"

#if(console_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const console_UART_INIT_STRUCT console_configUart =
    {
        console_UART_SUB_MODE,
        console_UART_DIRECTION,
        console_UART_DATA_BITS_NUM,
        console_UART_PARITY_TYPE,
        console_UART_STOP_BITS_NUM,
        console_UART_OVS_FACTOR,
        console_UART_IRDA_LOW_POWER,
        console_UART_MEDIAN_FILTER_ENABLE,
        console_UART_RETRY_ON_NACK,
        console_UART_IRDA_POLARITY,
        console_UART_DROP_ON_PARITY_ERR,
        console_UART_DROP_ON_FRAME_ERR,
        console_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        console_UART_MP_MODE_ENABLE,
        console_UART_MP_ACCEPT_ADDRESS,
        console_UART_MP_RX_ADDRESS,
        console_UART_MP_RX_ADDRESS_MASK,
        (uint32) console_SCB_IRQ_INTERNAL,
        console_UART_INTR_RX_MASK,
        console_UART_RX_TRIGGER_LEVEL,
        console_UART_INTR_TX_MASK,
        console_UART_TX_TRIGGER_LEVEL,
        (uint8) console_UART_BYTE_MODE_ENABLE,
        (uint8) console_UART_CTS_ENABLE,
        (uint8) console_UART_CTS_POLARITY,
        (uint8) console_UART_RTS_POLARITY,
        (uint8) console_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: console_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void console_UartInit(const console_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (console_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (console_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1) */

            /* Configure pins */
            console_SetPins(console_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            console_scbMode       = (uint8) console_SCB_MODE_UART;
            console_scbEnableWake = (uint8) config->enableWake;
            console_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            console_rxBuffer      =         config->rxBuffer;
            console_rxDataBits    = (uint8) config->dataBits;
            console_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            console_txBuffer      =         config->txBuffer;
            console_txDataBits    = (uint8) config->dataBits;
            console_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(console_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                console_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (console_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (console_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                console_CTRL_REG  = console_GET_CTRL_OVS(config->oversample);
            }

            console_CTRL_REG     |= console_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             console_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             console_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            console_UART_CTRL_REG = console_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            console_UART_RX_CTRL_REG = console_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        console_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        console_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        console_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        console_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(console_UART_PARITY_NONE != config->parity)
            {
               console_UART_RX_CTRL_REG |= console_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    console_UART_RX_CTRL_PARITY_ENABLED;
            }

            console_RX_CTRL_REG      = console_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                console_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                console_GET_UART_RX_CTRL_ENABLED(config->direction);

            console_RX_FIFO_CTRL_REG = console_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            console_RX_MATCH_REG     = console_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                console_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            console_UART_TX_CTRL_REG = console_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                console_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(console_UART_PARITY_NONE != config->parity)
            {
               console_UART_TX_CTRL_REG |= console_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    console_UART_TX_CTRL_PARITY_ENABLED;
            }

            console_TX_CTRL_REG      = console_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                console_GET_UART_TX_CTRL_ENABLED(config->direction);

            console_TX_FIFO_CTRL_REG = console_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1)
            console_UART_FLOW_CTRL_REG = console_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            console_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            console_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            console_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (console_ISR_NUMBER);
            CyIntSetPriority(console_ISR_NUMBER, console_ISR_PRIORITY);
            (void) CyIntSetVector(console_ISR_NUMBER, &console_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(console_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (console_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(console_RX_WAKE_ISR_NUMBER, console_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(console_RX_WAKE_ISR_NUMBER, &console_UART_WAKEUP_ISR);
        #endif /* (console_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            console_INTR_I2C_EC_MASK_REG = console_NO_INTR_SOURCES;
            console_INTR_SPI_EC_MASK_REG = console_NO_INTR_SOURCES;
            console_INTR_SLAVE_MASK_REG  = console_NO_INTR_SOURCES;
            console_INTR_MASTER_MASK_REG = console_NO_INTR_SOURCES;
            console_INTR_RX_MASK_REG     = config->rxInterruptMask;
            console_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            console_rxBufferHead     = 0u;
            console_rxBufferTail     = 0u;
            console_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            console_txBufferHead = 0u;
            console_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: console_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void console_UartInit(void)
    {
        /* Configure UART interface */
        console_CTRL_REG = console_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        console_UART_CTRL_REG = console_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        console_UART_RX_CTRL_REG = console_UART_DEFAULT_UART_RX_CTRL;
        console_RX_CTRL_REG      = console_UART_DEFAULT_RX_CTRL;
        console_RX_FIFO_CTRL_REG = console_UART_DEFAULT_RX_FIFO_CTRL;
        console_RX_MATCH_REG     = console_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        console_UART_TX_CTRL_REG = console_UART_DEFAULT_UART_TX_CTRL;
        console_TX_CTRL_REG      = console_UART_DEFAULT_TX_CTRL;
        console_TX_FIFO_CTRL_REG = console_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1)
        console_UART_FLOW_CTRL_REG = console_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(console_SCB_IRQ_INTERNAL)
        CyIntDisable    (console_ISR_NUMBER);
        CyIntSetPriority(console_ISR_NUMBER, console_ISR_PRIORITY);
        (void) CyIntSetVector(console_ISR_NUMBER, &console_SPI_UART_ISR);
    #endif /* (console_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(console_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (console_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(console_RX_WAKE_ISR_NUMBER, console_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(console_RX_WAKE_ISR_NUMBER, &console_UART_WAKEUP_ISR);
    #endif /* (console_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        console_INTR_I2C_EC_MASK_REG = console_UART_DEFAULT_INTR_I2C_EC_MASK;
        console_INTR_SPI_EC_MASK_REG = console_UART_DEFAULT_INTR_SPI_EC_MASK;
        console_INTR_SLAVE_MASK_REG  = console_UART_DEFAULT_INTR_SLAVE_MASK;
        console_INTR_MASTER_MASK_REG = console_UART_DEFAULT_INTR_MASTER_MASK;
        console_INTR_RX_MASK_REG     = console_UART_DEFAULT_INTR_RX_MASK;
        console_INTR_TX_MASK_REG     = console_UART_DEFAULT_INTR_TX_MASK;

    #if(console_INTERNAL_RX_SW_BUFFER_CONST)
        console_rxBufferHead     = 0u;
        console_rxBufferTail     = 0u;
        console_rxBufferOverflow = 0u;
    #endif /* (console_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(console_INTERNAL_TX_SW_BUFFER_CONST)
        console_txBufferHead = 0u;
        console_txBufferTail = 0u;
    #endif /* (console_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: console_UartPostEnable
********************************************************************************
*
* Summary:
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be 
*  controlled by the SCB UART.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void console_UartPostEnable(void)
{
#if (console_SCB_MODE_UNCONFIG_CONST_CFG)

#if (console_TX_SDA_MISO_PIN)
    if (console_CHECK_TX_SDA_MISO_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        console_SET_HSIOM_SEL(console_TX_SDA_MISO_HSIOM_REG, console_TX_SDA_MISO_HSIOM_MASK,
                                       console_TX_SDA_MISO_HSIOM_POS, console_HSIOM_UART_SEL);
    }
#endif /* (console_TX_SDA_MISO_PIN_PIN) */

#if (console_RTS_SS0_PIN)
    if (console_CHECK_RTS_SS0_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        console_SET_HSIOM_SEL(console_RTS_SS0_HSIOM_REG, console_RTS_SS0_HSIOM_MASK,
                                       console_RTS_SS0_HSIOM_POS, console_HSIOM_UART_SEL);
    }
#endif /* (console_RTS_SS0_PIN) */

#else
#if (console_UART_TX_PIN)
     /* Set SCB UART to drive the output pin */
    console_SET_HSIOM_SEL(console_TX_HSIOM_REG, console_TX_HSIOM_MASK,
                                   console_TX_HSIOM_POS, console_HSIOM_UART_SEL);
#endif /* (console_UART_TX_PIN) */

#if (console_UART_RTS_PIN)
    /* Set SCB UART to drive the output pin */
    console_SET_HSIOM_SEL(console_RTS_HSIOM_REG, console_RTS_HSIOM_MASK,
                                   console_RTS_HSIOM_POS, console_HSIOM_UART_SEL);
#endif /* (console_UART_RTS_PIN) */

#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: console_UartStop
********************************************************************************
*
* Summary:
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature to
*  not cause it to trigger after the component is enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void console_UartStop(void)
{
#if(console_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (console_TX_SDA_MISO_PIN)
        if (console_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            console_SET_HSIOM_SEL(console_TX_SDA_MISO_HSIOM_REG, console_TX_SDA_MISO_HSIOM_MASK,
                                           console_TX_SDA_MISO_HSIOM_POS, console_HSIOM_GPIO_SEL);
        }
    #endif /* (console_TX_SDA_MISO_PIN_PIN) */

    #if (console_RTS_SS0_PIN)
        if (console_CHECK_RTS_SS0_PIN_USED)
        {
            /* Set output pin state after block is disabled */
            console_uart_rts_spi_ss0_Write(console_GET_UART_RTS_INACTIVE);

            /* Set GPIO to drive output pin */
            console_SET_HSIOM_SEL(console_RTS_SS0_HSIOM_REG, console_RTS_SS0_HSIOM_MASK,
                                           console_RTS_SS0_HSIOM_POS, console_HSIOM_GPIO_SEL);
        }
    #endif /* (console_SS0_PIN) */

#else
    #if (console_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        console_SET_HSIOM_SEL(console_TX_HSIOM_REG, console_TX_HSIOM_MASK,
                                       console_TX_HSIOM_POS, console_HSIOM_GPIO_SEL);
    #endif /* (console_UART_TX_PIN) */

    #if (console_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        console_rts_Write(console_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        console_SET_HSIOM_SEL(console_RTS_HSIOM_REG, console_RTS_HSIOM_MASK,
                                       console_RTS_HSIOM_POS, console_HSIOM_GPIO_SEL);
    #endif /* (console_UART_RTS_PIN) */

#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (console_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    console_UART_RX_CTRL_REG &= (uint32) ~console_UART_RX_CTRL_SKIP_START;
#endif /* (console_UART_WAKE_ENABLE_CONST) */
}


/*******************************************************************************
* Function Name: console_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
* Parameters:
*  address: Address for hardware address detection.
*
* Return:
*  None
*
*******************************************************************************/
void console_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = console_RX_MATCH_REG;

    matchReg &= ((uint32) ~console_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & console_RX_MATCH_ADDR_MASK)); /* Set address  */

    console_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: console_UartSetRxAddressMask
********************************************************************************
*
* Summary:
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
* Parameters:
*  addressMask: Address mask.
*   0 - address bit does not care while comparison.
*   1 - address bit is significant while comparison.
*
* Return:
*  None
*
*******************************************************************************/
void console_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = console_RX_MATCH_REG;

    matchReg &= ((uint32) ~console_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << console_RX_MATCH_MASK_POS));

    console_RX_MATCH_REG = matchReg;
}


#if(console_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: console_UartGetChar
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *  This function is designed for ASCII characters and returns a char
    *  where 1 to 255 are valid characters and 0 indicates an error occurred or
    *  no data present.
    *  - The RX software buffer is disabled: returns the data element
    *    retrieved from the RX FIFO.
    *    Undefined data will be returned if the RX FIFO is empty.
    *  - The RX software buffer is enabled: returns the data element from
    *    the software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The next data element from the receive buffer.
    *  ASCII character values from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is enabled: The internal software buffer overflow
    *  does not treat as an error condition.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 console_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != console_SpiUartGetRxBufferSize())
        {
            rxData = console_SpiUartReadRxData();
        }

        if (console_CHECK_INTR_RX(console_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            console_ClearRxInterruptSource(console_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: console_UartGetByte
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Bits 7-0 contain the next data element from the receive buffer and
    *  other bits contain the error condition.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is disabled: The internal software buffer overflow
    *  is not returned as status by this function.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 console_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (console_CHECK_RX_SW_BUFFER)
        {
            console_DisableInt();
        }
        #endif

        if (0u != console_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (console_CHECK_RX_SW_BUFFER)
            {            
                console_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = console_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the case
            * of empty. Otherwise the first received byte will be read.
            */
            rxData = console_RX_FIFO_RD_REG;

            /* Enables interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine
            * in case the byte was received and read by code above.
            */
            #if (console_CHECK_RX_SW_BUFFER)
            {
                console_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (console_GetRxInterruptSource() & console_INTR_RX_ERR);
        console_ClearRxInterruptSource(console_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: console_UartSetRtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of RTS output signal.
        *
        * Parameters:
        *  polarity: Active polarity of RTS output signal.
        *   console_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   console_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void console_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                console_UART_FLOW_CTRL_REG |= (uint32)  console_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                console_UART_FLOW_CTRL_REG &= (uint32) ~console_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: console_UartSetRtsFifoLevel
        ********************************************************************************
        *
        * Summary:
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *
        * Parameters:
        *  level: Level in the RX FIFO for RTS signal activation.
        *         The range of valid level values is between 0 and RX FIFO depth - 1.
        *         Setting level value to 0 disables RTS signal activation.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void console_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = console_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~console_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (console_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            console_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1) */

#endif /* (console_UART_RX_DIRECTION) */


#if(console_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: console_UartPutString
    ********************************************************************************
    *
    * Summary:
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  string: pointer to the null terminated string array to be placed in the
    *          transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void console_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            console_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: console_UartPutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data followed by a carriage return (0x0D) and
    *  line feed (0x0A) into the transmit buffer.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  txDataByte : the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void console_UartPutCRLF(uint32 txDataByte)
    {
        console_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        console_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        console_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: consoleSCB_UartEnableCts
        ********************************************************************************
        *
        * Summary:
        *  Enables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void console_UartEnableCts(void)
        {
            console_UART_FLOW_CTRL_REG |= (uint32)  console_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: console_UartDisableCts
        ********************************************************************************
        *
        * Summary:
        *  Disables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void console_UartDisableCts(void)
        {
            console_UART_FLOW_CTRL_REG &= (uint32) ~console_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: console_UartSetCtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of CTS input signal.
        *
        * Parameters:
        *  polarity: Active polarity of CTS output signal.
        *   console_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   console_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void console_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                console_UART_FLOW_CTRL_REG |= (uint32)  console_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                console_UART_FLOW_CTRL_REG &= (uint32) ~console_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1) */

#endif /* (console_UART_TX_DIRECTION) */


#if(console_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: console_UartSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears and enables interrupt on a falling edge of the Rx input. The GPIO
    *  event wakes up the device and SKIP_START feature allows the UART continue
    *  receiving data bytes properly. The GPIO interrupt does not track in the
    *  active mode therefore requires to be cleared by this API.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void console_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. At GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        console_UART_RX_CTRL_REG |= console_UART_RX_CTRL_SKIP_START;

    #if(console_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(console_MOSI_SCL_RX_WAKE_PIN)
            (void) console_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt();
        #endif /* (console_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(console_UART_RX_WAKE_PIN)
            (void) console_rx_wake_ClearInterrupt();
        #endif /* (console_UART_RX_WAKE_PIN) */
    #endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(console_UART_RX_WAKEUP_IRQ)
        console_RxWakeClearPendingInt();
        console_RxWakeEnableInt();
    #endif /* (console_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: console_UartRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void console_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(console_UART_RX_WAKEUP_IRQ)
        console_RxWakeDisableInt();
    #endif /* (console_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (console_UART_WAKE_ENABLE_CONST) */


#if(console_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: console_UART_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
    *  event. This event is configured to trigger on a falling edge of the RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR(console_UART_WAKEUP_ISR)
    {
    #ifdef console_UART_WAKEUP_ISR_ENTRY_CALLBACK
        console_UART_WAKEUP_ISR_EntryCallback();
    #endif /* console_UART_WAKEUP_ISR_ENTRY_CALLBACK */

        /* Clear interrupt source: the event becomes multi triggered and is
        * only disabled by console_UartRestoreConfig() call.
        */
    #if(console_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(console_MOSI_SCL_RX_WAKE_PIN)
            (void) console_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt();
        #endif /* (console_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(console_UART_RX_WAKE_PIN)
            (void) console_rx_wake_ClearInterrupt();
        #endif /* (console_UART_RX_WAKE_PIN) */
    #endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */

    #ifdef console_UART_WAKEUP_ISR_EXIT_CALLBACK
        console_UART_WAKEUP_ISR_ExitCallback();
    #endif /* console_UART_WAKEUP_ISR_EXIT_CALLBACK */
    }
#endif /* (console_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
