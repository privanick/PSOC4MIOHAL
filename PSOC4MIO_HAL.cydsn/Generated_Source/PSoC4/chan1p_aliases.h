/*******************************************************************************
* File Name: chan1p.h  
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

#if !defined(CY_PINS_chan1p_ALIASES_H) /* Pins chan1p_ALIASES_H */
#define CY_PINS_chan1p_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define chan1p_0			(chan1p__0__PC)
#define chan1p_0_PS		(chan1p__0__PS)
#define chan1p_0_PC		(chan1p__0__PC)
#define chan1p_0_DR		(chan1p__0__DR)
#define chan1p_0_SHIFT	(chan1p__0__SHIFT)
#define chan1p_0_INTR	((uint16)((uint16)0x0003u << (chan1p__0__SHIFT*2u)))

#define chan1p_INTR_ALL	 ((uint16)(chan1p_0_INTR))


#endif /* End Pins chan1p_ALIASES_H */


/* [] END OF FILE */
