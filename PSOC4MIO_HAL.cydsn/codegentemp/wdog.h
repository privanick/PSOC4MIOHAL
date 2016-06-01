/*******************************************************************************
* File Name: wdog.h
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
#if !defined(CY_ISR_wdog_H)
#define CY_ISR_wdog_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void wdog_Start(void);
void wdog_StartEx(cyisraddress address);
void wdog_Stop(void);

CY_ISR_PROTO(wdog_Interrupt);

void wdog_SetVector(cyisraddress address);
cyisraddress wdog_GetVector(void);

void wdog_SetPriority(uint8 priority);
uint8 wdog_GetPriority(void);

void wdog_Enable(void);
uint8 wdog_GetState(void);
void wdog_Disable(void);

void wdog_SetPending(void);
void wdog_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the wdog ISR. */
#define wdog_INTC_VECTOR            ((reg32 *) wdog__INTC_VECT)

/* Address of the wdog ISR priority. */
#define wdog_INTC_PRIOR             ((reg32 *) wdog__INTC_PRIOR_REG)

/* Priority of the wdog interrupt. */
#define wdog_INTC_PRIOR_NUMBER      wdog__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable wdog interrupt. */
#define wdog_INTC_SET_EN            ((reg32 *) wdog__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the wdog interrupt. */
#define wdog_INTC_CLR_EN            ((reg32 *) wdog__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the wdog interrupt state to pending. */
#define wdog_INTC_SET_PD            ((reg32 *) wdog__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the wdog interrupt. */
#define wdog_INTC_CLR_PD            ((reg32 *) wdog__INTC_CLR_PD_REG)



#endif /* CY_ISR_wdog_H */


/* [] END OF FILE */
