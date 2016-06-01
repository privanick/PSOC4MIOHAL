/***************************************************************************//**
* \file LCD_UART.c
* \version 3.20
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_PVT.h"
#include "LCD_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (LCD_UART_WAKE_ENABLE_CONST && LCD_UART_RX_WAKEUP_IRQ)
    /**
    * \addtogroup group_globals
    * \{
    */
    /** This global variable determines whether to enable Skip Start
    * functionality when LCD_Sleep() function is called:
    * 0 – disable, other values – enable. Default value is 1.
    * It is only available when Enable wakeup from Deep Sleep Mode is enabled.
    */
    uint8 LCD_skipStart = 1u;
    /** \} globals */
#endif /* (LCD_UART_WAKE_ENABLE_CONST && LCD_UART_RX_WAKEUP_IRQ) */

#if(LCD_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const LCD_UART_INIT_STRUCT LCD_configUart =
    {
        LCD_UART_SUB_MODE,
        LCD_UART_DIRECTION,
        LCD_UART_DATA_BITS_NUM,
        LCD_UART_PARITY_TYPE,
        LCD_UART_STOP_BITS_NUM,
        LCD_UART_OVS_FACTOR,
        LCD_UART_IRDA_LOW_POWER,
        LCD_UART_MEDIAN_FILTER_ENABLE,
        LCD_UART_RETRY_ON_NACK,
        LCD_UART_IRDA_POLARITY,
        LCD_UART_DROP_ON_PARITY_ERR,
        LCD_UART_DROP_ON_FRAME_ERR,
        LCD_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        LCD_UART_MP_MODE_ENABLE,
        LCD_UART_MP_ACCEPT_ADDRESS,
        LCD_UART_MP_RX_ADDRESS,
        LCD_UART_MP_RX_ADDRESS_MASK,
        (uint32) LCD_SCB_IRQ_INTERNAL,
        LCD_UART_INTR_RX_MASK,
        LCD_UART_RX_TRIGGER_LEVEL,
        LCD_UART_INTR_TX_MASK,
        LCD_UART_TX_TRIGGER_LEVEL,
        (uint8) LCD_UART_BYTE_MODE_ENABLE,
        (uint8) LCD_UART_CTS_ENABLE,
        (uint8) LCD_UART_CTS_POLARITY,
        (uint8) LCD_UART_RTS_POLARITY,
        (uint8) LCD_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: LCD_UartInit
    ****************************************************************************//**
    *
    *  Configures the LCD for UART operation.
    *
    *  This function is intended specifically to be used when the LCD
    *  configuration is set to “Unconfigured LCD” in the customizer.
    *  After initializing the LCD in UART mode using this function,
    *  the component can be enabled using the LCD_Start() or
    * LCD_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration
    *  settings. This structure contains the same information that would otherwise
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of
    *   fields. These fields match the selections available in the customizer.
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void LCD_UartInit(const LCD_UART_INIT_STRUCT *config)
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

        #if !(LCD_CY_SCBIP_V0 || LCD_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (LCD_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (LCD_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(LCD_CY_SCBIP_V0 || LCD_CY_SCBIP_V1) */

            /* Configure pins */
            LCD_SetPins(LCD_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            LCD_scbMode       = (uint8) LCD_SCB_MODE_UART;
            LCD_scbEnableWake = (uint8) config->enableWake;
            LCD_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            LCD_rxBuffer      =         config->rxBuffer;
            LCD_rxDataBits    = (uint8) config->dataBits;
            LCD_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            LCD_txBuffer      =         config->txBuffer;
            LCD_txDataBits    = (uint8) config->dataBits;
            LCD_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(LCD_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                LCD_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (LCD_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (LCD_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                LCD_CTRL_REG  = LCD_GET_CTRL_OVS(config->oversample);
            }

            LCD_CTRL_REG     |= LCD_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             LCD_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             LCD_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            LCD_UART_CTRL_REG = LCD_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            LCD_UART_RX_CTRL_REG = LCD_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        LCD_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        LCD_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        LCD_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        LCD_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(LCD_UART_PARITY_NONE != config->parity)
            {
               LCD_UART_RX_CTRL_REG |= LCD_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    LCD_UART_RX_CTRL_PARITY_ENABLED;
            }

            LCD_RX_CTRL_REG      = LCD_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                LCD_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                LCD_GET_UART_RX_CTRL_ENABLED(config->direction);

            LCD_RX_FIFO_CTRL_REG = LCD_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            LCD_RX_MATCH_REG     = LCD_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                LCD_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            LCD_UART_TX_CTRL_REG = LCD_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                LCD_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(LCD_UART_PARITY_NONE != config->parity)
            {
               LCD_UART_TX_CTRL_REG |= LCD_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    LCD_UART_TX_CTRL_PARITY_ENABLED;
            }

            LCD_TX_CTRL_REG      = LCD_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                LCD_GET_UART_TX_CTRL_ENABLED(config->direction);

            LCD_TX_FIFO_CTRL_REG = LCD_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(LCD_CY_SCBIP_V0 || LCD_CY_SCBIP_V1)
            LCD_UART_FLOW_CTRL_REG = LCD_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            LCD_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            LCD_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            LCD_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(LCD_CY_SCBIP_V0 || LCD_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (LCD_ISR_NUMBER);
            CyIntSetPriority(LCD_ISR_NUMBER, LCD_ISR_PRIORITY);
            (void) CyIntSetVector(LCD_ISR_NUMBER, &LCD_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(LCD_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (LCD_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(LCD_RX_WAKE_ISR_NUMBER, LCD_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(LCD_RX_WAKE_ISR_NUMBER, &LCD_UART_WAKEUP_ISR);
        #endif /* (LCD_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            LCD_INTR_I2C_EC_MASK_REG = LCD_NO_INTR_SOURCES;
            LCD_INTR_SPI_EC_MASK_REG = LCD_NO_INTR_SOURCES;
            LCD_INTR_SLAVE_MASK_REG  = LCD_NO_INTR_SOURCES;
            LCD_INTR_MASTER_MASK_REG = LCD_NO_INTR_SOURCES;
            LCD_INTR_RX_MASK_REG     = config->rxInterruptMask;
            LCD_INTR_TX_MASK_REG     = config->txInterruptMask;
        
            /* Configure TX interrupt sources to restore. */
            LCD_IntrTxMask = LO16(LCD_INTR_TX_MASK_REG);

            /* Clear RX buffer indexes */
            LCD_rxBufferHead     = 0u;
            LCD_rxBufferTail     = 0u;
            LCD_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            LCD_txBufferHead = 0u;
            LCD_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: LCD_UartInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the UART operation.
    *
    *******************************************************************************/
    void LCD_UartInit(void)
    {
        /* Configure UART interface */
        LCD_CTRL_REG = LCD_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        LCD_UART_CTRL_REG = LCD_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        LCD_UART_RX_CTRL_REG = LCD_UART_DEFAULT_UART_RX_CTRL;
        LCD_RX_CTRL_REG      = LCD_UART_DEFAULT_RX_CTRL;
        LCD_RX_FIFO_CTRL_REG = LCD_UART_DEFAULT_RX_FIFO_CTRL;
        LCD_RX_MATCH_REG     = LCD_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        LCD_UART_TX_CTRL_REG = LCD_UART_DEFAULT_UART_TX_CTRL;
        LCD_TX_CTRL_REG      = LCD_UART_DEFAULT_TX_CTRL;
        LCD_TX_FIFO_CTRL_REG = LCD_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(LCD_CY_SCBIP_V0 || LCD_CY_SCBIP_V1)
        LCD_UART_FLOW_CTRL_REG = LCD_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(LCD_CY_SCBIP_V0 || LCD_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(LCD_SCB_IRQ_INTERNAL)
        CyIntDisable    (LCD_ISR_NUMBER);
        CyIntSetPriority(LCD_ISR_NUMBER, LCD_ISR_PRIORITY);
        (void) CyIntSetVector(LCD_ISR_NUMBER, &LCD_SPI_UART_ISR);
    #endif /* (LCD_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(LCD_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (LCD_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(LCD_RX_WAKE_ISR_NUMBER, LCD_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(LCD_RX_WAKE_ISR_NUMBER, &LCD_UART_WAKEUP_ISR);
    #endif /* (LCD_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        LCD_INTR_I2C_EC_MASK_REG = LCD_UART_DEFAULT_INTR_I2C_EC_MASK;
        LCD_INTR_SPI_EC_MASK_REG = LCD_UART_DEFAULT_INTR_SPI_EC_MASK;
        LCD_INTR_SLAVE_MASK_REG  = LCD_UART_DEFAULT_INTR_SLAVE_MASK;
        LCD_INTR_MASTER_MASK_REG = LCD_UART_DEFAULT_INTR_MASTER_MASK;
        LCD_INTR_RX_MASK_REG     = LCD_UART_DEFAULT_INTR_RX_MASK;
        LCD_INTR_TX_MASK_REG     = LCD_UART_DEFAULT_INTR_TX_MASK;
    
        /* Configure TX interrupt sources to restore. */
        LCD_IntrTxMask = LO16(LCD_INTR_TX_MASK_REG);

    #if(LCD_INTERNAL_RX_SW_BUFFER_CONST)
        LCD_rxBufferHead     = 0u;
        LCD_rxBufferTail     = 0u;
        LCD_rxBufferOverflow = 0u;
    #endif /* (LCD_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(LCD_INTERNAL_TX_SW_BUFFER_CONST)
        LCD_txBufferHead = 0u;
        LCD_txBufferTail = 0u;
    #endif /* (LCD_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (LCD_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: LCD_UartPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be
*  controlled by the SCB UART.
*
*******************************************************************************/
void LCD_UartPostEnable(void)
{
#if (LCD_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (LCD_TX_SDA_MISO_PIN)
        if (LCD_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set SCB UART to drive the output pin */
            LCD_SET_HSIOM_SEL(LCD_TX_SDA_MISO_HSIOM_REG, LCD_TX_SDA_MISO_HSIOM_MASK,
                                           LCD_TX_SDA_MISO_HSIOM_POS, LCD_TX_SDA_MISO_HSIOM_SEL_UART);
        }
    #endif /* (LCD_TX_SDA_MISO_PIN_PIN) */

    #if !(LCD_CY_SCBIP_V0 || LCD_CY_SCBIP_V1)
        #if (LCD_RTS_SS0_PIN)
            if (LCD_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set SCB UART to drive the output pin */
                LCD_SET_HSIOM_SEL(LCD_RTS_SS0_HSIOM_REG, LCD_RTS_SS0_HSIOM_MASK,
                                               LCD_RTS_SS0_HSIOM_POS, LCD_RTS_SS0_HSIOM_SEL_UART);
            }
        #endif /* (LCD_RTS_SS0_PIN) */
    #endif /* !(LCD_CY_SCBIP_V0 || LCD_CY_SCBIP_V1) */

#else
    #if (LCD_UART_TX_PIN)
         /* Set SCB UART to drive the output pin */
        LCD_SET_HSIOM_SEL(LCD_TX_HSIOM_REG, LCD_TX_HSIOM_MASK,
                                       LCD_TX_HSIOM_POS, LCD_TX_HSIOM_SEL_UART);
    #endif /* (LCD_UART_TX_PIN) */

    #if (LCD_UART_RTS_PIN)
        /* Set SCB UART to drive the output pin */
        LCD_SET_HSIOM_SEL(LCD_RTS_HSIOM_REG, LCD_RTS_HSIOM_MASK,
                                       LCD_RTS_HSIOM_POS, LCD_RTS_HSIOM_SEL_UART);
    #endif /* (LCD_UART_RTS_PIN) */
#endif /* (LCD_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    LCD_SetTxInterruptMode(LCD_IntrTxMask);
}


/*******************************************************************************
* Function Name: LCD_UartStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature
*  to not cause it to trigger after the component is enabled.
*
*******************************************************************************/
void LCD_UartStop(void)
{
#if(LCD_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (LCD_TX_SDA_MISO_PIN)
        if (LCD_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            LCD_SET_HSIOM_SEL(LCD_TX_SDA_MISO_HSIOM_REG, LCD_TX_SDA_MISO_HSIOM_MASK,
                                           LCD_TX_SDA_MISO_HSIOM_POS, LCD_TX_SDA_MISO_HSIOM_SEL_GPIO);
        }
    #endif /* (LCD_TX_SDA_MISO_PIN_PIN) */

    #if !(LCD_CY_SCBIP_V0 || LCD_CY_SCBIP_V1)
        #if (LCD_RTS_SS0_PIN)
            if (LCD_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set output pin state after block is disabled */
                LCD_uart_rts_spi_ss0_Write(LCD_GET_UART_RTS_INACTIVE);

                /* Set GPIO to drive output pin */
                LCD_SET_HSIOM_SEL(LCD_RTS_SS0_HSIOM_REG, LCD_RTS_SS0_HSIOM_MASK,
                                               LCD_RTS_SS0_HSIOM_POS, LCD_RTS_SS0_HSIOM_SEL_GPIO);
            }
        #endif /* (LCD_RTS_SS0_PIN) */
    #endif /* !(LCD_CY_SCBIP_V0 || LCD_CY_SCBIP_V1) */

#else
    #if (LCD_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        LCD_SET_HSIOM_SEL(LCD_TX_HSIOM_REG, LCD_TX_HSIOM_MASK,
                                       LCD_TX_HSIOM_POS, LCD_TX_HSIOM_SEL_GPIO);
    #endif /* (LCD_UART_TX_PIN) */

    #if (LCD_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        LCD_rts_Write(LCD_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        LCD_SET_HSIOM_SEL(LCD_RTS_HSIOM_REG, LCD_RTS_HSIOM_MASK,
                                       LCD_RTS_HSIOM_POS, LCD_RTS_HSIOM_SEL_GPIO);
    #endif /* (LCD_UART_RTS_PIN) */

#endif /* (LCD_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (LCD_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    LCD_UART_RX_CTRL_REG &= (uint32) ~LCD_UART_RX_CTRL_SKIP_START;
#endif /* (LCD_UART_WAKE_ENABLE_CONST) */

    /* Store TX interrupt sources (exclude level triggered). */
    LCD_IntrTxMask = LO16(LCD_GetTxInterruptMode() & LCD_INTR_UART_TX_RESTORE);
}


/*******************************************************************************
* Function Name: LCD_UartSetRxAddress
****************************************************************************//**
*
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
*  \param address: Address for hardware address detection.
*
*******************************************************************************/
void LCD_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = LCD_RX_MATCH_REG;

    matchReg &= ((uint32) ~LCD_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & LCD_RX_MATCH_ADDR_MASK)); /* Set address  */

    LCD_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: LCD_UartSetRxAddressMask
****************************************************************************//**
*
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
*  \param addressMask: Address mask.
*   - Bit value 0 – excludes bit from address comparison.
*   - Bit value 1 – the bit needs to match with the corresponding bit
*     of the address.
*
*******************************************************************************/
void LCD_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = LCD_RX_MATCH_REG;

    matchReg &= ((uint32) ~LCD_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << LCD_RX_MATCH_MASK_POS));

    LCD_RX_MATCH_REG = matchReg;
}


#if(LCD_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: LCD_UartGetChar
    ****************************************************************************//**
    *
    *  Retrieves next data element from receive buffer.
    *  This function is designed for ASCII characters and returns a char where
    *  1 to 255 are valid characters and 0 indicates an error occurred or no data
    *  is present.
    *  - RX software buffer is disabled: Returns data element retrieved from RX
    *    FIFO.
    *  - RX software buffer is enabled: Returns data element from the software
    *    receive buffer.
    *
    *  \return
    *   Next data element from the receive buffer. ASCII character values from
    *   1 to 255 are valid. A returned zero signifies an error condition or no
    *   data available.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check LCD_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 LCD_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != LCD_SpiUartGetRxBufferSize())
        {
            rxData = LCD_SpiUartReadRxData();
        }

        if (LCD_CHECK_INTR_RX(LCD_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            LCD_ClearRxInterruptSource(LCD_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: LCD_UartGetByte
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    *  \return
    *   Bits 7-0 contain the next data element from the receive buffer and
    *   other bits contain the error condition.
    *   - LCD_UART_RX_OVERFLOW - Attempt to write to a full
    *     receiver FIFO.
    *   - LCD_UART_RX_UNDERFLOW	Attempt to read from an empty
    *     receiver FIFO.
    *   - LCD_UART_RX_FRAME_ERROR - UART framing error detected.
    *   - LCD_UART_RX_PARITY_ERROR - UART parity error detected.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check LCD_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 LCD_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (LCD_CHECK_RX_SW_BUFFER)
        {
            LCD_DisableInt();
        }
        #endif

        if (0u != LCD_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (LCD_CHECK_RX_SW_BUFFER)
            {
                LCD_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = LCD_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the
            * case of empty. Otherwise the first received byte will be read.
            */
            rxData = LCD_RX_FIFO_RD_REG;


            /* Enables interrupt to receive more bytes. */
            #if (LCD_CHECK_RX_SW_BUFFER)
            {

                /* The byte has been read from RX FIFO. Clear RX interrupt to
                * not involve interrupt handler when RX FIFO is empty.
                */
                LCD_ClearRxInterruptSource(LCD_INTR_RX_NOT_EMPTY);

                LCD_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (LCD_GetRxInterruptSource() & LCD_INTR_RX_ERR);
        LCD_ClearRxInterruptSource(LCD_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(LCD_CY_SCBIP_V0 || LCD_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: LCD_UartSetRtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of RTS output signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of RTS output signal.
        *   - LCD_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   - LCD_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        *******************************************************************************/
        void LCD_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                LCD_UART_FLOW_CTRL_REG |= (uint32)  LCD_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                LCD_UART_FLOW_CTRL_REG &= (uint32) ~LCD_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: LCD_UartSetRtsFifoLevel
        ****************************************************************************//**
        *
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param level: Level in the RX FIFO for RTS signal activation.
        *   The range of valid level values is between 0 and RX FIFO depth - 1.
        *   Setting level value to 0 disables RTS signal activation.
        *
        *******************************************************************************/
        void LCD_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = LCD_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~LCD_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (LCD_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            LCD_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(LCD_CY_SCBIP_V0 || LCD_CY_SCBIP_V1) */

#endif /* (LCD_UART_RX_DIRECTION) */


#if(LCD_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: LCD_UartPutString
    ****************************************************************************//**
    *
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is a space available to put
    *  requested data in transmit buffer.
    *
    *  \param string: pointer to the null terminated string array to be placed in the
    *   transmit buffer.
    *
    *******************************************************************************/
    void LCD_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            LCD_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: LCD_UartPutCRLF
    ****************************************************************************//**
    *
    *  Places byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) in the transmit buffer.
    *  This function is blocking and waits until there is a space available to put
    *  all requested data in transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *
    *******************************************************************************/
    void LCD_UartPutCRLF(uint32 txDataByte)
    {
        LCD_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        LCD_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        LCD_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(LCD_CY_SCBIP_V0 || LCD_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: LCDSCB_UartEnableCts
        ****************************************************************************//**
        *
        *  Enables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void LCD_UartEnableCts(void)
        {
            LCD_UART_FLOW_CTRL_REG |= (uint32)  LCD_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: LCD_UartDisableCts
        ****************************************************************************//**
        *
        *  Disables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void LCD_UartDisableCts(void)
        {
            LCD_UART_FLOW_CTRL_REG &= (uint32) ~LCD_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: LCD_UartSetCtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of CTS input signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of CTS output signal.
        *   - LCD_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   - LCD_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        *******************************************************************************/
        void LCD_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                LCD_UART_FLOW_CTRL_REG |= (uint32)  LCD_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                LCD_UART_FLOW_CTRL_REG &= (uint32) ~LCD_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(LCD_CY_SCBIP_V0 || LCD_CY_SCBIP_V1) */

#endif /* (LCD_UART_TX_DIRECTION) */


#if (LCD_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: LCD_UartSaveConfig
    ****************************************************************************//**
    *
    *  Clears and enables an interrupt on a falling edge of the Rx input. The GPIO
    *  interrupt does not track in the active mode, therefore requires to be 
    *  cleared by this API.
    *
    *******************************************************************************/
    void LCD_UartSaveConfig(void)
    {
    #if (LCD_UART_RX_WAKEUP_IRQ)
        /* Set SKIP_START if requested (set by default). */
        if (0u != LCD_skipStart)
        {
            LCD_UART_RX_CTRL_REG |= (uint32)  LCD_UART_RX_CTRL_SKIP_START;
        }
        else
        {
            LCD_UART_RX_CTRL_REG &= (uint32) ~LCD_UART_RX_CTRL_SKIP_START;
        }
        
        /* Clear RX GPIO interrupt status and pending interrupt in NVIC because
        * falling edge on RX line occurs while UART communication in active mode.
        * Enable interrupt: next interrupt trigger should wakeup device.
        */
        LCD_CLEAR_UART_RX_WAKE_INTR;
        LCD_RxWakeClearPendingInt();
        LCD_RxWakeEnableInt();
    #endif /* (LCD_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: LCD_UartRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    *******************************************************************************/
    void LCD_UartRestoreConfig(void)
    {
    #if (LCD_UART_RX_WAKEUP_IRQ)
        /* Disable interrupt: no more triggers in active mode */
        LCD_RxWakeDisableInt();
    #endif /* (LCD_UART_RX_WAKEUP_IRQ) */
    }


    #if (LCD_UART_RX_WAKEUP_IRQ)
        /*******************************************************************************
        * Function Name: LCD_UART_WAKEUP_ISR
        ****************************************************************************//**
        *
        *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
        *  event. This event is configured to trigger on a falling edge of the RX line.
        *
        *******************************************************************************/
        CY_ISR(LCD_UART_WAKEUP_ISR)
        {
        #ifdef LCD_UART_WAKEUP_ISR_ENTRY_CALLBACK
            LCD_UART_WAKEUP_ISR_EntryCallback();
        #endif /* LCD_UART_WAKEUP_ISR_ENTRY_CALLBACK */

            LCD_CLEAR_UART_RX_WAKE_INTR;

        #ifdef LCD_UART_WAKEUP_ISR_EXIT_CALLBACK
            LCD_UART_WAKEUP_ISR_ExitCallback();
        #endif /* LCD_UART_WAKEUP_ISR_EXIT_CALLBACK */
        }
    #endif /* (LCD_UART_RX_WAKEUP_IRQ) */
#endif /* (LCD_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
