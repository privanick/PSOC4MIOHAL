/*******************************************************************************
* File Name: en33v_gpio1.h  
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

#if !defined(CY_PINS_en33v_gpio1_ALIASES_H) /* Pins en33v_gpio1_ALIASES_H */
#define CY_PINS_en33v_gpio1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define en33v_gpio1_0			(en33v_gpio1__0__PC)
#define en33v_gpio1_0_PS		(en33v_gpio1__0__PS)
#define en33v_gpio1_0_PC		(en33v_gpio1__0__PC)
#define en33v_gpio1_0_DR		(en33v_gpio1__0__DR)
#define en33v_gpio1_0_SHIFT	(en33v_gpio1__0__SHIFT)
#define en33v_gpio1_0_INTR	((uint16)((uint16)0x0003u << (en33v_gpio1__0__SHIFT*2u)))

#define en33v_gpio1_INTR_ALL	 ((uint16)(en33v_gpio1_0_INTR))


#endif /* End Pins en33v_gpio1_ALIASES_H */


/* [] END OF FILE */
