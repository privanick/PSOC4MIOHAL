/*******************************************************************************
* File Name: sectimer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "sectimer.h"

static sectimer_backupStruct sectimer_backup;


/*******************************************************************************
* Function Name: sectimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  sectimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void sectimer_SaveConfig(void) 
{
    #if (!sectimer_UsingFixedFunction)
        sectimer_backup.TimerUdb = sectimer_ReadCounter();
        sectimer_backup.InterruptMaskValue = sectimer_STATUS_MASK;
        #if (sectimer_UsingHWCaptureCounter)
            sectimer_backup.TimerCaptureCounter = sectimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!sectimer_UDB_CONTROL_REG_REMOVED)
            sectimer_backup.TimerControlRegister = sectimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: sectimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  sectimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void sectimer_RestoreConfig(void) 
{   
    #if (!sectimer_UsingFixedFunction)

        sectimer_WriteCounter(sectimer_backup.TimerUdb);
        sectimer_STATUS_MASK =sectimer_backup.InterruptMaskValue;
        #if (sectimer_UsingHWCaptureCounter)
            sectimer_SetCaptureCount(sectimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!sectimer_UDB_CONTROL_REG_REMOVED)
            sectimer_WriteControlRegister(sectimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: sectimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  sectimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void sectimer_Sleep(void) 
{
    #if(!sectimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(sectimer_CTRL_ENABLE == (sectimer_CONTROL & sectimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            sectimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            sectimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    sectimer_Stop();
    sectimer_SaveConfig();
}


/*******************************************************************************
* Function Name: sectimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  sectimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void sectimer_Wakeup(void) 
{
    sectimer_RestoreConfig();
    #if(!sectimer_UDB_CONTROL_REG_REMOVED)
        if(sectimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                sectimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
