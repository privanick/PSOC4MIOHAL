/*******************************************************************************
* File Name: seconds.h
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
#if !defined(CY_ISR_seconds_H)
#define CY_ISR_seconds_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void seconds_Start(void);
void seconds_StartEx(cyisraddress address);
void seconds_Stop(void);

CY_ISR_PROTO(seconds_Interrupt);

void seconds_SetVector(cyisraddress address);
cyisraddress seconds_GetVector(void);

void seconds_SetPriority(uint8 priority);
uint8 seconds_GetPriority(void);

void seconds_Enable(void);
uint8 seconds_GetState(void);
void seconds_Disable(void);

void seconds_SetPending(void);
void seconds_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the seconds ISR. */
#define seconds_INTC_VECTOR            ((reg32 *) seconds__INTC_VECT)

/* Address of the seconds ISR priority. */
#define seconds_INTC_PRIOR             ((reg32 *) seconds__INTC_PRIOR_REG)

/* Priority of the seconds interrupt. */
#define seconds_INTC_PRIOR_NUMBER      seconds__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable seconds interrupt. */
#define seconds_INTC_SET_EN            ((reg32 *) seconds__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the seconds interrupt. */
#define seconds_INTC_CLR_EN            ((reg32 *) seconds__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the seconds interrupt state to pending. */
#define seconds_INTC_SET_PD            ((reg32 *) seconds__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the seconds interrupt. */
#define seconds_INTC_CLR_PD            ((reg32 *) seconds__INTC_CLR_PD_REG)



#endif /* CY_ISR_seconds_H */


/* [] END OF FILE */
