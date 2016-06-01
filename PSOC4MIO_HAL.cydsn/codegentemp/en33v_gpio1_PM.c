/*******************************************************************************
* File Name: en33v_gpio1.c  
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
#include "en33v_gpio1.h"

static en33v_gpio1_BACKUP_STRUCT  en33v_gpio1_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: en33v_gpio1_Sleep
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
*  \snippet en33v_gpio1_SUT.c usage_en33v_gpio1_Sleep_Wakeup
*******************************************************************************/
void en33v_gpio1_Sleep(void)
{
    #if defined(en33v_gpio1__PC)
        en33v_gpio1_backup.pcState = en33v_gpio1_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            en33v_gpio1_backup.usbState = en33v_gpio1_CR1_REG;
            en33v_gpio1_USB_POWER_REG |= en33v_gpio1_USBIO_ENTER_SLEEP;
            en33v_gpio1_CR1_REG &= en33v_gpio1_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(en33v_gpio1__SIO)
        en33v_gpio1_backup.sioState = en33v_gpio1_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        en33v_gpio1_SIO_REG &= (uint32)(~en33v_gpio1_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: en33v_gpio1_Wakeup
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
*  Refer to en33v_gpio1_Sleep() for an example usage.
*******************************************************************************/
void en33v_gpio1_Wakeup(void)
{
    #if defined(en33v_gpio1__PC)
        en33v_gpio1_PC = en33v_gpio1_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            en33v_gpio1_USB_POWER_REG &= en33v_gpio1_USBIO_EXIT_SLEEP_PH1;
            en33v_gpio1_CR1_REG = en33v_gpio1_backup.usbState;
            en33v_gpio1_USB_POWER_REG &= en33v_gpio1_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(en33v_gpio1__SIO)
        en33v_gpio1_SIO_REG = en33v_gpio1_backup.sioState;
    #endif
}


/* [] END OF FILE */
