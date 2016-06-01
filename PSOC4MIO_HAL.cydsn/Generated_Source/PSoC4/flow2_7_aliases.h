/*******************************************************************************
* File Name: flow2_7.h  
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

#if !defined(CY_PINS_flow2_7_ALIASES_H) /* Pins flow2_7_ALIASES_H */
#define CY_PINS_flow2_7_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define flow2_7_0			(flow2_7__0__PC)
#define flow2_7_0_PS		(flow2_7__0__PS)
#define flow2_7_0_PC		(flow2_7__0__PC)
#define flow2_7_0_DR		(flow2_7__0__DR)
#define flow2_7_0_SHIFT	(flow2_7__0__SHIFT)
#define flow2_7_0_INTR	((uint16)((uint16)0x0003u << (flow2_7__0__SHIFT*2u)))

#define flow2_7_INTR_ALL	 ((uint16)(flow2_7_0_INTR))


#endif /* End Pins flow2_7_ALIASES_H */


/* [] END OF FILE */
