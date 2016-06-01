/*******************************************************************************
* File Name: nrst.h  
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

#if !defined(CY_PINS_nrst_ALIASES_H) /* Pins nrst_ALIASES_H */
#define CY_PINS_nrst_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define nrst_0			(nrst__0__PC)
#define nrst_0_PS		(nrst__0__PS)
#define nrst_0_PC		(nrst__0__PC)
#define nrst_0_DR		(nrst__0__DR)
#define nrst_0_SHIFT	(nrst__0__SHIFT)
#define nrst_0_INTR	((uint16)((uint16)0x0003u << (nrst__0__SHIFT*2u)))

#define nrst_INTR_ALL	 ((uint16)(nrst_0_INTR))


#endif /* End Pins nrst_ALIASES_H */


/* [] END OF FILE */
