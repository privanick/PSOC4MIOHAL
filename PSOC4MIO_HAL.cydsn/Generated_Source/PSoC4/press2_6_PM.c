/*******************************************************************************
* File Name: press2_6.c  
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
#include "press2_6.h"

static press2_6_BACKUP_STRUCT  press2_6_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: press2_6_Sleep
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
*  \snippet press2_6_SUT.c usage_press2_6_Sleep_Wakeup
*******************************************************************************/
void press2_6_Sleep(void)
{
    #if defined(press2_6__PC)
        press2_6_backup.pcState = press2_6_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            press2_6_backup.usbState = press2_6_CR1_REG;
            press2_6_USB_POWER_REG |= press2_6_USBIO_ENTER_SLEEP;
            press2_6_CR1_REG &= press2_6_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(press2_6__SIO)
        press2_6_backup.sioState = press2_6_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        press2_6_SIO_REG &= (uint32)(~press2_6_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: press2_6_Wakeup
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
*  Refer to press2_6_Sleep() for an example usage.
*******************************************************************************/
void press2_6_Wakeup(void)
{
    #if defined(press2_6__PC)
        press2_6_PC = press2_6_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            press2_6_USB_POWER_REG &= press2_6_USBIO_EXIT_SLEEP_PH1;
            press2_6_CR1_REG = press2_6_backup.usbState;
            press2_6_USB_POWER_REG &= press2_6_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(press2_6__SIO)
        press2_6_SIO_REG = press2_6_backup.sioState;
    #endif
}


/* [] END OF FILE */
