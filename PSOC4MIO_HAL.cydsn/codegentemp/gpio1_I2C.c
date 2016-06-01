/***************************************************************************//**
* \file gpio1_I2C.c
* \version 3.20
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
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
#include "gpio1_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 gpio1_state;  /* Current state of I2C FSM */

#if(gpio1_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const gpio1_I2C_INIT_STRUCT gpio1_configI2C =
    {
        gpio1_I2C_MODE,
        gpio1_I2C_OVS_FACTOR_LOW,
        gpio1_I2C_OVS_FACTOR_HIGH,
        gpio1_I2C_MEDIAN_FILTER_ENABLE,
        gpio1_I2C_SLAVE_ADDRESS,
        gpio1_I2C_SLAVE_ADDRESS_MASK,
        gpio1_I2C_ACCEPT_ADDRESS,
        gpio1_I2C_WAKE_ENABLE,
        gpio1_I2C_BYTE_MODE_ENABLE,
        gpio1_I2C_DATA_RATE,
        gpio1_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: gpio1_I2CInit
    ****************************************************************************//**
    *
    *
    *  Configures the gpio1 for I2C operation.
    *
    *  This function is intended specifically to be used when the gpio1 
    *  configuration is set to “Unconfigured gpio1” in the customizer. 
    *  After initializing the gpio1 in I2C mode using this function, 
    *  the component can be enabled using the gpio1_Start() or 
    * gpio1_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void gpio1_I2CInit(const gpio1_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            gpio1_SetPins(gpio1_SCB_MODE_I2C, gpio1_DUMMY_PARAM,
                                     gpio1_DUMMY_PARAM);

            /* Store internal configuration */
            gpio1_scbMode       = (uint8) gpio1_SCB_MODE_I2C;
            gpio1_scbEnableWake = (uint8) config->enableWake;
            gpio1_scbEnableIntr = (uint8) gpio1_SCB_IRQ_INTERNAL;

            gpio1_mode          = (uint8) config->mode;
            gpio1_acceptAddr    = (uint8) config->acceptAddr;

        #if (gpio1_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            gpio1_SET_I2C_CFG_SDA_FILT_TRIM(gpio1_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (gpio1_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((gpio1_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= gpio1_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (gpio1_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                gpio1_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = gpio1_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                gpio1_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = gpio1_DIGITAL_FILTER_ENABLE;
            }

        #if (!gpio1_CY_SCBIP_V0)
            locEnableWake = (gpio1_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!gpio1_CY_SCBIP_V0) */

            /* Configure I2C interface */
            gpio1_CTRL_REG     = gpio1_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            gpio1_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            gpio1_GET_CTRL_EC_AM_MODE (locEnableWake);

            gpio1_I2C_CTRL_REG = gpio1_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    gpio1_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    gpio1_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    gpio1_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            gpio1_RX_CTRL_REG      = gpio1_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                gpio1_I2C_RX_CTRL;
            gpio1_RX_FIFO_CTRL_REG = gpio1_CLEAR_REG;

            /* Set default address and mask */
            gpio1_RX_MATCH_REG    = ((gpio1_I2C_SLAVE) ?
                                                (gpio1_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 gpio1_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (gpio1_CLEAR_REG));


            /* Configure TX direction */
            gpio1_TX_CTRL_REG      = gpio1_I2C_TX_CTRL;
            gpio1_TX_FIFO_CTRL_REG = gpio1_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (gpio1_ISR_NUMBER);
            CyIntSetPriority(gpio1_ISR_NUMBER, gpio1_ISR_PRIORITY);
            (void) CyIntSetVector(gpio1_ISR_NUMBER, &gpio1_I2C_ISR);

            /* Configure interrupt sources */
        #if(!gpio1_CY_SCBIP_V1)
            gpio1_INTR_SPI_EC_MASK_REG = gpio1_NO_INTR_SOURCES;
        #endif /* (!gpio1_CY_SCBIP_V1) */

            gpio1_INTR_I2C_EC_MASK_REG = gpio1_NO_INTR_SOURCES;
            gpio1_INTR_RX_MASK_REG     = gpio1_NO_INTR_SOURCES;
            gpio1_INTR_TX_MASK_REG     = gpio1_NO_INTR_SOURCES;

            gpio1_INTR_SLAVE_MASK_REG  = ((gpio1_I2C_SLAVE) ?
                            (gpio1_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             gpio1_I2C_INTR_SLAVE_MASK) : (gpio1_CLEAR_REG));

            gpio1_INTR_MASTER_MASK_REG = ((gpio1_I2C_MASTER) ?
                                                     (gpio1_I2C_INTR_MASTER_MASK) :
                                                     (gpio1_CLEAR_REG));

            /* Configure global variables */
            gpio1_state = gpio1_I2C_FSM_IDLE;

            /* Internal slave variables */
            gpio1_slStatus        = 0u;
            gpio1_slRdBufIndex    = 0u;
            gpio1_slWrBufIndex    = 0u;
            gpio1_slOverFlowCount = 0u;

            /* Internal master variables */
            gpio1_mstrStatus     = 0u;
            gpio1_mstrRdBufIndex = 0u;
            gpio1_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: gpio1_I2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the I2C operation.
    *
    *******************************************************************************/
    void gpio1_I2CInit(void)
    {
    #if(gpio1_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        gpio1_SET_I2C_CFG_SDA_FILT_TRIM(gpio1_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (gpio1_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        gpio1_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        gpio1_CTRL_REG     = gpio1_I2C_DEFAULT_CTRL;
        gpio1_I2C_CTRL_REG = gpio1_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        gpio1_RX_CTRL_REG      = gpio1_I2C_DEFAULT_RX_CTRL;
        gpio1_RX_FIFO_CTRL_REG = gpio1_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        gpio1_RX_MATCH_REG     = gpio1_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        gpio1_TX_CTRL_REG      = gpio1_I2C_DEFAULT_TX_CTRL;
        gpio1_TX_FIFO_CTRL_REG = gpio1_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (gpio1_ISR_NUMBER);
        CyIntSetPriority(gpio1_ISR_NUMBER, gpio1_ISR_PRIORITY);
    #if(!gpio1_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(gpio1_ISR_NUMBER, &gpio1_I2C_ISR);
    #endif /* (gpio1_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!gpio1_CY_SCBIP_V1)
        gpio1_INTR_SPI_EC_MASK_REG = gpio1_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!gpio1_CY_SCBIP_V1) */

        gpio1_INTR_I2C_EC_MASK_REG = gpio1_I2C_DEFAULT_INTR_I2C_EC_MASK;
        gpio1_INTR_SLAVE_MASK_REG  = gpio1_I2C_DEFAULT_INTR_SLAVE_MASK;
        gpio1_INTR_MASTER_MASK_REG = gpio1_I2C_DEFAULT_INTR_MASTER_MASK;
        gpio1_INTR_RX_MASK_REG     = gpio1_I2C_DEFAULT_INTR_RX_MASK;
        gpio1_INTR_TX_MASK_REG     = gpio1_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        gpio1_state = gpio1_I2C_FSM_IDLE;

    #if(gpio1_I2C_SLAVE)
        /* Internal slave variable */
        gpio1_slStatus        = 0u;
        gpio1_slRdBufIndex    = 0u;
        gpio1_slWrBufIndex    = 0u;
        gpio1_slOverFlowCount = 0u;
    #endif /* (gpio1_I2C_SLAVE) */

    #if(gpio1_I2C_MASTER)
    /* Internal master variable */
        gpio1_mstrStatus     = 0u;
        gpio1_mstrRdBufIndex = 0u;
        gpio1_mstrWrBufIndex = 0u;
    #endif /* (gpio1_I2C_MASTER) */
    }
#endif /* (gpio1_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: gpio1_I2CStop
****************************************************************************//**
*
*  Resets the I2C FSM into the default state.
*
*******************************************************************************/
void gpio1_I2CStop(void)
{
    gpio1_state = gpio1_I2C_FSM_IDLE;
}


#if(gpio1_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: gpio1_I2CSaveConfig
    ****************************************************************************//**
    *
    *  Enables gpio1_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void gpio1_I2CSaveConfig(void)
    {
    #if (!gpio1_CY_SCBIP_V0)
        #if (gpio1_I2C_MULTI_MASTER_SLAVE_CONST && gpio1_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (gpio1_CTRL_REG & gpio1_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                gpio1_Stop();
                gpio1_CTRL_REG |= gpio1_CTRL_EC_AM_MODE;
                gpio1_Enable();
            }
        #endif /* (gpio1_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (gpio1_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            gpio1_SCBCLK_Stop();
        #endif /* (gpio1_SCB_CLK_INTERNAL) */
    #endif /* (!gpio1_CY_SCBIP_V0) */

        gpio1_SetI2CExtClkInterruptMode(gpio1_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: gpio1_I2CRestoreConfig
    ****************************************************************************//**
    *
    *  Disables gpio1_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void gpio1_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        gpio1_SetI2CExtClkInterruptMode(gpio1_NO_INTR_SOURCES);

    #if (!gpio1_CY_SCBIP_V0)
        #if (gpio1_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            gpio1_SCBCLK_Start();
        #endif /* (gpio1_SCB_CLK_INTERNAL) */
    #endif /* (!gpio1_CY_SCBIP_V0) */
    }
#endif /* (gpio1_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
