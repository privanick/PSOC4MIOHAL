/*******************************************************************************
* File Name: chan4p.h  
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

#if !defined(CY_PINS_chan4p_H) /* Pins chan4p_H */
#define CY_PINS_chan4p_H

#include "cytypes.h"
#include "cyfitter.h"
#include "chan4p_aliases.h"


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
} chan4p_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   chan4p_Read(void);
void    chan4p_Write(uint8 value);
uint8   chan4p_ReadDataReg(void);
#if defined(chan4p__PC) || (CY_PSOC4_4200L) 
    void    chan4p_SetDriveMode(uint8 mode);
#endif
void    chan4p_SetInterruptMode(uint16 position, uint16 mode);
uint8   chan4p_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void chan4p_Sleep(void); 
void chan4p_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(chan4p__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define chan4p_DRIVE_MODE_BITS        (3)
    #define chan4p_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - chan4p_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the chan4p_SetDriveMode() function.
         *  @{
         */
        #define chan4p_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define chan4p_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define chan4p_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define chan4p_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define chan4p_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define chan4p_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define chan4p_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define chan4p_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define chan4p_MASK               chan4p__MASK
#define chan4p_SHIFT              chan4p__SHIFT
#define chan4p_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in chan4p_SetInterruptMode() function.
     *  @{
     */
        #define chan4p_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define chan4p_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define chan4p_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define chan4p_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(chan4p__SIO)
    #define chan4p_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(chan4p__PC) && (CY_PSOC4_4200L)
    #define chan4p_USBIO_ENABLE               ((uint32)0x80000000u)
    #define chan4p_USBIO_DISABLE              ((uint32)(~chan4p_USBIO_ENABLE))
    #define chan4p_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define chan4p_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define chan4p_USBIO_ENTER_SLEEP          ((uint32)((1u << chan4p_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << chan4p_USBIO_SUSPEND_DEL_SHIFT)))
    #define chan4p_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << chan4p_USBIO_SUSPEND_SHIFT)))
    #define chan4p_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << chan4p_USBIO_SUSPEND_DEL_SHIFT)))
    #define chan4p_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(chan4p__PC)
    /* Port Configuration */
    #define chan4p_PC                 (* (reg32 *) chan4p__PC)
#endif
/* Pin State */
#define chan4p_PS                     (* (reg32 *) chan4p__PS)
/* Data Register */
#define chan4p_DR                     (* (reg32 *) chan4p__DR)
/* Input Buffer Disable Override */
#define chan4p_INP_DIS                (* (reg32 *) chan4p__PC2)

/* Interrupt configuration Registers */
#define chan4p_INTCFG                 (* (reg32 *) chan4p__INTCFG)
#define chan4p_INTSTAT                (* (reg32 *) chan4p__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define chan4p_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(chan4p__SIO)
    #define chan4p_SIO_REG            (* (reg32 *) chan4p__SIO)
#endif /* (chan4p__SIO_CFG) */

/* USBIO registers */
#if !defined(chan4p__PC) && (CY_PSOC4_4200L)
    #define chan4p_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define chan4p_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define chan4p_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define chan4p_DRIVE_MODE_SHIFT       (0x00u)
#define chan4p_DRIVE_MODE_MASK        (0x07u << chan4p_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins chan4p_H */


/* [] END OF FILE */
