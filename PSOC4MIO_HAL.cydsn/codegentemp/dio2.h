/*******************************************************************************
* File Name: dio2.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_dio2_H) /* Pins dio2_H */
#define CY_PINS_dio2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "dio2_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} dio2_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   dio2_Read(void);
void    dio2_Write(uint8 value);
uint8   dio2_ReadDataReg(void);
#if defined(dio2__PC) || (CY_PSOC4_4200L) 
    void    dio2_SetDriveMode(uint8 mode);
#endif
void    dio2_SetInterruptMode(uint16 position, uint16 mode);
uint8   dio2_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void dio2_Sleep(void); 
void dio2_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(dio2__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define dio2_DRIVE_MODE_BITS        (3)
    #define dio2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - dio2_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the dio2_SetDriveMode() function.
         *  @{
         */
        #define dio2_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define dio2_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define dio2_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define dio2_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define dio2_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define dio2_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define dio2_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define dio2_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define dio2_MASK               dio2__MASK
#define dio2_SHIFT              dio2__SHIFT
#define dio2_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in dio2_SetInterruptMode() function.
     *  @{
     */
        #define dio2_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define dio2_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define dio2_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define dio2_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(dio2__SIO)
    #define dio2_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(dio2__PC) && (CY_PSOC4_4200L)
    #define dio2_USBIO_ENABLE               ((uint32)0x80000000u)
    #define dio2_USBIO_DISABLE              ((uint32)(~dio2_USBIO_ENABLE))
    #define dio2_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define dio2_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define dio2_USBIO_ENTER_SLEEP          ((uint32)((1u << dio2_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << dio2_USBIO_SUSPEND_DEL_SHIFT)))
    #define dio2_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << dio2_USBIO_SUSPEND_SHIFT)))
    #define dio2_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << dio2_USBIO_SUSPEND_DEL_SHIFT)))
    #define dio2_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(dio2__PC)
    /* Port Configuration */
    #define dio2_PC                 (* (reg32 *) dio2__PC)
#endif
/* Pin State */
#define dio2_PS                     (* (reg32 *) dio2__PS)
/* Data Register */
#define dio2_DR                     (* (reg32 *) dio2__DR)
/* Input Buffer Disable Override */
#define dio2_INP_DIS                (* (reg32 *) dio2__PC2)

/* Interrupt configuration Registers */
#define dio2_INTCFG                 (* (reg32 *) dio2__INTCFG)
#define dio2_INTSTAT                (* (reg32 *) dio2__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define dio2_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(dio2__SIO)
    #define dio2_SIO_REG            (* (reg32 *) dio2__SIO)
#endif /* (dio2__SIO_CFG) */

/* USBIO registers */
#if !defined(dio2__PC) && (CY_PSOC4_4200L)
    #define dio2_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define dio2_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define dio2_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define dio2_DRIVE_MODE_SHIFT       (0x00u)
#define dio2_DRIVE_MODE_MASK        (0x07u << dio2_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins dio2_H */


/* [] END OF FILE */
