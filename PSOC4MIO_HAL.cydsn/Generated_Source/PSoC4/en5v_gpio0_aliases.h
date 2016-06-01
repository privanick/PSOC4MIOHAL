/*******************************************************************************
* File Name: en5v_gpio0.h  
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

#if !defined(CY_PINS_en5v_gpio0_ALIASES_H) /* Pins en5v_gpio0_ALIASES_H */
#define CY_PINS_en5v_gpio0_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define en5v_gpio0_0			(en5v_gpio0__0__PC)
#define en5v_gpio0_0_PS		(en5v_gpio0__0__PS)
#define en5v_gpio0_0_PC		(en5v_gpio0__0__PC)
#define en5v_gpio0_0_DR		(en5v_gpio0__0__DR)
#define en5v_gpio0_0_SHIFT	(en5v_gpio0__0__SHIFT)
#define en5v_gpio0_0_INTR	((uint16)((uint16)0x0003u << (en5v_gpio0__0__SHIFT*2u)))

#define en5v_gpio0_INTR_ALL	 ((uint16)(en5v_gpio0_0_INTR))


#endif /* End Pins en5v_gpio0_ALIASES_H */


/* [] END OF FILE */
