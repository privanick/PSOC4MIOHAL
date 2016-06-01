/*******************************************************************************
* File Name: flow_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "flow.h"

static flow_BACKUP_STRUCT flow_backup;


/*******************************************************************************
* Function Name: flow_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void flow_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: flow_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void flow_Sleep(void)
{
    if(0u != (flow_BLOCK_CONTROL_REG & flow_MASK))
    {
        flow_backup.enableState = 1u;
    }
    else
    {
        flow_backup.enableState = 0u;
    }

    flow_Stop();
    flow_SaveConfig();
}


/*******************************************************************************
* Function Name: flow_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void flow_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: flow_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void flow_Wakeup(void)
{
    flow_RestoreConfig();

    if(0u != flow_backup.enableState)
    {
        flow_Enable();
    }
}


/* [] END OF FILE */
