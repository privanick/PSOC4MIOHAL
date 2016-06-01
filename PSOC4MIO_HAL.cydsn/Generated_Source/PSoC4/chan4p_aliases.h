/*******************************************************************************
* File Name: chan4p.h  
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

#if !defined(CY_PINS_chan4p_ALIASES_H) /* Pins chan4p_ALIASES_H */
#define CY_PINS_chan4p_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define chan4p_0			(chan4p__0__PC)
#define chan4p_0_PS		(chan4p__0__PS)
#define chan4p_0_PC		(chan4p__0__PC)
#define chan4p_0_DR		(chan4p__0__DR)
#define chan4p_0_SHIFT	(chan4p__0__SHIFT)
#define chan4p_0_INTR	((uint16)((uint16)0x0003u << (chan4p__0__SHIFT*2u)))

#define chan4p_INTR_ALL	 ((uint16)(chan4p_0_INTR))


#endif /* End Pins chan4p_ALIASES_H */


/* [] END OF FILE */
