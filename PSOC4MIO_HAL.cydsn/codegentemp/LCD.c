/*******************************************************************************
* File Name: LCD.c
* Version 1.50
*
* Description:
*  This file provides the source code to the API for the Software Transmit UART.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_PVT.h"

#if(LCD_PIN_STATIC_MODE == 1u)
    uint32 LCD_pinNumber = LCD_PIN_NUMBER;
    uint32 LCD_pinPortNumber = LCD_PIN_PORT_NUMBER;
    #if(CY_PSOC3)
        uint32 pdata LCD_pinDrAdress = LCD_PIN_DR;
    #else
        uint32 LCD_pinDrAdress = LCD_PIN_DR;
    #endif /* (CY_PSOC3) */
#else
    uint32 LCD_pinNumber;
    uint32 LCD_pinPortNumber;
    #if(CY_PSOC3)
        uint32 pdata LCD_pinDrAdress;
    #else
        uint32 LCD_pinDrAdress;
    #endif /* (CY_PSOC3) */
#endif /* (LCD_PIN_STATIC_MODE == 1u) */


#if(LCD_PIN_STATIC_MODE == 1u)
    /*******************************************************************************
    * Function Name: LCD_Start
    ********************************************************************************
    *
    * Summary:
    *  Empty function. Included for consistency with other
    *  components. This API is not available when PinAssignmentMethod
    *  is set to Dynamic.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void LCD_Start(void) 
    {

    }
#else
    /*******************************************************************************
    * Function Name: LCD_StartEx
    ********************************************************************************
    *
    * Summary:
    *  Configures the SW Tx UART to use the pin specified
    *  by the parameters. This API is only available when
    *  PinAssignmentMethod is set to Dynamic.
    *
    * Parameters:
    *  port:  Port number for dynamic pin assignment
    *  pin:   Pin number for dynamic pin assignment
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void LCD_StartEx(uint8 port, uint8 pin) 
    {
        uint32 portConfigAddr;

        #if (CY_PSOC4)
            uint32 portDataRegAddr;
        #endif /* (CY_PSOC4) */

        if ((pin <= LCD_MAX_PIN_NUMBER) && (port <= LCD_MAX_PORT_NUMBER))
        {
            #if (!CY_PSOC4)
                portConfigAddr = LCD_PORT_CNF_BASE;
                portConfigAddr += ((uint32)port * (LCD_MAX_PIN_NUMBER + 1u)) + pin;
                CyPins_SetPinDriveMode(portConfigAddr, CY_PINS_DM_STRONG);
                CyPins_SetPin(portConfigAddr);
                LCD_pinDrAdress = portConfigAddr;
            #else
                portConfigAddr = LCD_PORT_CNF_BASE + (LCD_PORT_CNF_SIZE * port) +
                                                                                LCD_PORT_CNF_MODE_OFFSET;
                CY_SYS_PINS_SET_DRIVE_MODE(portConfigAddr, pin, CY_SYS_PINS_DM_STRONG);
                portDataRegAddr = LCD_PORT_CNF_BASE + (LCD_PORT_CNF_SIZE * port) +
                                                                                LCD_PORT_CNF_DR_OFFSET;
                CY_SYS_PINS_SET_PIN(portDataRegAddr, pin);
                LCD_pinDrAdress = portDataRegAddr;
            #endif /* (!CY_PSOC4) */
            LCD_pinNumber = pin;
            LCD_pinPortNumber = port;
        }
    }
#endif /* (LCD_PIN_STATIC_MODE == 1u) */


/*******************************************************************************
* Function Name: LCD_Stop
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LCD_Stop(void) 
{

}


/*******************************************************************************
* Function Name: LCD_PutString
********************************************************************************
*
* Summary:
*  Sends a NULL terminated string via the Tx pin.
*
* Parameters:
*  string: Pointer to the null terminated string to send
*
* Return:
*  None
*
*******************************************************************************/
void LCD_PutString(const char8 string[]) 
{
    uint8 stringIndex = 1u;
    char8 current = *string;

    /* Until null is reached, print next character */
    while((char8) '\0' != current)
    {
        LCD_PutChar((uint8)current);
        current = string[stringIndex];
        stringIndex++;
    }
}


/*******************************************************************************
* Function Name: LCD_PutArray
********************************************************************************
*
* Summary:
*  Sends byteCount bytes from a memory array via the Tx pin.
*
* Parameters:
*  data: Pointer to the memory array
*  byteCount: Number of bytes to be transmitted
*
* Return:
*  None
*
*******************************************************************************/
void LCD_PutArray(const uint8 array[], uint32 byteCount) 
{
    uint32 arrayIndex;

    for (arrayIndex = 0u; arrayIndex < byteCount; arrayIndex++)
    {
        LCD_PutChar(array[arrayIndex]);
    }
}


/*******************************************************************************
* Function Name: LCD_PutHexByte
********************************************************************************
*
* Summary:
*  Sends a byte in Hex representation (two characters, uppercase for A-F) via
*  the Tx pin.
*
* Parameters:
*  TxHexByte: The byte to be converted to ASCII characters and
*             sent via the Tx pin.
*
* Return:
*  None
*
*******************************************************************************/
void LCD_PutHexByte(uint8 txHexByte) 
{
    static char8 const CYCODE LCD_hex[] = "0123456789ABCDEF";

    LCD_PutChar((uint8) LCD_hex[txHexByte >> LCD_BYTE_UPPER_NIBBLE_SHIFT]);
    LCD_PutChar((uint8) LCD_hex[txHexByte & LCD_BYTE_LOWER_NIBBLE_MASK]);
}


/*******************************************************************************
* Function Name: LCD_PutHexInt
********************************************************************************
*
* Summary:
*  Sends a 16-bit unsigned integer in Hex representation (four characters,
*  uppercase for A-F) via the Tx pin.
*
* Parameters:
*  TxHexInt: The uint16 to be converted to ASCII characters and sent via
*            the Tx pin.
*
* Return:
*  None
*
*******************************************************************************/
void LCD_PutHexInt(uint16 txHexInt) 
{
    LCD_PutHexByte((uint8)(txHexInt >> LCD_U16_UPPER_BYTE_SHIFT));
    LCD_PutHexByte((uint8)(txHexInt & LCD_U16_LOWER_BYTE_MASK));
}


/*******************************************************************************
* Function Name: LCD_PutCRLF
********************************************************************************
*
* Summary:
*  Sends a carriage return (0x0D) and a line feed (0x0A) via the Tx pin.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LCD_PutCRLF(void) 
{
    LCD_PutChar(0x0Du);
    LCD_PutChar(0x0Au);
}


/* [] END OF FILE */
