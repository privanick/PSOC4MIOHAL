/*******************************************************************************
* File Name: dio2.h  
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

#if !defined(CY_PINS_dio2_ALIASES_H) /* Pins dio2_ALIASES_H */
#define CY_PINS_dio2_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define dio2_0			(dio2__0__PC)
#define dio2_0_PS		(dio2__0__PS)
#define dio2_0_PC		(dio2__0__PC)
#define dio2_0_DR		(dio2__0__DR)
#define dio2_0_SHIFT	(dio2__0__SHIFT)
#define dio2_0_INTR	((uint16)((uint16)0x0003u << (dio2__0__SHIFT*2u)))

#define dio2_INTR_ALL	 ((uint16)(dio2_0_INTR))


#endif /* End Pins dio2_ALIASES_H */


/* [] END OF FILE */
