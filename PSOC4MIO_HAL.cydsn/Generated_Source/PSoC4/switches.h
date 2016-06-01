/*******************************************************************************
* File Name: switches.h  
* Version 1.90
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_switches_H) /* CY_STATUS_REG_switches_H */
#define CY_STATUS_REG_switches_H

#include "cytypes.h"
#include "CyLib.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} switches_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 switches_Read(void) ;
void switches_InterruptEnable(void) ;
void switches_InterruptDisable(void) ;
void switches_WriteMask(uint8 mask) ;
uint8 switches_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define switches_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define switches_INPUTS              4


/***************************************
*             Registers
***************************************/

/* Status Register */
#define switches_Status             (* (reg8 *) switches_sts_sts_reg__STATUS_REG )
#define switches_Status_PTR         (  (reg8 *) switches_sts_sts_reg__STATUS_REG )
#define switches_Status_Mask        (* (reg8 *) switches_sts_sts_reg__MASK_REG )
#define switches_Status_Aux_Ctrl    (* (reg8 *) switches_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_switches_H */


/* [] END OF FILE */
