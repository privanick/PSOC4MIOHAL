/*******************************************************************************
* File Name: console_BOOT.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_console_H)
#define CY_SCB_BOOT_console_H

#include "console_PVT.h"

#if (console_SCB_MODE_I2C_INC)
    #include "console_I2C.h"
#endif /* (console_SCB_MODE_I2C_INC) */

#if (console_SCB_MODE_EZI2C_INC)
    #include "console_EZI2C.h"
#endif /* (console_SCB_MODE_EZI2C_INC) */

#if (console_SCB_MODE_SPI_INC || console_SCB_MODE_UART_INC)
    #include "console_SPI_UART.h"
#endif /* (console_SCB_MODE_SPI_INC || console_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define console_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_console) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (console_SCB_MODE_I2C_INC)
    #define console_I2C_BTLDR_COMM_ENABLED     (console_BTLDR_COMM_ENABLED && \
                                                            (console_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             console_I2C_SLAVE_CONST))
#else
     #define console_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (console_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (console_SCB_MODE_EZI2C_INC)
    #define console_EZI2C_BTLDR_COMM_ENABLED   (console_BTLDR_COMM_ENABLED && \
                                                         console_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define console_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (console_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (console_SCB_MODE_SPI_INC)
    #define console_SPI_BTLDR_COMM_ENABLED     (console_BTLDR_COMM_ENABLED && \
                                                            (console_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             console_SPI_SLAVE_CONST))
#else
        #define console_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (console_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (console_SCB_MODE_UART_INC)
       #define console_UART_BTLDR_COMM_ENABLED    (console_BTLDR_COMM_ENABLED && \
                                                            (console_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (console_UART_RX_DIRECTION && \
                                                              console_UART_TX_DIRECTION)))
#else
     #define console_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (console_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define console_BTLDR_COMM_MODE_ENABLED    (console_I2C_BTLDR_COMM_ENABLED   || \
                                                     console_SPI_BTLDR_COMM_ENABLED   || \
                                                     console_EZI2C_BTLDR_COMM_ENABLED || \
                                                     console_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (console_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void console_I2CCyBtldrCommStart(void);
    void console_I2CCyBtldrCommStop (void);
    void console_I2CCyBtldrCommReset(void);
    cystatus console_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus console_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (console_SCB_MODE_I2C_CONST_CFG)
        #define console_CyBtldrCommStart   console_I2CCyBtldrCommStart
        #define console_CyBtldrCommStop    console_I2CCyBtldrCommStop
        #define console_CyBtldrCommReset   console_I2CCyBtldrCommReset
        #define console_CyBtldrCommRead    console_I2CCyBtldrCommRead
        #define console_CyBtldrCommWrite   console_I2CCyBtldrCommWrite
    #endif /* (console_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (console_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (console_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void console_EzI2CCyBtldrCommStart(void);
    void console_EzI2CCyBtldrCommStop (void);
    void console_EzI2CCyBtldrCommReset(void);
    cystatus console_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus console_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (console_SCB_MODE_EZI2C_CONST_CFG)
        #define console_CyBtldrCommStart   console_EzI2CCyBtldrCommStart
        #define console_CyBtldrCommStop    console_EzI2CCyBtldrCommStop
        #define console_CyBtldrCommReset   console_EzI2CCyBtldrCommReset
        #define console_CyBtldrCommRead    console_EzI2CCyBtldrCommRead
        #define console_CyBtldrCommWrite   console_EzI2CCyBtldrCommWrite
    #endif /* (console_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (console_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (console_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void console_SpiCyBtldrCommStart(void);
    void console_SpiCyBtldrCommStop (void);
    void console_SpiCyBtldrCommReset(void);
    cystatus console_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus console_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (console_SCB_MODE_SPI_CONST_CFG)
        #define console_CyBtldrCommStart   console_SpiCyBtldrCommStart
        #define console_CyBtldrCommStop    console_SpiCyBtldrCommStop
        #define console_CyBtldrCommReset   console_SpiCyBtldrCommReset
        #define console_CyBtldrCommRead    console_SpiCyBtldrCommRead
        #define console_CyBtldrCommWrite   console_SpiCyBtldrCommWrite
    #endif /* (console_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (console_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (console_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void console_UartCyBtldrCommStart(void);
    void console_UartCyBtldrCommStop (void);
    void console_UartCyBtldrCommReset(void);
    cystatus console_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus console_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (console_SCB_MODE_UART_CONST_CFG)
        #define console_CyBtldrCommStart   console_UartCyBtldrCommStart
        #define console_CyBtldrCommStop    console_UartCyBtldrCommStop
        #define console_CyBtldrCommReset   console_UartCyBtldrCommReset
        #define console_CyBtldrCommRead    console_UartCyBtldrCommRead
        #define console_CyBtldrCommWrite   console_UartCyBtldrCommWrite
    #endif /* (console_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (console_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (console_BTLDR_COMM_ENABLED)
    #if (console_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void console_CyBtldrCommStart(void);
        void console_CyBtldrCommStop (void);
        void console_CyBtldrCommReset(void);
        cystatus console_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus console_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_console)
        #define CyBtldrCommStart    console_CyBtldrCommStart
        #define CyBtldrCommStop     console_CyBtldrCommStop
        #define CyBtldrCommReset    console_CyBtldrCommReset
        #define CyBtldrCommWrite    console_CyBtldrCommWrite
        #define CyBtldrCommRead     console_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_console) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (console_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define console_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define console_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define console_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define console_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef console_SPI_BYTE_TO_BYTE
    #define console_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef console_UART_BYTE_TO_BYTE
    #define console_UART_BYTE_TO_BYTE  (1040u)
#endif /* console_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_console_H) */


/* [] END OF FILE */
