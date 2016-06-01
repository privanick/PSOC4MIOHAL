/*******************************************************************************
* File Name: pwr_en.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_pwr_en_H) /* CY_CONTROL_REG_pwr_en_H */
#define CY_CONTROL_REG_pwr_en_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} pwr_en_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    pwr_en_Write(uint8 control) ;
uint8   pwr_en_Read(void) ;

void pwr_en_SaveConfig(void) ;
void pwr_en_RestoreConfig(void) ;
void pwr_en_Sleep(void) ; 
void pwr_en_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define pwr_en_Control        (* (reg8 *) pwr_en_Sync_ctrl_reg__CONTROL_REG )
#define pwr_en_Control_PTR    (  (reg8 *) pwr_en_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_pwr_en_H */


/* [] END OF FILE */
