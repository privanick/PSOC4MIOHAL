/*******************************************************************************
* File Name: sticks.h
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
#if !defined(CY_ISR_sticks_H)
#define CY_ISR_sticks_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void sticks_Start(void);
void sticks_StartEx(cyisraddress address);
void sticks_Stop(void);

CY_ISR_PROTO(sticks_Interrupt);

void sticks_SetVector(cyisraddress address);
cyisraddress sticks_GetVector(void);

void sticks_SetPriority(uint8 priority);
uint8 sticks_GetPriority(void);

void sticks_Enable(void);
uint8 sticks_GetState(void);
void sticks_Disable(void);

void sticks_SetPending(void);
void sticks_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the sticks ISR. */
#define sticks_INTC_VECTOR            ((reg32 *) sticks__INTC_VECT)

/* Address of the sticks ISR priority. */
#define sticks_INTC_PRIOR             ((reg32 *) sticks__INTC_PRIOR_REG)

/* Priority of the sticks interrupt. */
#define sticks_INTC_PRIOR_NUMBER      sticks__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable sticks interrupt. */
#define sticks_INTC_SET_EN            ((reg32 *) sticks__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the sticks interrupt. */
#define sticks_INTC_CLR_EN            ((reg32 *) sticks__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the sticks interrupt state to pending. */
#define sticks_INTC_SET_PD            ((reg32 *) sticks__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the sticks interrupt. */
#define sticks_INTC_CLR_PD            ((reg32 *) sticks__INTC_CLR_PD_REG)



#endif /* CY_ISR_sticks_H */


/* [] END OF FILE */
