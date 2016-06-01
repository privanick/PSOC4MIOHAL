/*******************************************************************************
* File Name: gpio1IP.h  
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

#if !defined(CY_PINS_gpio1IP_ALIASES_H) /* Pins gpio1IP_ALIASES_H */
#define CY_PINS_gpio1IP_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define gpio1IP_0			(gpio1IP__0__PC)
#define gpio1IP_0_PS		(gpio1IP__0__PS)
#define gpio1IP_0_PC		(gpio1IP__0__PC)
#define gpio1IP_0_DR		(gpio1IP__0__DR)
#define gpio1IP_0_SHIFT	(gpio1IP__0__SHIFT)
#define gpio1IP_0_INTR	((uint16)((uint16)0x0003u << (gpio1IP__0__SHIFT*2u)))

#define gpio1IP_INTR_ALL	 ((uint16)(gpio1IP_0_INTR))


#endif /* End Pins gpio1IP_ALIASES_H */


/* [] END OF FILE */
