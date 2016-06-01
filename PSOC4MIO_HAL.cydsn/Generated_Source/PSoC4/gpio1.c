/***************************************************************************//**
* \file gpio1.c
* \version 3.20
*
* \brief
*  This file provides the source code to the API for the SCB Component.
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

#include "gpio1_PVT.h"

#if (gpio1_SCB_MODE_I2C_INC)
    #include "gpio1_I2C_PVT.h"
#endif /* (gpio1_SCB_MODE_I2C_INC) */

#if (gpio1_SCB_MODE_EZI2C_INC)
    #include "gpio1_EZI2C_PVT.h"
#endif /* (gpio1_SCB_MODE_EZI2C_INC) */

#if (gpio1_SCB_MODE_SPI_INC || gpio1_SCB_MODE_UART_INC)
    #include "gpio1_SPI_UART_PVT.h"
#endif /* (gpio1_SCB_MODE_SPI_INC || gpio1_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (gpio1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 gpio1_scbMode = gpio1_SCB_MODE_UNCONFIG;
    uint8 gpio1_scbEnableWake;
    uint8 gpio1_scbEnableIntr;

    /* I2C configuration variables */
    uint8 gpio1_mode;
    uint8 gpio1_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * gpio1_rxBuffer;
    uint8  gpio1_rxDataBits;
    uint32 gpio1_rxBufferSize;

    volatile uint8 * gpio1_txBuffer;
    uint8  gpio1_txDataBits;
    uint32 gpio1_txBufferSize;

    /* EZI2C configuration variables */
    uint8 gpio1_numberOfAddr;
    uint8 gpio1_subAddrSize;
#endif /* (gpio1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** gpio1_initVar indicates whether the gpio1 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the gpio1_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  gpio1_Init() function can be called before the 
*  gpio1_Start() or gpio1_Enable() function.
*/
uint8 gpio1_initVar = 0u;


#if (! (gpio1_SCB_MODE_I2C_CONST_CFG || \
        gpio1_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * gpio1_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent gpio1_Enable() call.
    */
    uint16 gpio1_IntrTxMask = 0u;
#endif /* (! (gpio1_SCB_MODE_I2C_CONST_CFG || \
              gpio1_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (gpio1_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_gpio1_CUSTOM_INTR_HANDLER)
    void (*gpio1_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_gpio1_CUSTOM_INTR_HANDLER) */
#endif /* (gpio1_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void gpio1_ScbEnableIntr(void);
static void gpio1_ScbModeStop(void);
static void gpio1_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: gpio1_Init
****************************************************************************//**
*
*  Initializes the gpio1 component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  gpio1_I2CInit, gpio1_SpiInit, 
*  gpio1_UartInit or gpio1_EzI2CInit.
*
*******************************************************************************/
void gpio1_Init(void)
{
#if (gpio1_SCB_MODE_UNCONFIG_CONST_CFG)
    if (gpio1_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        gpio1_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (gpio1_SCB_MODE_I2C_CONST_CFG)
    gpio1_I2CInit();

#elif (gpio1_SCB_MODE_SPI_CONST_CFG)
    gpio1_SpiInit();

#elif (gpio1_SCB_MODE_UART_CONST_CFG)
    gpio1_UartInit();

#elif (gpio1_SCB_MODE_EZI2C_CONST_CFG)
    gpio1_EzI2CInit();

#endif /* (gpio1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: gpio1_Enable
****************************************************************************//**
*
*  Enables gpio1 component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  gpio1_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The gpio1 configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured gpio1”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void gpio1_Enable(void)
{
#if (gpio1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!gpio1_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        gpio1_CTRL_REG |= gpio1_CTRL_ENABLED;

        gpio1_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        gpio1_ScbModePostEnable();
    }
#else
    gpio1_CTRL_REG |= gpio1_CTRL_ENABLED;

    gpio1_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    gpio1_ScbModePostEnable();
#endif /* (gpio1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: gpio1_Start
****************************************************************************//**
*
*  Invokes gpio1_Init() and gpio1_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  gpio1_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void gpio1_Start(void)
{
    if (0u == gpio1_initVar)
    {
        gpio1_Init();
        gpio1_initVar = 1u; /* Component was initialized */
    }

    gpio1_Enable();
}


/*******************************************************************************
* Function Name: gpio1_Stop
****************************************************************************//**
*
*  Disables the gpio1 component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function gpio1_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void gpio1_Stop(void)
{
#if (gpio1_SCB_IRQ_INTERNAL)
    gpio1_DisableInt();
#endif /* (gpio1_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    gpio1_ScbModeStop();

    /* Disable SCB IP */
    gpio1_CTRL_REG &= (uint32) ~gpio1_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    gpio1_SetTxInterruptMode(gpio1_NO_INTR_SOURCES);

#if (gpio1_SCB_IRQ_INTERNAL)
    gpio1_ClearPendingInt();
#endif /* (gpio1_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: gpio1_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void gpio1_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = gpio1_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~gpio1_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (gpio1_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    gpio1_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: gpio1_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void gpio1_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = gpio1_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~gpio1_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (gpio1_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    gpio1_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (gpio1_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: gpio1_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void gpio1_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_gpio1_CUSTOM_INTR_HANDLER)
        gpio1_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_gpio1_CUSTOM_INTR_HANDLER) */
    }
#endif /* (gpio1_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: gpio1_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void gpio1_ScbEnableIntr(void)
{
#if (gpio1_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (gpio1_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != gpio1_scbEnableIntr)
        {
            gpio1_EnableInt();
        }

    #else
        gpio1_EnableInt();

    #endif /* (gpio1_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (gpio1_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: gpio1_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void gpio1_ScbModePostEnable(void)
{
#if (gpio1_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!gpio1_CY_SCBIP_V1)
    if (gpio1_SCB_MODE_SPI_RUNTM_CFG)
    {
        gpio1_SpiPostEnable();
    }
    else if (gpio1_SCB_MODE_UART_RUNTM_CFG)
    {
        gpio1_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!gpio1_CY_SCBIP_V1) */

#elif (gpio1_SCB_MODE_SPI_CONST_CFG)
    gpio1_SpiPostEnable();

#elif (gpio1_SCB_MODE_UART_CONST_CFG)
    gpio1_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (gpio1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: gpio1_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void gpio1_ScbModeStop(void)
{
#if (gpio1_SCB_MODE_UNCONFIG_CONST_CFG)
    if (gpio1_SCB_MODE_I2C_RUNTM_CFG)
    {
        gpio1_I2CStop();
    }
    else if (gpio1_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        gpio1_EzI2CStop();
    }
#if (!gpio1_CY_SCBIP_V1)
    else if (gpio1_SCB_MODE_SPI_RUNTM_CFG)
    {
        gpio1_SpiStop();
    }
    else if (gpio1_SCB_MODE_UART_RUNTM_CFG)
    {
        gpio1_UartStop();
    }
#endif /* (!gpio1_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (gpio1_SCB_MODE_I2C_CONST_CFG)
    gpio1_I2CStop();

#elif (gpio1_SCB_MODE_EZI2C_CONST_CFG)
    gpio1_EzI2CStop();

#elif (gpio1_SCB_MODE_SPI_CONST_CFG)
    gpio1_SpiStop();

#elif (gpio1_SCB_MODE_UART_CONST_CFG)
    gpio1_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (gpio1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (gpio1_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: gpio1_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void gpio1_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[gpio1_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!gpio1_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!gpio1_CY_SCBIP_V1) */
        
        uint32 hsiomSel[gpio1_SCB_PINS_NUMBER] = 
        {
            gpio1_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            gpio1_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (gpio1_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (gpio1_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < gpio1_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = gpio1_PIN_DM_ALG_HIZ;
        }

        if ((gpio1_SCB_MODE_I2C   == mode) ||
            (gpio1_SCB_MODE_EZI2C == mode))
        {
        #if (gpio1_RX_SCL_MOSI_PIN)
            hsiomSel[gpio1_RX_SCL_MOSI_PIN_INDEX] = gpio1_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [gpio1_RX_SCL_MOSI_PIN_INDEX] = gpio1_PIN_DM_OD_LO;
        #elif (gpio1_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[gpio1_RX_WAKE_SCL_MOSI_PIN_INDEX] = gpio1_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [gpio1_RX_WAKE_SCL_MOSI_PIN_INDEX] = gpio1_PIN_DM_OD_LO;
        #else
        #endif /* (gpio1_RX_SCL_MOSI_PIN) */
        
        #if (gpio1_TX_SDA_MISO_PIN)
            hsiomSel[gpio1_TX_SDA_MISO_PIN_INDEX] = gpio1_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [gpio1_TX_SDA_MISO_PIN_INDEX] = gpio1_PIN_DM_OD_LO;
        #endif /* (gpio1_TX_SDA_MISO_PIN) */
        }
    #if (!gpio1_CY_SCBIP_V1)
        else if (gpio1_SCB_MODE_SPI == mode)
        {
        #if (gpio1_RX_SCL_MOSI_PIN)
            hsiomSel[gpio1_RX_SCL_MOSI_PIN_INDEX] = gpio1_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (gpio1_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[gpio1_RX_WAKE_SCL_MOSI_PIN_INDEX] = gpio1_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (gpio1_RX_SCL_MOSI_PIN) */
        
        #if (gpio1_TX_SDA_MISO_PIN)
            hsiomSel[gpio1_TX_SDA_MISO_PIN_INDEX] = gpio1_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (gpio1_TX_SDA_MISO_PIN) */
        
        #if (gpio1_CTS_SCLK_PIN)
            hsiomSel[gpio1_CTS_SCLK_PIN_INDEX] = gpio1_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (gpio1_CTS_SCLK_PIN) */

            if (gpio1_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[gpio1_RX_SCL_MOSI_PIN_INDEX] = gpio1_PIN_DM_DIG_HIZ;
                pinsDm[gpio1_TX_SDA_MISO_PIN_INDEX] = gpio1_PIN_DM_STRONG;
                pinsDm[gpio1_CTS_SCLK_PIN_INDEX] = gpio1_PIN_DM_DIG_HIZ;

            #if (gpio1_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[gpio1_RTS_SS0_PIN_INDEX] = gpio1_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [gpio1_RTS_SS0_PIN_INDEX] = gpio1_PIN_DM_DIG_HIZ;
            #endif /* (gpio1_RTS_SS0_PIN) */

            #if (gpio1_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= gpio1_TX_SDA_MISO_PIN_MASK;
            #endif /* (gpio1_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[gpio1_RX_SCL_MOSI_PIN_INDEX] = gpio1_PIN_DM_STRONG;
                pinsDm[gpio1_TX_SDA_MISO_PIN_INDEX] = gpio1_PIN_DM_DIG_HIZ;
                pinsDm[gpio1_CTS_SCLK_PIN_INDEX] = gpio1_PIN_DM_STRONG;

            #if (gpio1_RTS_SS0_PIN)
                hsiomSel [gpio1_RTS_SS0_PIN_INDEX] = gpio1_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [gpio1_RTS_SS0_PIN_INDEX] = gpio1_PIN_DM_STRONG;
                pinsInBuf |= gpio1_RTS_SS0_PIN_MASK;
            #endif /* (gpio1_RTS_SS0_PIN) */

            #if (gpio1_SS1_PIN)
                hsiomSel [gpio1_SS1_PIN_INDEX] = gpio1_SS1_HSIOM_SEL_SPI;
                pinsDm   [gpio1_SS1_PIN_INDEX] = gpio1_PIN_DM_STRONG;
                pinsInBuf |= gpio1_SS1_PIN_MASK;
            #endif /* (gpio1_SS1_PIN) */

            #if (gpio1_SS2_PIN)
                hsiomSel [gpio1_SS2_PIN_INDEX] = gpio1_SS2_HSIOM_SEL_SPI;
                pinsDm   [gpio1_SS2_PIN_INDEX] = gpio1_PIN_DM_STRONG;
                pinsInBuf |= gpio1_SS2_PIN_MASK;
            #endif /* (gpio1_SS2_PIN) */

            #if (gpio1_SS3_PIN)
                hsiomSel [gpio1_SS3_PIN_INDEX] = gpio1_SS3_HSIOM_SEL_SPI;
                pinsDm   [gpio1_SS3_PIN_INDEX] = gpio1_PIN_DM_STRONG;
                pinsInBuf |= gpio1_SS3_PIN_MASK;
            #endif /* (gpio1_SS3_PIN) */

                /* Disable input buffers */
            #if (gpio1_RX_SCL_MOSI_PIN)
                pinsInBuf |= gpio1_RX_SCL_MOSI_PIN_MASK;
            #elif (gpio1_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= gpio1_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (gpio1_RX_SCL_MOSI_PIN) */

            #if (gpio1_CTS_SCLK_PIN)
                pinsInBuf |= gpio1_CTS_SCLK_PIN_MASK;
            #endif /* (gpio1_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (gpio1_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (gpio1_TX_SDA_MISO_PIN)
                hsiomSel[gpio1_TX_SDA_MISO_PIN_INDEX] = gpio1_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [gpio1_TX_SDA_MISO_PIN_INDEX] = gpio1_PIN_DM_OD_LO;
            #endif /* (gpio1_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (gpio1_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (gpio1_RX_SCL_MOSI_PIN)
                    hsiomSel[gpio1_RX_SCL_MOSI_PIN_INDEX] = gpio1_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [gpio1_RX_SCL_MOSI_PIN_INDEX] = gpio1_PIN_DM_DIG_HIZ;
                #elif (gpio1_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[gpio1_RX_WAKE_SCL_MOSI_PIN_INDEX] = gpio1_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [gpio1_RX_WAKE_SCL_MOSI_PIN_INDEX] = gpio1_PIN_DM_DIG_HIZ;
                #else
                #endif /* (gpio1_RX_SCL_MOSI_PIN) */
                }

                if (0u != (gpio1_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (gpio1_TX_SDA_MISO_PIN)
                    hsiomSel[gpio1_TX_SDA_MISO_PIN_INDEX] = gpio1_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [gpio1_TX_SDA_MISO_PIN_INDEX] = gpio1_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= gpio1_TX_SDA_MISO_PIN_MASK;
                #endif /* (gpio1_TX_SDA_MISO_PIN) */
                }

            #if !(gpio1_CY_SCBIP_V0 || gpio1_CY_SCBIP_V1)
                if (gpio1_UART_MODE_STD == subMode)
                {
                    if (0u != (gpio1_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (gpio1_CTS_SCLK_PIN)
                        hsiomSel[gpio1_CTS_SCLK_PIN_INDEX] = gpio1_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [gpio1_CTS_SCLK_PIN_INDEX] = gpio1_PIN_DM_DIG_HIZ;
                    #endif /* (gpio1_CTS_SCLK_PIN) */
                    }

                    if (0u != (gpio1_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (gpio1_RTS_SS0_PIN)
                        hsiomSel[gpio1_RTS_SS0_PIN_INDEX] = gpio1_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [gpio1_RTS_SS0_PIN_INDEX] = gpio1_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= gpio1_RTS_SS0_PIN_MASK;
                    #endif /* (gpio1_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(gpio1_CY_SCBIP_V0 || gpio1_CY_SCBIP_V1) */
            }
        }
    #endif /* (!gpio1_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (gpio1_RX_SCL_MOSI_PIN)
        gpio1_SET_HSIOM_SEL(gpio1_RX_SCL_MOSI_HSIOM_REG,
                                       gpio1_RX_SCL_MOSI_HSIOM_MASK,
                                       gpio1_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[gpio1_RX_SCL_MOSI_PIN_INDEX]);

        gpio1_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[gpio1_RX_SCL_MOSI_PIN_INDEX]);

        #if (!gpio1_CY_SCBIP_V1)
            gpio1_SET_INP_DIS(gpio1_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         gpio1_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & gpio1_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!gpio1_CY_SCBIP_V1) */
    
    #elif (gpio1_RX_WAKE_SCL_MOSI_PIN)
        gpio1_SET_HSIOM_SEL(gpio1_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       gpio1_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       gpio1_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[gpio1_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        gpio1_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[gpio1_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        gpio1_SET_INP_DIS(gpio1_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     gpio1_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & gpio1_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        gpio1_SET_INCFG_TYPE(gpio1_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        gpio1_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        gpio1_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        gpio1_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (gpio1_RX_WAKE_SCL_MOSI_PIN) */

    #if (gpio1_TX_SDA_MISO_PIN)
        gpio1_SET_HSIOM_SEL(gpio1_TX_SDA_MISO_HSIOM_REG,
                                       gpio1_TX_SDA_MISO_HSIOM_MASK,
                                       gpio1_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[gpio1_TX_SDA_MISO_PIN_INDEX]);

        gpio1_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[gpio1_TX_SDA_MISO_PIN_INDEX]);

    #if (!gpio1_CY_SCBIP_V1)
        gpio1_SET_INP_DIS(gpio1_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     gpio1_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & gpio1_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!gpio1_CY_SCBIP_V1) */
    #endif /* (gpio1_RX_SCL_MOSI_PIN) */

    #if (gpio1_CTS_SCLK_PIN)
        gpio1_SET_HSIOM_SEL(gpio1_CTS_SCLK_HSIOM_REG,
                                       gpio1_CTS_SCLK_HSIOM_MASK,
                                       gpio1_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[gpio1_CTS_SCLK_PIN_INDEX]);

        gpio1_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[gpio1_CTS_SCLK_PIN_INDEX]);

        gpio1_SET_INP_DIS(gpio1_uart_cts_spi_sclk_INP_DIS,
                                     gpio1_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & gpio1_CTS_SCLK_PIN_MASK)));
    #endif /* (gpio1_CTS_SCLK_PIN) */

    #if (gpio1_RTS_SS0_PIN)
        gpio1_SET_HSIOM_SEL(gpio1_RTS_SS0_HSIOM_REG,
                                       gpio1_RTS_SS0_HSIOM_MASK,
                                       gpio1_RTS_SS0_HSIOM_POS,
                                       hsiomSel[gpio1_RTS_SS0_PIN_INDEX]);

        gpio1_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[gpio1_RTS_SS0_PIN_INDEX]);

        gpio1_SET_INP_DIS(gpio1_uart_rts_spi_ss0_INP_DIS,
                                     gpio1_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & gpio1_RTS_SS0_PIN_MASK)));
    #endif /* (gpio1_RTS_SS0_PIN) */

    #if (gpio1_SS1_PIN)
        gpio1_SET_HSIOM_SEL(gpio1_SS1_HSIOM_REG,
                                       gpio1_SS1_HSIOM_MASK,
                                       gpio1_SS1_HSIOM_POS,
                                       hsiomSel[gpio1_SS1_PIN_INDEX]);

        gpio1_spi_ss1_SetDriveMode((uint8) pinsDm[gpio1_SS1_PIN_INDEX]);

        gpio1_SET_INP_DIS(gpio1_spi_ss1_INP_DIS,
                                     gpio1_spi_ss1_MASK,
                                     (0u != (pinsInBuf & gpio1_SS1_PIN_MASK)));
    #endif /* (gpio1_SS1_PIN) */

    #if (gpio1_SS2_PIN)
        gpio1_SET_HSIOM_SEL(gpio1_SS2_HSIOM_REG,
                                       gpio1_SS2_HSIOM_MASK,
                                       gpio1_SS2_HSIOM_POS,
                                       hsiomSel[gpio1_SS2_PIN_INDEX]);

        gpio1_spi_ss2_SetDriveMode((uint8) pinsDm[gpio1_SS2_PIN_INDEX]);

        gpio1_SET_INP_DIS(gpio1_spi_ss2_INP_DIS,
                                     gpio1_spi_ss2_MASK,
                                     (0u != (pinsInBuf & gpio1_SS2_PIN_MASK)));
    #endif /* (gpio1_SS2_PIN) */

    #if (gpio1_SS3_PIN)
        gpio1_SET_HSIOM_SEL(gpio1_SS3_HSIOM_REG,
                                       gpio1_SS3_HSIOM_MASK,
                                       gpio1_SS3_HSIOM_POS,
                                       hsiomSel[gpio1_SS3_PIN_INDEX]);

        gpio1_spi_ss3_SetDriveMode((uint8) pinsDm[gpio1_SS3_PIN_INDEX]);

        gpio1_SET_INP_DIS(gpio1_spi_ss3_INP_DIS,
                                     gpio1_spi_ss3_MASK,
                                     (0u != (pinsInBuf & gpio1_SS3_PIN_MASK)));
    #endif /* (gpio1_SS3_PIN) */
    }

#endif /* (gpio1_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (gpio1_CY_SCBIP_V0 || gpio1_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: gpio1_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void gpio1_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (gpio1_CTRL_REG & gpio1_CTRL_EC_AM_MODE)) &&
            (0u == (gpio1_I2C_CTRL_REG & gpio1_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            gpio1_CTRL_REG &= ~gpio1_CTRL_EC_AM_MODE;
            gpio1_CTRL_REG |=  gpio1_CTRL_EC_AM_MODE;
        }

        gpio1_I2C_SLAVE_CMD_REG = gpio1_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (gpio1_CY_SCBIP_V0 || gpio1_CY_SCBIP_V1) */


/* [] END OF FILE */
