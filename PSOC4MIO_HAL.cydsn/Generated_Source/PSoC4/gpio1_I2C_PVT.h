/***************************************************************************//**
* \file .h
* \version 3.20
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_I2C_PVT_gpio1_H)
#define CY_SCB_I2C_PVT_gpio1_H

#include "gpio1_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 gpio1_state; /* Current state of I2C FSM */

#if(gpio1_I2C_SLAVE_CONST)
    extern volatile uint8 gpio1_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * gpio1_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  gpio1_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  gpio1_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * gpio1_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  gpio1_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  gpio1_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  gpio1_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   gpio1_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (gpio1_I2C_SLAVE_CONST) */

#if(gpio1_I2C_MASTER_CONST)
    extern volatile uint16 gpio1_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  gpio1_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * gpio1_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  gpio1_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  gpio1_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * gpio1_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  gpio1_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  gpio1_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  gpio1_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (gpio1_I2C_MASTER_CONST) */

#if (gpio1_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    extern uint32 (*gpio1_customAddressHandler) (void);
#endif /* (gpio1_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/***************************************
*     Private Function Prototypes
***************************************/

#if(gpio1_SCB_MODE_I2C_CONST_CFG)
    void gpio1_I2CInit(void);
#endif /* (gpio1_SCB_MODE_I2C_CONST_CFG) */

void gpio1_I2CStop(void);
void gpio1_I2CSaveConfig(void);
void gpio1_I2CRestoreConfig(void);

#if(gpio1_I2C_MASTER_CONST)
    void gpio1_I2CReStartGeneration(void);
#endif /* (gpio1_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_gpio1_H) */


/* [] END OF FILE */
