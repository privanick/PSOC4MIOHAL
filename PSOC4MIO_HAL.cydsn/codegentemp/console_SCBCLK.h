/*******************************************************************************
* File Name: console_SCBCLK.h
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

#if !defined(CY_CLOCK_console_SCBCLK_H)
#define CY_CLOCK_console_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void console_SCBCLK_StartEx(uint32 alignClkDiv);
#define console_SCBCLK_Start() \
    console_SCBCLK_StartEx(console_SCBCLK__PA_DIV_ID)

#else

void console_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void console_SCBCLK_Stop(void);

void console_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 console_SCBCLK_GetDividerRegister(void);
uint8  console_SCBCLK_GetFractionalDividerRegister(void);

#define console_SCBCLK_Enable()                         console_SCBCLK_Start()
#define console_SCBCLK_Disable()                        console_SCBCLK_Stop()
#define console_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    console_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define console_SCBCLK_SetDivider(clkDivider)           console_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define console_SCBCLK_SetDividerValue(clkDivider)      console_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define console_SCBCLK_DIV_ID     console_SCBCLK__DIV_ID

#define console_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define console_SCBCLK_CTRL_REG   (*(reg32 *)console_SCBCLK__CTRL_REGISTER)
#define console_SCBCLK_DIV_REG    (*(reg32 *)console_SCBCLK__DIV_REGISTER)

#define console_SCBCLK_CMD_DIV_SHIFT          (0u)
#define console_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define console_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define console_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define console_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << console_SCBCLK_CMD_DISABLE_SHIFT))
#define console_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << console_SCBCLK_CMD_ENABLE_SHIFT))

#define console_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define console_SCBCLK_DIV_FRAC_SHIFT (3u)
#define console_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define console_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define console_SCBCLK_DIV_REG        (*(reg32 *)console_SCBCLK__REGISTER)
#define console_SCBCLK_ENABLE_REG     console_SCBCLK_DIV_REG
#define console_SCBCLK_DIV_FRAC_MASK  console_SCBCLK__FRAC_MASK
#define console_SCBCLK_DIV_FRAC_SHIFT (16u)
#define console_SCBCLK_DIV_INT_MASK   console_SCBCLK__DIVIDER_MASK
#define console_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_console_SCBCLK_H) */

/* [] END OF FILE */
