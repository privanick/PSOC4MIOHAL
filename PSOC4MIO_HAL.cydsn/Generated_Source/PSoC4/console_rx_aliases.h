/*******************************************************************************
* File Name: console_rx.h  
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

#if !defined(CY_PINS_console_rx_ALIASES_H) /* Pins console_rx_ALIASES_H */
#define CY_PINS_console_rx_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define console_rx_0			(console_rx__0__PC)
#define console_rx_0_PS		(console_rx__0__PS)
#define console_rx_0_PC		(console_rx__0__PC)
#define console_rx_0_DR		(console_rx__0__DR)
#define console_rx_0_SHIFT	(console_rx__0__SHIFT)
#define console_rx_0_INTR	((uint16)((uint16)0x0003u << (console_rx__0__SHIFT*2u)))

#define console_rx_INTR_ALL	 ((uint16)(console_rx_0_INTR))


#endif /* End Pins console_rx_ALIASES_H */


/* [] END OF FILE */
