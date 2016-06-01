/***************************************************************************//**
* \file gpio1_PM.c
* \version 3.20
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
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

#include "gpio1.h"
#include "gpio1_PVT.h"

#if(gpio1_SCB_MODE_I2C_INC)
    #include "gpio1_I2C_PVT.h"
#endif /* (gpio1_SCB_MODE_I2C_INC) */

#if(gpio1_SCB_MODE_EZI2C_INC)
    #include "gpio1_EZI2C_PVT.h"
#endif /* (gpio1_SCB_MODE_EZI2C_INC) */

#if(gpio1_SCB_MODE_SPI_INC || gpio1_SCB_MODE_UART_INC)
    #include "gpio1_SPI_UART_PVT.h"
#endif /* (gpio1_SCB_MODE_SPI_INC || gpio1_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(gpio1_SCB_MODE_UNCONFIG_CONST_CFG || \
   (gpio1_SCB_MODE_I2C_CONST_CFG   && (!gpio1_I2C_WAKE_ENABLE_CONST))   || \
   (gpio1_SCB_MODE_EZI2C_CONST_CFG && (!gpio1_EZI2C_WAKE_ENABLE_CONST)) || \
   (gpio1_SCB_MODE_SPI_CONST_CFG   && (!gpio1_SPI_WAKE_ENABLE_CONST))   || \
   (gpio1_SCB_MODE_UART_CONST_CFG  && (!gpio1_UART_WAKE_ENABLE_CONST)))

    gpio1_BACKUP_STRUCT gpio1_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: gpio1_Sleep
****************************************************************************//**
*
*  Prepares the gpio1 component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the gpio1_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void gpio1_Sleep(void)
{
#if(gpio1_SCB_MODE_UNCONFIG_CONST_CFG)

    if(gpio1_SCB_WAKE_ENABLE_CHECK)
    {
        if(gpio1_SCB_MODE_I2C_RUNTM_CFG)
        {
            gpio1_I2CSaveConfig();
        }
        else if(gpio1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            gpio1_EzI2CSaveConfig();
        }
    #if(!gpio1_CY_SCBIP_V1)
        else if(gpio1_SCB_MODE_SPI_RUNTM_CFG)
        {
            gpio1_SpiSaveConfig();
        }
        else if(gpio1_SCB_MODE_UART_RUNTM_CFG)
        {
            gpio1_UartSaveConfig();
        }
    #endif /* (!gpio1_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        gpio1_backup.enableState = (uint8) gpio1_GET_CTRL_ENABLED;

        if(0u != gpio1_backup.enableState)
        {
            gpio1_Stop();
        }
    }

#else

    #if (gpio1_SCB_MODE_I2C_CONST_CFG && gpio1_I2C_WAKE_ENABLE_CONST)
        gpio1_I2CSaveConfig();

    #elif (gpio1_SCB_MODE_EZI2C_CONST_CFG && gpio1_EZI2C_WAKE_ENABLE_CONST)
        gpio1_EzI2CSaveConfig();

    #elif (gpio1_SCB_MODE_SPI_CONST_CFG && gpio1_SPI_WAKE_ENABLE_CONST)
        gpio1_SpiSaveConfig();

    #elif (gpio1_SCB_MODE_UART_CONST_CFG && gpio1_UART_WAKE_ENABLE_CONST)
        gpio1_UartSaveConfig();

    #else

        gpio1_backup.enableState = (uint8) gpio1_GET_CTRL_ENABLED;

        if(0u != gpio1_backup.enableState)
        {
            gpio1_Stop();
        }

    #endif /* defined (gpio1_SCB_MODE_I2C_CONST_CFG) && (gpio1_I2C_WAKE_ENABLE_CONST) */

#endif /* (gpio1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: gpio1_Wakeup
****************************************************************************//**
*
*  Prepares the gpio1 component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the gpio1_Wakeup() function without first calling the 
*   gpio1_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void gpio1_Wakeup(void)
{
#if(gpio1_SCB_MODE_UNCONFIG_CONST_CFG)

    if(gpio1_SCB_WAKE_ENABLE_CHECK)
    {
        if(gpio1_SCB_MODE_I2C_RUNTM_CFG)
        {
            gpio1_I2CRestoreConfig();
        }
        else if(gpio1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            gpio1_EzI2CRestoreConfig();
        }
    #if(!gpio1_CY_SCBIP_V1)
        else if(gpio1_SCB_MODE_SPI_RUNTM_CFG)
        {
            gpio1_SpiRestoreConfig();
        }
        else if(gpio1_SCB_MODE_UART_RUNTM_CFG)
        {
            gpio1_UartRestoreConfig();
        }
    #endif /* (!gpio1_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != gpio1_backup.enableState)
        {
            gpio1_Enable();
        }
    }

#else

    #if (gpio1_SCB_MODE_I2C_CONST_CFG  && gpio1_I2C_WAKE_ENABLE_CONST)
        gpio1_I2CRestoreConfig();

    #elif (gpio1_SCB_MODE_EZI2C_CONST_CFG && gpio1_EZI2C_WAKE_ENABLE_CONST)
        gpio1_EzI2CRestoreConfig();

    #elif (gpio1_SCB_MODE_SPI_CONST_CFG && gpio1_SPI_WAKE_ENABLE_CONST)
        gpio1_SpiRestoreConfig();

    #elif (gpio1_SCB_MODE_UART_CONST_CFG && gpio1_UART_WAKE_ENABLE_CONST)
        gpio1_UartRestoreConfig();

    #else

        if(0u != gpio1_backup.enableState)
        {
            gpio1_Enable();
        }

    #endif /* (gpio1_I2C_WAKE_ENABLE_CONST) */

#endif /* (gpio1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
