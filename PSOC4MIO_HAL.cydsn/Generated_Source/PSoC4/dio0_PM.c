/*******************************************************************************
* File Name: dio0.c  
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
#include "dio0.h"

static dio0_BACKUP_STRUCT  dio0_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: dio0_Sleep
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
*  \snippet dio0_SUT.c usage_dio0_Sleep_Wakeup
*******************************************************************************/
void dio0_Sleep(void)
{
    #if defined(dio0__PC)
        dio0_backup.pcState = dio0_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            dio0_backup.usbState = dio0_CR1_REG;
            dio0_USB_POWER_REG |= dio0_USBIO_ENTER_SLEEP;
            dio0_CR1_REG &= dio0_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(dio0__SIO)
        dio0_backup.sioState = dio0_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        dio0_SIO_REG &= (uint32)(~dio0_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: dio0_Wakeup
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
*  Refer to dio0_Sleep() for an example usage.
*******************************************************************************/
void dio0_Wakeup(void)
{
    #if defined(dio0__PC)
        dio0_PC = dio0_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            dio0_USB_POWER_REG &= dio0_USBIO_EXIT_SLEEP_PH1;
            dio0_CR1_REG = dio0_backup.usbState;
            dio0_USB_POWER_REG &= dio0_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(dio0__SIO)
        dio0_SIO_REG = dio0_backup.sioState;
    #endif
}


/* [] END OF FILE */
