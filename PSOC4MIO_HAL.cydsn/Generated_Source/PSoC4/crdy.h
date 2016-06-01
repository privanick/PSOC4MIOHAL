/*******************************************************************************
* File Name: crdy.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_crdy_H)
#define CY_ISR_crdy_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void crdy_Start(void);
void crdy_StartEx(cyisraddress address);
void crdy_Stop(void);

CY_ISR_PROTO(crdy_Interrupt);

void crdy_SetVector(cyisraddress address);
cyisraddress crdy_GetVector(void);

void crdy_SetPriority(uint8 priority);
uint8 crdy_GetPriority(void);

void crdy_Enable(void);
uint8 crdy_GetState(void);
void crdy_Disable(void);

void crdy_SetPending(void);
void crdy_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the crdy ISR. */
#define crdy_INTC_VECTOR            ((reg32 *) crdy__INTC_VECT)

/* Address of the crdy ISR priority. */
#define crdy_INTC_PRIOR             ((reg32 *) crdy__INTC_PRIOR_REG)

/* Priority of the crdy interrupt. */
#define crdy_INTC_PRIOR_NUMBER      crdy__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable crdy interrupt. */
#define crdy_INTC_SET_EN            ((reg32 *) crdy__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the crdy interrupt. */
#define crdy_INTC_CLR_EN            ((reg32 *) crdy__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the crdy interrupt state to pending. */
#define crdy_INTC_SET_PD            ((reg32 *) crdy__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the crdy interrupt. */
#define crdy_INTC_CLR_PD            ((reg32 *) crdy__INTC_CLR_PD_REG)



#endif /* CY_ISR_crdy_H */


/* [] END OF FILE */
