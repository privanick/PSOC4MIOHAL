/*******************************************************************************
* File Name: chan1n.h  
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

#if !defined(CY_PINS_chan1n_H) /* Pins chan1n_H */
#define CY_PINS_chan1n_H

#include "cytypes.h"
#include "cyfitter.h"
#include "chan1n_aliases.h"


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
} chan1n_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   chan1n_Read(void);
void    chan1n_Write(uint8 value);
uint8   chan1n_ReadDataReg(void);
#if defined(chan1n__PC) || (CY_PSOC4_4200L) 
    void    chan1n_SetDriveMode(uint8 mode);
#endif
void    chan1n_SetInterruptMode(uint16 position, uint16 mode);
uint8   chan1n_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void chan1n_Sleep(void); 
void chan1n_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(chan1n__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define chan1n_DRIVE_MODE_BITS        (3)
    #define chan1n_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - chan1n_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the chan1n_SetDriveMode() function.
         *  @{
         */
        #define chan1n_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define chan1n_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define chan1n_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define chan1n_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define chan1n_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define chan1n_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define chan1n_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define chan1n_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define chan1n_MASK               chan1n__MASK
#define chan1n_SHIFT              chan1n__SHIFT
#define chan1n_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in chan1n_SetInterruptMode() function.
     *  @{
     */
        #define chan1n_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define chan1n_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define chan1n_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define chan1n_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(chan1n__SIO)
    #define chan1n_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(chan1n__PC) && (CY_PSOC4_4200L)
    #define chan1n_USBIO_ENABLE               ((uint32)0x80000000u)
    #define chan1n_USBIO_DISABLE              ((uint32)(~chan1n_USBIO_ENABLE))
    #define chan1n_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define chan1n_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define chan1n_USBIO_ENTER_SLEEP          ((uint32)((1u << chan1n_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << chan1n_USBIO_SUSPEND_DEL_SHIFT)))
    #define chan1n_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << chan1n_USBIO_SUSPEND_SHIFT)))
    #define chan1n_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << chan1n_USBIO_SUSPEND_DEL_SHIFT)))
    #define chan1n_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(chan1n__PC)
    /* Port Configuration */
    #define chan1n_PC                 (* (reg32 *) chan1n__PC)
#endif
/* Pin State */
#define chan1n_PS                     (* (reg32 *) chan1n__PS)
/* Data Register */
#define chan1n_DR                     (* (reg32 *) chan1n__DR)
/* Input Buffer Disable Override */
#define chan1n_INP_DIS                (* (reg32 *) chan1n__PC2)

/* Interrupt configuration Registers */
#define chan1n_INTCFG                 (* (reg32 *) chan1n__INTCFG)
#define chan1n_INTSTAT                (* (reg32 *) chan1n__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define chan1n_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(chan1n__SIO)
    #define chan1n_SIO_REG            (* (reg32 *) chan1n__SIO)
#endif /* (chan1n__SIO_CFG) */

/* USBIO registers */
#if !defined(chan1n__PC) && (CY_PSOC4_4200L)
    #define chan1n_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define chan1n_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define chan1n_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define chan1n_DRIVE_MODE_SHIFT       (0x00u)
#define chan1n_DRIVE_MODE_MASK        (0x07u << chan1n_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins chan1n_H */


/* [] END OF FILE */
