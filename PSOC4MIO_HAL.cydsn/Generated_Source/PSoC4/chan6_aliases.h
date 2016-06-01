/*******************************************************************************
* File Name: chan6.h  
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

#if !defined(CY_PINS_chan6_ALIASES_H) /* Pins chan6_ALIASES_H */
#define CY_PINS_chan6_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define chan6_0			(chan6__0__PC)
#define chan6_0_PS		(chan6__0__PS)
#define chan6_0_PC		(chan6__0__PC)
#define chan6_0_DR		(chan6__0__DR)
#define chan6_0_SHIFT	(chan6__0__SHIFT)
#define chan6_0_INTR	((uint16)((uint16)0x0003u << (chan6__0__SHIFT*2u)))

#define chan6_INTR_ALL	 ((uint16)(chan6_0_INTR))


#endif /* End Pins chan6_ALIASES_H */


/* [] END OF FILE */
