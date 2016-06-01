/*******************************************************************************
* File Name: LCD.h
* Version 1.50
*
* Description:
*  This file provides constants and parameter values for the Software Transmit
*  UART Component.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_SW_TX_UART_LCD_H
#define CY_SW_TX_UART_LCD_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"

#define LCD_BAUD_RATE                      (115200u)
#define LCD_PIN_STATIC_MODE                (1u)


/***************************************
*        Function Prototypes
***************************************/
#if(LCD_PIN_STATIC_MODE == 1u)
    void LCD_Start(void) ;
#else
    void LCD_StartEx(uint8 port, uint8 pin) ;
#endif /* (LCD_PIN_STATIC_MODE == 1u) */

void LCD_Stop(void) ;
void LCD_PutChar(uint8 txDataByte) ;
void LCD_PutString(const char8 string[]) ;
void LCD_PutArray(const uint8 array[], uint32 byteCount) ;
void LCD_PutHexByte(uint8 txHexByte) ;
void LCD_PutHexInt(uint16 txHexInt) ;
void LCD_PutCRLF(void) ;

#endif /* CY_SW_TX_UART_LCD_H */


/* [] END OF FILE */
