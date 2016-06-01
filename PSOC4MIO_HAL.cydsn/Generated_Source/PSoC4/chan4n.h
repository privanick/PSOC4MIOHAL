/*******************************************************************************
* File Name: chan4n.h  
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

#if !defined(CY_PINS_chan4n_H) /* Pins chan4n_H */
#define CY_PINS_chan4n_H

#include "cytypes.h"
#include "cyfitter.h"
#include "chan4n_aliases.h"


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
} chan4n_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   chan4n_Read(void);
void    chan4n_Write(uint8 value);
uint8   chan4n_ReadDataReg(void);
#if defined(chan4n__PC) || (CY_PSOC4_4200L) 
    void    chan4n_SetDriveMode(uint8 mode);
#endif
void    chan4n_SetInterruptMode(uint16 position, uint16 mode);
uint8   chan4n_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void chan4n_Sleep(void); 
void chan4n_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(chan4n__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define chan4n_DRIVE_MODE_BITS        (3)
    #define chan4n_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - chan4n_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the chan4n_SetDriveMode() function.
         *  @{
         */
        #define chan4n_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define chan4n_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define chan4n_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define chan4n_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define chan4n_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define chan4n_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define chan4n_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define chan4n_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define chan4n_MASK               chan4n__MASK
#define chan4n_SHIFT              chan4n__SHIFT
#define chan4n_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in chan4n_SetInterruptMode() function.
     *  @{
     */
        #define chan4n_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define chan4n_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define chan4n_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define chan4n_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(chan4n__SIO)
    #define chan4n_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(chan4n__PC) && (CY_PSOC4_4200L)
    #define chan4n_USBIO_ENABLE               ((uint32)0x80000000u)
    #define chan4n_USBIO_DISABLE              ((uint32)(~chan4n_USBIO_ENABLE))
    #define chan4n_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define chan4n_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define chan4n_USBIO_ENTER_SLEEP          ((uint32)((1u << chan4n_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << chan4n_USBIO_SUSPEND_DEL_SHIFT)))
    #define chan4n_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << chan4n_USBIO_SUSPEND_SHIFT)))
    #define chan4n_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << chan4n_USBIO_SUSPEND_DEL_SHIFT)))
    #define chan4n_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(chan4n__PC)
    /* Port Configuration */
    #define chan4n_PC                 (* (reg32 *) chan4n__PC)
#endif
/* Pin State */
#define chan4n_PS                     (* (reg32 *) chan4n__PS)
/* Data Register */
#define chan4n_DR                     (* (reg32 *) chan4n__DR)
/* Input Buffer Disable Override */
#define chan4n_INP_DIS                (* (reg32 *) chan4n__PC2)

/* Interrupt configuration Registers */
#define chan4n_INTCFG                 (* (reg32 *) chan4n__INTCFG)
#define chan4n_INTSTAT                (* (reg32 *) chan4n__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define chan4n_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(chan4n__SIO)
    #define chan4n_SIO_REG            (* (reg32 *) chan4n__SIO)
#endif /* (chan4n__SIO_CFG) */

/* USBIO registers */
#if !defined(chan4n__PC) && (CY_PSOC4_4200L)
    #define chan4n_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define chan4n_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define chan4n_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define chan4n_DRIVE_MODE_SHIFT       (0x00u)
#define chan4n_DRIVE_MODE_MASK        (0x07u << chan4n_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins chan4n_H */


/* [] END OF FILE */
