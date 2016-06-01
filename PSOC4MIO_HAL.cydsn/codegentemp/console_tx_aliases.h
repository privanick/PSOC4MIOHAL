/*******************************************************************************
* File Name: console_tx.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_console_tx_ALIASES_H) /* Pins console_tx_ALIASES_H */
#define CY_PINS_console_tx_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define console_tx_0			(console_tx__0__PC)
#define console_tx_0_PS		(console_tx__0__PS)
#define console_tx_0_PC		(console_tx__0__PC)
#define console_tx_0_DR		(console_tx__0__DR)
#define console_tx_0_SHIFT	(console_tx__0__SHIFT)
#define console_tx_0_INTR	((uint16)((uint16)0x0003u << (console_tx__0__SHIFT*2u)))

#define console_tx_INTR_ALL	 ((uint16)(console_tx_0_INTR))


#endif /* End Pins console_tx_ALIASES_H */


/* [] END OF FILE */
