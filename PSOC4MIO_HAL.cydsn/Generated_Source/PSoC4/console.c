/*******************************************************************************
* File Name: console.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the SCB Component.
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

#if (console_SCB_MODE_I2C_INC)
    #include "console_I2C_PVT.h"
#endif /* (console_SCB_MODE_I2C_INC) */

#if (console_SCB_MODE_EZI2C_INC)
    #include "console_EZI2C_PVT.h"
#endif /* (console_SCB_MODE_EZI2C_INC) */

#if (console_SCB_MODE_SPI_INC || console_SCB_MODE_UART_INC)
    #include "console_SPI_UART_PVT.h"
#endif /* (console_SCB_MODE_SPI_INC || console_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (console_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 console_scbMode = console_SCB_MODE_UNCONFIG;
    uint8 console_scbEnableWake;
    uint8 console_scbEnableIntr;

    /* I2C configuration variables */
    uint8 console_mode;
    uint8 console_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * console_rxBuffer;
    uint8  console_rxDataBits;
    uint32 console_rxBufferSize;

    volatile uint8 * console_txBuffer;
    uint8  console_txDataBits;
    uint32 console_txBufferSize;

    /* EZI2C configuration variables */
    uint8 console_numberOfAddr;
    uint8 console_subAddrSize;
#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 console_initVar = 0u;

#if (console_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_console_CUSTOM_INTR_HANDLER)
    void (*console_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_console_CUSTOM_INTR_HANDLER) */
#endif /* (console_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void console_ScbEnableIntr(void);
static void console_ScbModeStop(void);
static void console_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: console_Init
********************************************************************************
*
* Summary:
*  Initializes the SCB component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SCB_I2CInit, SCB_SpiInit, SCB_UartInit or SCB_EzI2CInit.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void console_Init(void)
{
#if (console_SCB_MODE_UNCONFIG_CONST_CFG)
    if (console_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        console_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (console_SCB_MODE_I2C_CONST_CFG)
    console_I2CInit();

#elif (console_SCB_MODE_SPI_CONST_CFG)
    console_SpiInit();

#elif (console_SCB_MODE_UART_CONST_CFG)
    console_UartInit();

#elif (console_SCB_MODE_EZI2C_CONST_CFG)
    console_EzI2CInit();

#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: console_Enable
********************************************************************************
*
* Summary:
*  Enables the SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void console_Enable(void)
{
#if (console_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!console_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        console_CTRL_REG |= console_CTRL_ENABLED;

        console_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        console_ScbModePostEnable();
    }
#else
    console_CTRL_REG |= console_CTRL_ENABLED;

    console_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    console_ScbModePostEnable();
#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: console_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZ I2C. Otherwise this function does not enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  console_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void console_Start(void)
{
    if (0u == console_initVar)
    {
        console_Init();
        console_initVar = 1u; /* Component was initialized */
    }

    console_Enable();
}


/*******************************************************************************
* Function Name: console_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component and its interrupt.
*  It also disables all TX interrupt sources so as not to cause an unexpected
*  interrupt trigger because after the component is enabled, the TX FIFO 
*  is empty.
*
* Parameters:
*  None
*
* Return:
*  None
* 
*******************************************************************************/
void console_Stop(void)
{
#if (console_SCB_IRQ_INTERNAL)
    console_DisableInt();
#endif /* (console_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    console_ScbModeStop();

    /* Disable SCB IP */
    console_CTRL_REG &= (uint32) ~console_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger because after the component is enabled, the TX FIFO
    * is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when they are disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    console_SetTxInterruptMode(console_NO_INTR_SOURCES);

#if (console_SCB_IRQ_INTERNAL)
    console_ClearPendingInt();
#endif /* (console_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: console_SetRxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the RX FIFO to generate RX level interrupt.
*         The range of valid level values is between 0 and RX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void console_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = console_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~console_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (console_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    console_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: console_SetTxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has more entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the TX FIFO to generate TX level interrupt.
*         The range of valid level values is between 0 and TX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void console_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = console_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~console_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (console_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    console_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (console_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: console_SetCustomInterruptHandler
    ********************************************************************************
    *
    * Summary:
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    * Parameters:
    *  func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void console_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_console_CUSTOM_INTR_HANDLER)
        console_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_console_CUSTOM_INTR_HANDLER) */
    }
#endif /* (console_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: console_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables an interrupt for a specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void console_ScbEnableIntr(void)
{
#if (console_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (console_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != console_scbEnableIntr)
        {
            console_EnableInt();
        }

    #else
        console_EnableInt();

    #endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (console_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: console_ScbModePostEnable
********************************************************************************
*
* Summary:
*  Calls the PostEnable function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void console_ScbModePostEnable(void)
{
#if (console_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!console_CY_SCBIP_V1)
    if (console_SCB_MODE_SPI_RUNTM_CFG)
    {
        console_SpiPostEnable();
    }
    else if (console_SCB_MODE_UART_RUNTM_CFG)
    {
        console_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!console_CY_SCBIP_V1) */

#elif (console_SCB_MODE_SPI_CONST_CFG)
    console_SpiPostEnable();

#elif (console_SCB_MODE_UART_CONST_CFG)
    console_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: console_ScbModeStop
********************************************************************************
*
* Summary:
*  Calls the Stop function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void console_ScbModeStop(void)
{
#if (console_SCB_MODE_UNCONFIG_CONST_CFG)
    if (console_SCB_MODE_I2C_RUNTM_CFG)
    {
        console_I2CStop();
    }
    else if (console_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        console_EzI2CStop();
    }
#if (!console_CY_SCBIP_V1)
    else if (console_SCB_MODE_SPI_RUNTM_CFG)
    {
        console_SpiStop();
    }
    else if (console_SCB_MODE_UART_RUNTM_CFG)
    {
        console_UartStop();
    }
#endif /* (!console_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (console_SCB_MODE_I2C_CONST_CFG)
    console_I2CStop();

#elif (console_SCB_MODE_EZI2C_CONST_CFG)
    console_EzI2CStop();

#elif (console_SCB_MODE_SPI_CONST_CFG)
    console_SpiStop();

#elif (console_SCB_MODE_UART_CONST_CFG)
    console_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (console_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: console_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void console_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [console_SCB_PINS_NUMBER];
        uint32 pinsDm   [console_SCB_PINS_NUMBER];

    #if (!console_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!console_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < console_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = console_HSIOM_DEF_SEL;
            pinsDm[i]    = console_PIN_DM_ALG_HIZ;
        }

        if ((console_SCB_MODE_I2C   == mode) ||
           (console_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[console_RX_SCL_MOSI_PIN_INDEX] = console_HSIOM_I2C_SEL;
            hsiomSel[console_TX_SDA_MISO_PIN_INDEX] = console_HSIOM_I2C_SEL;

            pinsDm[console_RX_SCL_MOSI_PIN_INDEX] = console_PIN_DM_OD_LO;
            pinsDm[console_TX_SDA_MISO_PIN_INDEX] = console_PIN_DM_OD_LO;
        }
    #if (!console_CY_SCBIP_V1)
        else if (console_SCB_MODE_SPI == mode)
        {
            hsiomSel[console_RX_SCL_MOSI_PIN_INDEX] = console_HSIOM_SPI_SEL;
            hsiomSel[console_TX_SDA_MISO_PIN_INDEX] = console_HSIOM_SPI_SEL;
            hsiomSel[console_CTS_SCLK_PIN_INDEX] = console_HSIOM_SPI_SEL;

            if (console_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[console_RX_SCL_MOSI_PIN_INDEX] = console_PIN_DM_DIG_HIZ;
                pinsDm[console_TX_SDA_MISO_PIN_INDEX] = console_PIN_DM_STRONG;
                pinsDm[console_CTS_SCLK_PIN_INDEX] = console_PIN_DM_DIG_HIZ;

            #if (console_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[console_RTS_SS0_PIN_INDEX] = console_HSIOM_SPI_SEL;
                pinsDm  [console_RTS_SS0_PIN_INDEX] = console_PIN_DM_DIG_HIZ;
            #endif /* (console_RTS_SS0_PIN) */

            #if (console_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= console_TX_SDA_MISO_PIN_MASK;
            #endif /* (console_TX_SDA_MISO_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[console_RX_SCL_MOSI_PIN_INDEX] = console_PIN_DM_STRONG;
                pinsDm[console_TX_SDA_MISO_PIN_INDEX] = console_PIN_DM_DIG_HIZ;
                pinsDm[console_CTS_SCLK_PIN_INDEX] = console_PIN_DM_STRONG;

            #if (console_RTS_SS0_PIN)
                hsiomSel [console_RTS_SS0_PIN_INDEX] = console_HSIOM_SPI_SEL;
                pinsDm   [console_RTS_SS0_PIN_INDEX] = console_PIN_DM_STRONG;
                pinsInBuf |= console_RTS_SS0_PIN_MASK;
            #endif /* (console_RTS_SS0_PIN) */

            #if (console_SS1_PIN)
                hsiomSel [console_SS1_PIN_INDEX] = console_HSIOM_SPI_SEL;
                pinsDm   [console_SS1_PIN_INDEX] = console_PIN_DM_STRONG;
                pinsInBuf |= console_SS1_PIN_MASK;
            #endif /* (console_SS1_PIN) */

            #if (console_SS2_PIN)
                hsiomSel [console_SS2_PIN_INDEX] = console_HSIOM_SPI_SEL;
                pinsDm   [console_SS2_PIN_INDEX] = console_PIN_DM_STRONG;
                pinsInBuf |= console_SS2_PIN_MASK;
            #endif /* (console_SS2_PIN) */

            #if (console_SS3_PIN)
                hsiomSel [console_SS3_PIN_INDEX] = console_HSIOM_SPI_SEL;
                pinsDm   [console_SS3_PIN_INDEX] = console_PIN_DM_STRONG;
                pinsInBuf |= console_SS3_PIN_MASK;
            #endif /* (console_SS3_PIN) */

                /* Disable input buffers */
            #if (console_RX_SCL_MOSI_PIN)
                pinsInBuf |= console_RX_SCL_MOSI_PIN_MASK;
            #endif /* (console_RX_SCL_MOSI_PIN) */

             #if (console_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= console_RX_WAKE_SCL_MOSI_PIN_MASK;
            #endif /* (console_RX_WAKE_SCL_MOSI_PIN) */

            #if (console_CTS_SCLK_PIN)
                pinsInBuf |= console_CTS_SCLK_PIN_MASK;
            #endif /* (console_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (console_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[console_TX_SDA_MISO_PIN_INDEX] = console_HSIOM_UART_SEL;
                pinsDm  [console_TX_SDA_MISO_PIN_INDEX] = console_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if (0u != (console_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[console_RX_SCL_MOSI_PIN_INDEX] = console_HSIOM_UART_SEL;
                    pinsDm  [console_RX_SCL_MOSI_PIN_INDEX] = console_PIN_DM_DIG_HIZ;
                }

                if (0u != (console_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[console_TX_SDA_MISO_PIN_INDEX] = console_HSIOM_UART_SEL;
                    pinsDm  [console_TX_SDA_MISO_PIN_INDEX] = console_PIN_DM_STRONG;

                #if (console_TX_SDA_MISO_PIN)
                     pinsInBuf |= console_TX_SDA_MISO_PIN_MASK;
                #endif /* (console_TX_SDA_MISO_PIN) */
                }

            #if !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1)
                if (console_UART_MODE_STD == subMode)
                {
                    if (0u != (console_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[console_CTS_SCLK_PIN_INDEX] = console_HSIOM_UART_SEL;
                        pinsDm  [console_CTS_SCLK_PIN_INDEX] = console_PIN_DM_DIG_HIZ;
                    }

                    if (0u != (console_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[console_RTS_SS0_PIN_INDEX] = console_HSIOM_UART_SEL;
                        pinsDm  [console_RTS_SS0_PIN_INDEX] = console_PIN_DM_STRONG;

                    #if (console_RTS_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= console_RTS_SS0_PIN_MASK;
                    #endif /* (console_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1) */
            }
        }
    #endif /* (!console_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (console_RX_WAKE_SCL_MOSI_PIN)
        console_SET_HSIOM_SEL(console_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       console_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       console_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[console_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        console_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[console_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        console_SET_INP_DIS(console_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     console_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & console_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        console_SET_INCFG_TYPE(console_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        console_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        console_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        console_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (console_RX_WAKE_SCL_MOSI_PIN) */

    #if (console_RX_SCL_MOSI_PIN)
        console_SET_HSIOM_SEL(console_RX_SCL_MOSI_HSIOM_REG,
                                       console_RX_SCL_MOSI_HSIOM_MASK,
                                       console_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[console_RX_SCL_MOSI_PIN_INDEX]);

        console_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[console_RX_SCL_MOSI_PIN_INDEX]);

    #if (!console_CY_SCBIP_V1)
        console_SET_INP_DIS(console_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                     console_uart_rx_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & console_RX_SCL_MOSI_PIN_MASK)));
    #endif /* (!console_CY_SCBIP_V1) */
    #endif /* (console_RX_SCL_MOSI_PIN) */

    #if (console_TX_SDA_MISO_PIN)
        console_SET_HSIOM_SEL(console_TX_SDA_MISO_HSIOM_REG,
                                       console_TX_SDA_MISO_HSIOM_MASK,
                                       console_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[console_TX_SDA_MISO_PIN_INDEX]);

        console_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[console_TX_SDA_MISO_PIN_INDEX]);

    #if (!console_CY_SCBIP_V1)
        console_SET_INP_DIS(console_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     console_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & console_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!console_CY_SCBIP_V1) */
    #endif /* (console_RX_SCL_MOSI_PIN) */

    #if (console_CTS_SCLK_PIN)
        console_SET_HSIOM_SEL(console_CTS_SCLK_HSIOM_REG,
                                       console_CTS_SCLK_HSIOM_MASK,
                                       console_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[console_CTS_SCLK_PIN_INDEX]);

        console_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[console_CTS_SCLK_PIN_INDEX]);

        console_SET_INP_DIS(console_uart_cts_spi_sclk_INP_DIS,
                                     console_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & console_CTS_SCLK_PIN_MASK)));
    #endif /* (console_CTS_SCLK_PIN) */

    #if (console_RTS_SS0_PIN)
        console_SET_HSIOM_SEL(console_RTS_SS0_HSIOM_REG,
                                       console_RTS_SS0_HSIOM_MASK,
                                       console_RTS_SS0_HSIOM_POS,
                                       hsiomSel[console_RTS_SS0_PIN_INDEX]);

        console_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[console_RTS_SS0_PIN_INDEX]);

        console_SET_INP_DIS(console_uart_rts_spi_ss0_INP_DIS,
                                     console_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & console_RTS_SS0_PIN_MASK)));
    #endif /* (console_RTS_SS0_PIN) */

    #if (console_SS1_PIN)
        console_SET_HSIOM_SEL(console_SS1_HSIOM_REG,
                                       console_SS1_HSIOM_MASK,
                                       console_SS1_HSIOM_POS,
                                       hsiomSel[console_SS1_PIN_INDEX]);

        console_spi_ss1_SetDriveMode((uint8) pinsDm[console_SS1_PIN_INDEX]);

        console_SET_INP_DIS(console_spi_ss1_INP_DIS,
                                     console_spi_ss1_MASK,
                                     (0u != (pinsInBuf & console_SS1_PIN_MASK)));
    #endif /* (console_SS1_PIN) */

    #if (console_SS2_PIN)
        console_SET_HSIOM_SEL(console_SS2_HSIOM_REG,
                                       console_SS2_HSIOM_MASK,
                                       console_SS2_HSIOM_POS,
                                       hsiomSel[console_SS2_PIN_INDEX]);

        console_spi_ss2_SetDriveMode((uint8) pinsDm[console_SS2_PIN_INDEX]);

        console_SET_INP_DIS(console_spi_ss2_INP_DIS,
                                     console_spi_ss2_MASK,
                                     (0u != (pinsInBuf & console_SS2_PIN_MASK)));
    #endif /* (console_SS2_PIN) */

    #if (console_SS3_PIN)
        console_SET_HSIOM_SEL(console_SS3_HSIOM_REG,
                                       console_SS3_HSIOM_MASK,
                                       console_SS3_HSIOM_POS,
                                       hsiomSel[console_SS3_PIN_INDEX]);

        console_spi_ss3_SetDriveMode((uint8) pinsDm[console_SS3_PIN_INDEX]);

        console_SET_INP_DIS(console_spi_ss3_INP_DIS,
                                     console_spi_ss3_MASK,
                                     (0u != (pinsInBuf & console_SS3_PIN_MASK)));
    #endif /* (console_SS3_PIN) */
    }

#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (console_CY_SCBIP_V0 || console_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: console_I2CSlaveNackGeneration
    ********************************************************************************
    *
    * Summary:
    *  Sets command to generate NACK to the address or data.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void console_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (console_CTRL_REG & console_CTRL_EC_AM_MODE)) &&
            (0u == (console_I2C_CTRL_REG & console_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            console_CTRL_REG &= ~console_CTRL_EC_AM_MODE;
            console_CTRL_REG |=  console_CTRL_EC_AM_MODE;
        }

        console_I2C_SLAVE_CMD_REG = console_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (console_CY_SCBIP_V0 || console_CY_SCBIP_V1) */


/* [] END OF FILE */
