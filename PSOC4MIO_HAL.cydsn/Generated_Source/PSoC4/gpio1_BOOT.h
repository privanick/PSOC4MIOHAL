/***************************************************************************//**
* \file gpio1_BOOT.h
* \version 3.20
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_gpio1_H)
#define CY_SCB_BOOT_gpio1_H

#include "gpio1_PVT.h"

#if (gpio1_SCB_MODE_I2C_INC)
    #include "gpio1_I2C.h"
#endif /* (gpio1_SCB_MODE_I2C_INC) */

#if (gpio1_SCB_MODE_EZI2C_INC)
    #include "gpio1_EZI2C.h"
#endif /* (gpio1_SCB_MODE_EZI2C_INC) */

#if (gpio1_SCB_MODE_SPI_INC || gpio1_SCB_MODE_UART_INC)
    #include "gpio1_SPI_UART.h"
#endif /* (gpio1_SCB_MODE_SPI_INC || gpio1_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define gpio1_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_gpio1) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (gpio1_SCB_MODE_I2C_INC)
    #define gpio1_I2C_BTLDR_COMM_ENABLED     (gpio1_BTLDR_COMM_ENABLED && \
                                                            (gpio1_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             gpio1_I2C_SLAVE_CONST))
#else
     #define gpio1_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (gpio1_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (gpio1_SCB_MODE_EZI2C_INC)
    #define gpio1_EZI2C_BTLDR_COMM_ENABLED   (gpio1_BTLDR_COMM_ENABLED && \
                                                         gpio1_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define gpio1_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (gpio1_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (gpio1_SCB_MODE_SPI_INC)
    #define gpio1_SPI_BTLDR_COMM_ENABLED     (gpio1_BTLDR_COMM_ENABLED && \
                                                            (gpio1_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             gpio1_SPI_SLAVE_CONST))
#else
        #define gpio1_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (gpio1_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (gpio1_SCB_MODE_UART_INC)
       #define gpio1_UART_BTLDR_COMM_ENABLED    (gpio1_BTLDR_COMM_ENABLED && \
                                                            (gpio1_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (gpio1_UART_RX_DIRECTION && \
                                                              gpio1_UART_TX_DIRECTION)))
#else
     #define gpio1_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (gpio1_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define gpio1_BTLDR_COMM_MODE_ENABLED    (gpio1_I2C_BTLDR_COMM_ENABLED   || \
                                                     gpio1_SPI_BTLDR_COMM_ENABLED   || \
                                                     gpio1_EZI2C_BTLDR_COMM_ENABLED || \
                                                     gpio1_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (gpio1_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void gpio1_I2CCyBtldrCommStart(void);
    void gpio1_I2CCyBtldrCommStop (void);
    void gpio1_I2CCyBtldrCommReset(void);
    cystatus gpio1_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus gpio1_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (gpio1_SCB_MODE_I2C_CONST_CFG)
        #define gpio1_CyBtldrCommStart   gpio1_I2CCyBtldrCommStart
        #define gpio1_CyBtldrCommStop    gpio1_I2CCyBtldrCommStop
        #define gpio1_CyBtldrCommReset   gpio1_I2CCyBtldrCommReset
        #define gpio1_CyBtldrCommRead    gpio1_I2CCyBtldrCommRead
        #define gpio1_CyBtldrCommWrite   gpio1_I2CCyBtldrCommWrite
    #endif /* (gpio1_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (gpio1_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (gpio1_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void gpio1_EzI2CCyBtldrCommStart(void);
    void gpio1_EzI2CCyBtldrCommStop (void);
    void gpio1_EzI2CCyBtldrCommReset(void);
    cystatus gpio1_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus gpio1_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (gpio1_SCB_MODE_EZI2C_CONST_CFG)
        #define gpio1_CyBtldrCommStart   gpio1_EzI2CCyBtldrCommStart
        #define gpio1_CyBtldrCommStop    gpio1_EzI2CCyBtldrCommStop
        #define gpio1_CyBtldrCommReset   gpio1_EzI2CCyBtldrCommReset
        #define gpio1_CyBtldrCommRead    gpio1_EzI2CCyBtldrCommRead
        #define gpio1_CyBtldrCommWrite   gpio1_EzI2CCyBtldrCommWrite
    #endif /* (gpio1_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (gpio1_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (gpio1_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void gpio1_SpiCyBtldrCommStart(void);
    void gpio1_SpiCyBtldrCommStop (void);
    void gpio1_SpiCyBtldrCommReset(void);
    cystatus gpio1_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus gpio1_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (gpio1_SCB_MODE_SPI_CONST_CFG)
        #define gpio1_CyBtldrCommStart   gpio1_SpiCyBtldrCommStart
        #define gpio1_CyBtldrCommStop    gpio1_SpiCyBtldrCommStop
        #define gpio1_CyBtldrCommReset   gpio1_SpiCyBtldrCommReset
        #define gpio1_CyBtldrCommRead    gpio1_SpiCyBtldrCommRead
        #define gpio1_CyBtldrCommWrite   gpio1_SpiCyBtldrCommWrite
    #endif /* (gpio1_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (gpio1_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (gpio1_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void gpio1_UartCyBtldrCommStart(void);
    void gpio1_UartCyBtldrCommStop (void);
    void gpio1_UartCyBtldrCommReset(void);
    cystatus gpio1_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus gpio1_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (gpio1_SCB_MODE_UART_CONST_CFG)
        #define gpio1_CyBtldrCommStart   gpio1_UartCyBtldrCommStart
        #define gpio1_CyBtldrCommStop    gpio1_UartCyBtldrCommStop
        #define gpio1_CyBtldrCommReset   gpio1_UartCyBtldrCommReset
        #define gpio1_CyBtldrCommRead    gpio1_UartCyBtldrCommRead
        #define gpio1_CyBtldrCommWrite   gpio1_UartCyBtldrCommWrite
    #endif /* (gpio1_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (gpio1_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (gpio1_BTLDR_COMM_ENABLED)
    #if (gpio1_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void gpio1_CyBtldrCommStart(void);
        void gpio1_CyBtldrCommStop (void);
        void gpio1_CyBtldrCommReset(void);
        cystatus gpio1_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus gpio1_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (gpio1_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_gpio1)
        #define CyBtldrCommStart    gpio1_CyBtldrCommStart
        #define CyBtldrCommStop     gpio1_CyBtldrCommStop
        #define CyBtldrCommReset    gpio1_CyBtldrCommReset
        #define CyBtldrCommWrite    gpio1_CyBtldrCommWrite
        #define CyBtldrCommRead     gpio1_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_gpio1) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (gpio1_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define gpio1_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define gpio1_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define gpio1_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define gpio1_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef gpio1_SPI_BYTE_TO_BYTE
    #define gpio1_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef gpio1_UART_BYTE_TO_BYTE
    #define gpio1_UART_BYTE_TO_BYTE  (2500u)
#endif /* gpio1_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_gpio1_H) */


/* [] END OF FILE */
