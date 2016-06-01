/*******************************************************************************
* File Name: pwr_en_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "pwr_en.h"

/* Check for removal by optimization */
#if !defined(pwr_en_Sync_ctrl_reg__REMOVED)

static pwr_en_BACKUP_STRUCT  pwr_en_backup = {0u};

    
/*******************************************************************************
* Function Name: pwr_en_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void pwr_en_SaveConfig(void) 
{
    pwr_en_backup.controlState = pwr_en_Control;
}


/*******************************************************************************
* Function Name: pwr_en_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void pwr_en_RestoreConfig(void) 
{
     pwr_en_Control = pwr_en_backup.controlState;
}


/*******************************************************************************
* Function Name: pwr_en_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void pwr_en_Sleep(void) 
{
    pwr_en_SaveConfig();
}


/*******************************************************************************
* Function Name: pwr_en_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void pwr_en_Wakeup(void)  
{
    pwr_en_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
