/*******************************************************************************
* File Name: gpio1IP.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "gpio1IP.h"

static gpio1IP_BACKUP_STRUCT  gpio1IP_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: gpio1IP_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet gpio1IP_SUT.c usage_gpio1IP_Sleep_Wakeup
*******************************************************************************/
void gpio1IP_Sleep(void)
{
    #if defined(gpio1IP__PC)
        gpio1IP_backup.pcState = gpio1IP_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            gpio1IP_backup.usbState = gpio1IP_CR1_REG;
            gpio1IP_USB_POWER_REG |= gpio1IP_USBIO_ENTER_SLEEP;
            gpio1IP_CR1_REG &= gpio1IP_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(gpio1IP__SIO)
        gpio1IP_backup.sioState = gpio1IP_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        gpio1IP_SIO_REG &= (uint32)(~gpio1IP_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: gpio1IP_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to gpio1IP_Sleep() for an example usage.
*******************************************************************************/
void gpio1IP_Wakeup(void)
{
    #if defined(gpio1IP__PC)
        gpio1IP_PC = gpio1IP_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            gpio1IP_USB_POWER_REG &= gpio1IP_USBIO_EXIT_SLEEP_PH1;
            gpio1IP_CR1_REG = gpio1IP_backup.usbState;
            gpio1IP_USB_POWER_REG &= gpio1IP_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(gpio1IP__SIO)
        gpio1IP_SIO_REG = gpio1IP_backup.sioState;
    #endif
}


/* [] END OF FILE */
