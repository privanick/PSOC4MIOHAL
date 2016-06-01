/*******************************************************************************
* File Name: console_SPI_UART.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_console_H)
#define CY_SCB_SPI_UART_console_H

#include "console.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define console_SPI_MODE                   (0u)
#define console_SPI_SUB_MODE               (0u)
#define console_SPI_CLOCK_MODE             (0u)
#define console_SPI_OVS_FACTOR             (16u)
#define console_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define console_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define console_SPI_RX_DATA_BITS_NUM       (8u)
#define console_SPI_TX_DATA_BITS_NUM       (8u)
#define console_SPI_WAKE_ENABLE            (0u)
#define console_SPI_BITS_ORDER             (1u)
#define console_SPI_TRANSFER_SEPARATION    (1u)
#define console_SPI_NUMBER_OF_SS_LINES     (1u)
#define console_SPI_RX_BUFFER_SIZE         (8u)
#define console_SPI_TX_BUFFER_SIZE         (8u)

#define console_SPI_INTERRUPT_MODE         (0u)

#define console_SPI_INTR_RX_MASK           (0u)
#define console_SPI_INTR_TX_MASK           (0u)

#define console_SPI_RX_TRIGGER_LEVEL       (7u)
#define console_SPI_TX_TRIGGER_LEVEL       (0u)

#define console_SPI_BYTE_MODE_ENABLE       (0u)
#define console_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define console_SPI_SS0_POLARITY           (0u)
#define console_SPI_SS1_POLARITY           (0u)
#define console_SPI_SS2_POLARITY           (0u)
#define console_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define console_UART_SUB_MODE              (0u)
#define console_UART_DIRECTION             (3u)
#define console_UART_DATA_BITS_NUM         (8u)
#define console_UART_PARITY_TYPE           (2u)
#define console_UART_STOP_BITS_NUM         (2u)
#define console_UART_OVS_FACTOR            (12u)
#define console_UART_IRDA_LOW_POWER        (0u)
#define console_UART_MEDIAN_FILTER_ENABLE  (0u)
#define console_UART_RETRY_ON_NACK         (0u)
#define console_UART_IRDA_POLARITY         (0u)
#define console_UART_DROP_ON_FRAME_ERR     (0u)
#define console_UART_DROP_ON_PARITY_ERR    (0u)
#define console_UART_WAKE_ENABLE           (0u)
#define console_UART_RX_BUFFER_SIZE        (8u)
#define console_UART_TX_BUFFER_SIZE        (8u)
#define console_UART_MP_MODE_ENABLE        (0u)
#define console_UART_MP_ACCEPT_ADDRESS     (0u)
#define console_UART_MP_RX_ADDRESS         (2u)
#define console_UART_MP_RX_ADDRESS_MASK    (255u)

#define console_UART_INTERRUPT_MODE        (2u)

#define console_UART_INTR_RX_MASK          (4u)
#define console_UART_INTR_TX_MASK          (0u)

#define console_UART_RX_TRIGGER_LEVEL      (7u)
#define console_UART_TX_TRIGGER_LEVEL      (0u)

#define console_UART_BYTE_MODE_ENABLE      (0u)
#define console_UART_CTS_ENABLE            (0u)
#define console_UART_CTS_POLARITY          (0u)
#define console_UART_RTS_ENABLE            (0u)
#define console_UART_RTS_POLARITY          (0u)
#define console_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define console_SPI_SLAVE  (0u)
#define console_SPI_MASTER (1u)

/* UART direction enum */
#define console_UART_RX    (1u)
#define console_UART_TX    (2u)
#define console_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(console_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define console_SPI_SLAVE_CONST        (1u)
    #define console_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define console_RX_DIRECTION           (1u)
    #define console_TX_DIRECTION           (1u)
    #define console_UART_RX_DIRECTION      (1u)
    #define console_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define console_INTERNAL_RX_SW_BUFFER   (0u)
    #define console_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define console_INTERNAL_RX_BUFFER_SIZE    (console_rxBufferSize + 1u)
    #define console_RX_BUFFER_SIZE             (console_rxBufferSize)
    #define console_TX_BUFFER_SIZE             (console_txBufferSize)

    /* Return true if buffer is provided */
    #define console_CHECK_RX_SW_BUFFER (NULL != console_rxBuffer)
    #define console_CHECK_TX_SW_BUFFER (NULL != console_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define console_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define console_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define console_SPI_WAKE_ENABLE_CONST  (1u)
    #define console_CHECK_SPI_WAKE_ENABLE  (0u != console_scbEnableWake)
    #define console_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (console_CY_SCBIP_V0 || console_CY_SCBIP_V1)
        #define console_SPI_UART_FIFO_SIZE             (console_FIFO_SIZE)
        #define console_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define console_SPI_UART_FIFO_SIZE (console_GET_FIFO_SIZE(console_CTRL_REG & \
                                                                                    console_CTRL_BYTE_MODE))

        #define console_CHECK_UART_RTS_CONTROL_FLOW \
                    ((console_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != console_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(console_UART_FLOW_CTRL_REG)))
    #endif /* (console_CY_SCBIP_V0 || console_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (console_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define console_SPI_RX_DIRECTION (1u)
        #define console_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (console_CY_SCBIP_V0 || console_CY_SCBIP_V1)
            #define console_SPI_UART_FIFO_SIZE    (console_FIFO_SIZE)
        #else
            #define console_SPI_UART_FIFO_SIZE \
                                           console_GET_FIFO_SIZE(console_SPI_BYTE_MODE_ENABLE)

        #endif /* (console_CY_SCBIP_V0 || console_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define console_INTERNAL_SPI_RX_SW_BUFFER  (console_SPI_RX_BUFFER_SIZE > \
                                                                console_SPI_UART_FIFO_SIZE)
        #define console_INTERNAL_SPI_TX_SW_BUFFER  (console_SPI_TX_BUFFER_SIZE > \
                                                                console_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define console_INTERNAL_RX_SW_BUFFER  (console_INTERNAL_SPI_RX_SW_BUFFER)
        #define console_INTERNAL_TX_SW_BUFFER  (console_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define console_INTERNAL_RX_BUFFER_SIZE    (console_SPI_RX_BUFFER_SIZE + 1u)
        #define console_RX_BUFFER_SIZE             (console_SPI_RX_BUFFER_SIZE)
        #define console_TX_BUFFER_SIZE             (console_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define console_SPI_WAKE_ENABLE_CONST  (0u != console_SPI_WAKE_ENABLE)
        #define console_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define console_UART_RX_DIRECTION (0u != (console_UART_DIRECTION & console_UART_RX))
        #define console_UART_TX_DIRECTION (0u != (console_UART_DIRECTION & console_UART_TX))

        /* Get FIFO size */
        #if (console_CY_SCBIP_V0 || console_CY_SCBIP_V1)
            #define console_SPI_UART_FIFO_SIZE    (console_FIFO_SIZE)
        #else
            #define console_SPI_UART_FIFO_SIZE \
                                           console_GET_FIFO_SIZE(console_UART_BYTE_MODE_ENABLE)
        #endif /* (console_CY_SCBIP_V0 || console_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define console_INTERNAL_UART_RX_SW_BUFFER  (console_UART_RX_BUFFER_SIZE > \
                                                                console_SPI_UART_FIFO_SIZE)
        #define console_INTERNAL_UART_TX_SW_BUFFER  (console_UART_TX_BUFFER_SIZE > \
                                                                    console_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define console_INTERNAL_RX_SW_BUFFER  (console_INTERNAL_UART_RX_SW_BUFFER)
        #define console_INTERNAL_TX_SW_BUFFER  (console_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define console_INTERNAL_RX_BUFFER_SIZE    (console_UART_RX_BUFFER_SIZE + 1u)
        #define console_RX_BUFFER_SIZE             (console_UART_RX_BUFFER_SIZE)
        #define console_TX_BUFFER_SIZE             (console_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define console_SPI_WAKE_ENABLE_CONST  (0u)
        #define console_UART_WAKE_ENABLE_CONST (0u != console_UART_WAKE_ENABLE)

    #endif /* (console_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define console_SPI_SLAVE_CONST    (console_SPI_MODE == console_SPI_SLAVE)
    #define console_SPI_MASTER_CONST   (console_SPI_MODE == console_SPI_MASTER)

    /* Direction */
    #define console_RX_DIRECTION ((console_SCB_MODE_SPI_CONST_CFG) ? \
                                            (console_SPI_RX_DIRECTION) : (console_UART_RX_DIRECTION))

    #define console_TX_DIRECTION ((console_SCB_MODE_SPI_CONST_CFG) ? \
                                            (console_SPI_TX_DIRECTION) : (console_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define console_CHECK_RX_SW_BUFFER (console_INTERNAL_RX_SW_BUFFER)
    #define console_CHECK_TX_SW_BUFFER (console_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define console_INTERNAL_RX_SW_BUFFER_CONST    (console_INTERNAL_RX_SW_BUFFER)
    #define console_INTERNAL_TX_SW_BUFFER_CONST    (console_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define console_CHECK_SPI_WAKE_ENABLE  (console_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define console_CHECK_UART_RTS_CONTROL_FLOW    (console_SCB_MODE_UART_CONST_CFG && \
                                                             console_UART_RTS_ENABLE)

#endif /* End (console_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* console_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableFreeRunSclk;
    uint8 polaritySs;
} console_SPI_INIT_STRUCT;

/* console_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableCts;
    uint8 ctsPolarity;
    uint8 rtsRxFifoLevel;
    uint8 rtsPolarity;
} console_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(console_SCB_MODE_UNCONFIG_CONST_CFG)
    void console_SpiInit(const console_SPI_INIT_STRUCT *config);
#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(console_SCB_MODE_SPI_INC)
    #define console_SpiIsBusBusy() ((uint32) (0u != (console_SPI_STATUS_REG & \
                                                              console_SPI_STATUS_BUS_BUSY)))

    #if (console_SPI_MASTER_CONST)
        void console_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(console_SPI_MASTER_CONST) */

    #if !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1)
        void console_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1) */
#endif /* (console_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(console_SCB_MODE_UNCONFIG_CONST_CFG)
    void console_UartInit(const console_UART_INIT_STRUCT *config);
#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(console_SCB_MODE_UART_INC)
    void console_UartSetRxAddress(uint32 address);
    void console_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(console_UART_RX_DIRECTION)
        uint32 console_UartGetChar(void);
        uint32 console_UartGetByte(void);

        #if !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void console_UartSetRtsPolarity(uint32 polarity);
            void console_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1) */
    #endif /* (console_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(console_UART_TX_DIRECTION)
        #define console_UartPutChar(ch)    console_SpiUartWriteTxData((uint32)(ch))
        void console_UartPutString(const char8 string[]);
        void console_UartPutCRLF(uint32 txDataByte);

        #if !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void console_UartEnableCts(void);
            void console_UartDisableCts(void);
            void console_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(console_CY_SCBIP_V0 || console_CY_SCBIP_V1) */
    #endif /* (console_UART_TX_DIRECTION) */
#endif /* (console_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(console_RX_DIRECTION)
    uint32 console_SpiUartReadRxData(void);
    uint32 console_SpiUartGetRxBufferSize(void);
    void   console_SpiUartClearRxBuffer(void);
#endif /* (console_RX_DIRECTION) */

/* Common APIs TX direction */
#if(console_TX_DIRECTION)
    void   console_SpiUartWriteTxData(uint32 txData);
    void   console_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 console_SpiUartGetTxBufferSize(void);
    void   console_SpiUartClearTxBuffer(void);
#endif /* (console_TX_DIRECTION) */

CY_ISR_PROTO(console_SPI_UART_ISR);

#if(console_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(console_UART_WAKEUP_ISR);
#endif /* (console_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(console_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   console_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 console_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   console_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 console_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(console_INTERNAL_RX_SW_BUFFER_CONST)
        #define console_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    console_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define console_GetWordFromRxBuffer(idx) console_rxBufferInternal[(idx)]

    #endif /* (console_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(console_INTERNAL_TX_SW_BUFFER_CONST)
        #define console_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        console_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define console_GetWordFromTxBuffer(idx) console_txBufferInternal[(idx)]

    #endif /* (console_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (console_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define console_SPI_MODE_MOTOROLA      (0x00u)
#define console_SPI_MODE_TI_COINCIDES  (0x01u)
#define console_SPI_MODE_TI_PRECEDES   (0x11u)
#define console_SPI_MODE_NATIONAL      (0x02u)
#define console_SPI_MODE_MASK          (0x03u)
#define console_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define console_SPI_MODE_NS_MICROWIRE  (console_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define console_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define console_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define console_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define console_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define console_BITS_ORDER_LSB_FIRST   (0u)
#define console_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define console_SPI_TRANSFER_SEPARATED     (0u)
#define console_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define console_SPI_SLAVE_SELECT0    (console_SCB__SS0_POSISTION)
#define console_SPI_SLAVE_SELECT1    (console_SCB__SS1_POSISTION)
#define console_SPI_SLAVE_SELECT2    (console_SCB__SS2_POSISTION)
#define console_SPI_SLAVE_SELECT3    (console_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define console_SPI_SS_ACTIVE_LOW  (0u)
#define console_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define console_UART_MODE_STD          (0u)
#define console_UART_MODE_SMARTCARD    (1u)
#define console_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define console_UART_RX    (1u)
#define console_UART_TX    (2u)
#define console_UART_TX_RX (3u)

/* UART parity enum */
#define console_UART_PARITY_EVEN   (0u)
#define console_UART_PARITY_ODD    (1u)
#define console_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define console_UART_STOP_BITS_1   (2u)
#define console_UART_STOP_BITS_1_5 (3u)
#define console_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define console_UART_IRDA_LP_OVS16     (16u)
#define console_UART_IRDA_LP_OVS32     (32u)
#define console_UART_IRDA_LP_OVS48     (48u)
#define console_UART_IRDA_LP_OVS96     (96u)
#define console_UART_IRDA_LP_OVS192    (192u)
#define console_UART_IRDA_LP_OVS768    (768u)
#define console_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define console_UART_MP_MARK       (0x100u)
#define console_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define console_UART_CTS_ACTIVE_LOW    (0u)
#define console_UART_CTS_ACTIVE_HIGH   (1u)
#define console_UART_RTS_ACTIVE_LOW    (0u)
#define console_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define console_INTR_RX_ERR        (console_INTR_RX_OVERFLOW    | \
                                             console_INTR_RX_UNDERFLOW   | \
                                             console_INTR_RX_FRAME_ERROR | \
                                             console_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for console_UartGetByte() */
#define console_UART_RX_OVERFLOW       (console_INTR_RX_OVERFLOW << 8u)
#define console_UART_RX_UNDERFLOW      (console_INTR_RX_UNDERFLOW << 8u)
#define console_UART_RX_FRAME_ERROR    (console_INTR_RX_FRAME_ERROR << 8u)
#define console_UART_RX_PARITY_ERROR   (console_INTR_RX_PARITY_ERROR << 8u)
#define console_UART_RX_ERROR_MASK     (console_UART_RX_OVERFLOW    | \
                                                 console_UART_RX_UNDERFLOW   | \
                                                 console_UART_RX_FRAME_ERROR | \
                                                 console_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(console_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const console_SPI_INIT_STRUCT  console_configSpi;
    extern const console_UART_INIT_STRUCT console_configUart;
#endif /* (console_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define console_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & console_INTR_SLAVE_SPI_BUS_ERROR)
#define console_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & console_INTR_MASTER_SPI_DONE)
#define console_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~console_INTR_SLAVE_SPI_BUS_ERROR)

#define console_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~console_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define console_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((console_UART_IRDA_LP_OVS16   == (oversample)) ? console_CTRL_OVS_IRDA_LP_OVS16 : \
         ((console_UART_IRDA_LP_OVS32   == (oversample)) ? console_CTRL_OVS_IRDA_LP_OVS32 : \
          ((console_UART_IRDA_LP_OVS48   == (oversample)) ? console_CTRL_OVS_IRDA_LP_OVS48 : \
           ((console_UART_IRDA_LP_OVS96   == (oversample)) ? console_CTRL_OVS_IRDA_LP_OVS96 : \
            ((console_UART_IRDA_LP_OVS192  == (oversample)) ? console_CTRL_OVS_IRDA_LP_OVS192 : \
             ((console_UART_IRDA_LP_OVS768  == (oversample)) ? console_CTRL_OVS_IRDA_LP_OVS768 : \
              ((console_UART_IRDA_LP_OVS1536 == (oversample)) ? console_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          console_CTRL_OVS_IRDA_LP_OVS16)))))))

#define console_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (console_UART_RX & (direction))) ? \
                                                                     (console_RX_CTRL_ENABLED) : (0u))

#define console_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (console_UART_TX & (direction))) ? \
                                                                     (console_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define console_CTRL_SPI      (console_CTRL_MODE_SPI)
#define console_SPI_RX_CTRL   (console_RX_CTRL_ENABLED)
#define console_SPI_TX_CTRL   (console_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define console_SPI_SS_POLARITY \
             (((uint32) console_SPI_SS0_POLARITY << console_SPI_SLAVE_SELECT0) | \
              ((uint32) console_SPI_SS1_POLARITY << console_SPI_SLAVE_SELECT1) | \
              ((uint32) console_SPI_SS2_POLARITY << console_SPI_SLAVE_SELECT2) | \
              ((uint32) console_SPI_SS3_POLARITY << console_SPI_SLAVE_SELECT3))

#if(console_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define console_SPI_DEFAULT_CTRL \
                    (console_GET_CTRL_OVS(console_SPI_OVS_FACTOR) | \
                     console_GET_CTRL_BYTE_MODE (console_SPI_BYTE_MODE_ENABLE) | \
                     console_GET_CTRL_EC_AM_MODE(console_SPI_WAKE_ENABLE)      | \
                     console_CTRL_SPI)

    #define console_SPI_DEFAULT_SPI_CTRL \
                    (console_GET_SPI_CTRL_CONTINUOUS    (console_SPI_TRANSFER_SEPARATION)       | \
                     console_GET_SPI_CTRL_SELECT_PRECEDE(console_SPI_SUB_MODE &                   \
                                                                  console_SPI_MODE_TI_PRECEDES_MASK)     | \
                     console_GET_SPI_CTRL_SCLK_MODE     (console_SPI_CLOCK_MODE)                | \
                     console_GET_SPI_CTRL_LATE_MISO_SAMPLE(console_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     console_GET_SPI_CTRL_SCLK_CONTINUOUS(console_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     console_GET_SPI_CTRL_SSEL_POLARITY (console_SPI_SS_POLARITY)               | \
                     console_GET_SPI_CTRL_SUB_MODE      (console_SPI_SUB_MODE)                  | \
                     console_GET_SPI_CTRL_MASTER_MODE   (console_SPI_MODE))

    /* RX direction */
    #define console_SPI_DEFAULT_RX_CTRL \
                    (console_GET_RX_CTRL_DATA_WIDTH(console_SPI_RX_DATA_BITS_NUM)     | \
                     console_GET_RX_CTRL_BIT_ORDER (console_SPI_BITS_ORDER)           | \
                     console_GET_RX_CTRL_MEDIAN    (console_SPI_MEDIAN_FILTER_ENABLE) | \
                     console_SPI_RX_CTRL)

    #define console_SPI_DEFAULT_RX_FIFO_CTRL \
                    console_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(console_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define console_SPI_DEFAULT_TX_CTRL \
                    (console_GET_TX_CTRL_DATA_WIDTH(console_SPI_TX_DATA_BITS_NUM) | \
                     console_GET_TX_CTRL_BIT_ORDER (console_SPI_BITS_ORDER)       | \
                     console_SPI_TX_CTRL)

    #define console_SPI_DEFAULT_TX_FIFO_CTRL \
                    console_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(console_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define console_SPI_DEFAULT_INTR_SPI_EC_MASK   (console_NO_INTR_SOURCES)

    #define console_SPI_DEFAULT_INTR_I2C_EC_MASK   (console_NO_INTR_SOURCES)
    #define console_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (console_SPI_INTR_RX_MASK & console_INTR_SLAVE_SPI_BUS_ERROR)

    #define console_SPI_DEFAULT_INTR_MASTER_MASK \
                    (console_SPI_INTR_TX_MASK & console_INTR_MASTER_SPI_DONE)

    #define console_SPI_DEFAULT_INTR_RX_MASK \
                    (console_SPI_INTR_RX_MASK & (uint32) ~console_INTR_SLAVE_SPI_BUS_ERROR)

    #define console_SPI_DEFAULT_INTR_TX_MASK \
                    (console_SPI_INTR_TX_MASK & (uint32) ~console_INTR_MASTER_SPI_DONE)

#endif /* (console_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define console_CTRL_UART      (console_CTRL_MODE_UART)
#define console_UART_RX_CTRL   (console_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define console_UART_TX_CTRL   (console_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(console_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(console_UART_MODE_IRDA == console_UART_SUB_MODE)

        #define console_DEFAULT_CTRL_OVS   ((0u != console_UART_IRDA_LOW_POWER) ?              \
                                (console_UART_GET_CTRL_OVS_IRDA_LP(console_UART_OVS_FACTOR)) : \
                                (console_CTRL_OVS_IRDA_OVS16))

    #else

        #define console_DEFAULT_CTRL_OVS   console_GET_CTRL_OVS(console_UART_OVS_FACTOR)

    #endif /* (console_UART_MODE_IRDA == console_UART_SUB_MODE) */

    #define console_UART_DEFAULT_CTRL \
                                (console_GET_CTRL_BYTE_MODE  (console_UART_BYTE_MODE_ENABLE)  | \
                                 console_GET_CTRL_ADDR_ACCEPT(console_UART_MP_ACCEPT_ADDRESS) | \
                                 console_DEFAULT_CTRL_OVS                                              | \
                                 console_CTRL_UART)

    #define console_UART_DEFAULT_UART_CTRL \
                                    (console_GET_UART_CTRL_MODE(console_UART_SUB_MODE))

    /* RX direction */
    #define console_UART_DEFAULT_RX_CTRL_PARITY \
                                ((console_UART_PARITY_NONE != console_UART_PARITY_TYPE) ?      \
                                  (console_GET_UART_RX_CTRL_PARITY(console_UART_PARITY_TYPE) | \
                                   console_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define console_UART_DEFAULT_UART_RX_CTRL \
                    (console_GET_UART_RX_CTRL_MODE(console_UART_STOP_BITS_NUM)                    | \
                     console_GET_UART_RX_CTRL_POLARITY(console_UART_IRDA_POLARITY)                | \
                     console_GET_UART_RX_CTRL_MP_MODE(console_UART_MP_MODE_ENABLE)                | \
                     console_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(console_UART_DROP_ON_PARITY_ERR) | \
                     console_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(console_UART_DROP_ON_FRAME_ERR)   | \
                     console_UART_DEFAULT_RX_CTRL_PARITY)

    #define console_UART_DEFAULT_RX_CTRL \
                                (console_GET_RX_CTRL_DATA_WIDTH(console_UART_DATA_BITS_NUM)        | \
                                 console_GET_RX_CTRL_MEDIAN    (console_UART_MEDIAN_FILTER_ENABLE) | \
                                 console_GET_UART_RX_CTRL_ENABLED(console_UART_DIRECTION))

    #define console_UART_DEFAULT_RX_FIFO_CTRL \
                                console_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(console_UART_RX_TRIGGER_LEVEL)

    #define console_UART_DEFAULT_RX_MATCH_REG  ((0u != console_UART_MP_MODE_ENABLE) ?          \
                                (console_GET_RX_MATCH_ADDR(console_UART_MP_RX_ADDRESS) | \
                                 console_GET_RX_MATCH_MASK(console_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define console_UART_DEFAULT_TX_CTRL_PARITY (console_UART_DEFAULT_RX_CTRL_PARITY)

    #define console_UART_DEFAULT_UART_TX_CTRL \
                                (console_GET_UART_TX_CTRL_MODE(console_UART_STOP_BITS_NUM)       | \
                                 console_GET_UART_TX_CTRL_RETRY_NACK(console_UART_RETRY_ON_NACK) | \
                                 console_UART_DEFAULT_TX_CTRL_PARITY)

    #define console_UART_DEFAULT_TX_CTRL \
                                (console_GET_TX_CTRL_DATA_WIDTH(console_UART_DATA_BITS_NUM) | \
                                 console_GET_UART_TX_CTRL_ENABLED(console_UART_DIRECTION))

    #define console_UART_DEFAULT_TX_FIFO_CTRL \
                                console_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(console_UART_TX_TRIGGER_LEVEL)

    #define console_UART_DEFAULT_FLOW_CTRL \
                        (console_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(console_UART_RTS_FIFO_LEVEL) | \
                         console_GET_UART_FLOW_CTRL_RTS_POLARITY (console_UART_RTS_POLARITY)   | \
                         console_GET_UART_FLOW_CTRL_CTS_POLARITY (console_UART_CTS_POLARITY)   | \
                         console_GET_UART_FLOW_CTRL_CTS_ENABLE   (console_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define console_UART_DEFAULT_INTR_I2C_EC_MASK  (console_NO_INTR_SOURCES)
    #define console_UART_DEFAULT_INTR_SPI_EC_MASK  (console_NO_INTR_SOURCES)
    #define console_UART_DEFAULT_INTR_SLAVE_MASK   (console_NO_INTR_SOURCES)
    #define console_UART_DEFAULT_INTR_MASTER_MASK  (console_NO_INTR_SOURCES)
    #define console_UART_DEFAULT_INTR_RX_MASK      (console_UART_INTR_RX_MASK)
    #define console_UART_DEFAULT_INTR_TX_MASK      (console_UART_INTR_TX_MASK)

#endif /* (console_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define console_SPIM_ACTIVE_SS0    (console_SPI_SLAVE_SELECT0)
#define console_SPIM_ACTIVE_SS1    (console_SPI_SLAVE_SELECT1)
#define console_SPIM_ACTIVE_SS2    (console_SPI_SLAVE_SELECT2)
#define console_SPIM_ACTIVE_SS3    (console_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_console_H */


/* [] END OF FILE */
