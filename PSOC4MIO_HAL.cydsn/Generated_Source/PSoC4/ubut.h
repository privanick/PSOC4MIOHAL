/*******************************************************************************
* File Name: ubut.h
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
#if !defined(CY_ISR_ubut_H)
#define CY_ISR_ubut_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ubut_Start(void);
void ubut_StartEx(cyisraddress address);
void ubut_Stop(void);

CY_ISR_PROTO(ubut_Interrupt);

void ubut_SetVector(cyisraddress address);
cyisraddress ubut_GetVector(void);

void ubut_SetPriority(uint8 priority);
uint8 ubut_GetPriority(void);

void ubut_Enable(void);
uint8 ubut_GetState(void);
void ubut_Disable(void);

void ubut_SetPending(void);
void ubut_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ubut ISR. */
#define ubut_INTC_VECTOR            ((reg32 *) ubut__INTC_VECT)

/* Address of the ubut ISR priority. */
#define ubut_INTC_PRIOR             ((reg32 *) ubut__INTC_PRIOR_REG)

/* Priority of the ubut interrupt. */
#define ubut_INTC_PRIOR_NUMBER      ubut__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ubut interrupt. */
#define ubut_INTC_SET_EN            ((reg32 *) ubut__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ubut interrupt. */
#define ubut_INTC_CLR_EN            ((reg32 *) ubut__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ubut interrupt state to pending. */
#define ubut_INTC_SET_PD            ((reg32 *) ubut__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ubut interrupt. */
#define ubut_INTC_CLR_PD            ((reg32 *) ubut__INTC_CLR_PD_REG)



#endif /* CY_ISR_ubut_H */


/* [] END OF FILE */
