/*******************************************************************************
* File Name: gpio1_led.h  
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

#if !defined(CY_PINS_gpio1_led_ALIASES_H) /* Pins gpio1_led_ALIASES_H */
#define CY_PINS_gpio1_led_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define gpio1_led_0			(gpio1_led__0__PC)
#define gpio1_led_0_PS		(gpio1_led__0__PS)
#define gpio1_led_0_PC		(gpio1_led__0__PC)
#define gpio1_led_0_DR		(gpio1_led__0__DR)
#define gpio1_led_0_SHIFT	(gpio1_led__0__SHIFT)
#define gpio1_led_0_INTR	((uint16)((uint16)0x0003u << (gpio1_led__0__SHIFT*2u)))

#define gpio1_led_INTR_ALL	 ((uint16)(gpio1_led_0_INTR))


#endif /* End Pins gpio1_led_ALIASES_H */


/* [] END OF FILE */
