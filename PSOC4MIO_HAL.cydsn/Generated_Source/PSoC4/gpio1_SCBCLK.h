/*******************************************************************************
* File Name: gpio1_SCBCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_gpio1_SCBCLK_H)
#define CY_CLOCK_gpio1_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void gpio1_SCBCLK_StartEx(uint32 alignClkDiv);
#define gpio1_SCBCLK_Start() \
    gpio1_SCBCLK_StartEx(gpio1_SCBCLK__PA_DIV_ID)

#else

void gpio1_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void gpio1_SCBCLK_Stop(void);

void gpio1_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 gpio1_SCBCLK_GetDividerRegister(void);
uint8  gpio1_SCBCLK_GetFractionalDividerRegister(void);

#define gpio1_SCBCLK_Enable()                         gpio1_SCBCLK_Start()
#define gpio1_SCBCLK_Disable()                        gpio1_SCBCLK_Stop()
#define gpio1_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    gpio1_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define gpio1_SCBCLK_SetDivider(clkDivider)           gpio1_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define gpio1_SCBCLK_SetDividerValue(clkDivider)      gpio1_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define gpio1_SCBCLK_DIV_ID     gpio1_SCBCLK__DIV_ID

#define gpio1_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define gpio1_SCBCLK_CTRL_REG   (*(reg32 *)gpio1_SCBCLK__CTRL_REGISTER)
#define gpio1_SCBCLK_DIV_REG    (*(reg32 *)gpio1_SCBCLK__DIV_REGISTER)

#define gpio1_SCBCLK_CMD_DIV_SHIFT          (0u)
#define gpio1_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define gpio1_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define gpio1_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define gpio1_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << gpio1_SCBCLK_CMD_DISABLE_SHIFT))
#define gpio1_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << gpio1_SCBCLK_CMD_ENABLE_SHIFT))

#define gpio1_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define gpio1_SCBCLK_DIV_FRAC_SHIFT (3u)
#define gpio1_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define gpio1_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define gpio1_SCBCLK_DIV_REG        (*(reg32 *)gpio1_SCBCLK__REGISTER)
#define gpio1_SCBCLK_ENABLE_REG     gpio1_SCBCLK_DIV_REG
#define gpio1_SCBCLK_DIV_FRAC_MASK  gpio1_SCBCLK__FRAC_MASK
#define gpio1_SCBCLK_DIV_FRAC_SHIFT (16u)
#define gpio1_SCBCLK_DIV_INT_MASK   gpio1_SCBCLK__DIVIDER_MASK
#define gpio1_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_gpio1_SCBCLK_H) */

/* [] END OF FILE */
