/*******************************************************************************
* File Name: press2_6.h  
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

#if !defined(CY_PINS_press2_6_H) /* Pins press2_6_H */
#define CY_PINS_press2_6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "press2_6_aliases.h"


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
} press2_6_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   press2_6_Read(void);
void    press2_6_Write(uint8 value);
uint8   press2_6_ReadDataReg(void);
#if defined(press2_6__PC) || (CY_PSOC4_4200L) 
    void    press2_6_SetDriveMode(uint8 mode);
#endif
void    press2_6_SetInterruptMode(uint16 position, uint16 mode);
uint8   press2_6_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void press2_6_Sleep(void); 
void press2_6_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(press2_6__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define press2_6_DRIVE_MODE_BITS        (3)
    #define press2_6_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - press2_6_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the press2_6_SetDriveMode() function.
         *  @{
         */
        #define press2_6_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define press2_6_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define press2_6_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define press2_6_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define press2_6_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define press2_6_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define press2_6_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define press2_6_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define press2_6_MASK               press2_6__MASK
#define press2_6_SHIFT              press2_6__SHIFT
#define press2_6_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in press2_6_SetInterruptMode() function.
     *  @{
     */
        #define press2_6_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define press2_6_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define press2_6_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define press2_6_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(press2_6__SIO)
    #define press2_6_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(press2_6__PC) && (CY_PSOC4_4200L)
    #define press2_6_USBIO_ENABLE               ((uint32)0x80000000u)
    #define press2_6_USBIO_DISABLE              ((uint32)(~press2_6_USBIO_ENABLE))
    #define press2_6_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define press2_6_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define press2_6_USBIO_ENTER_SLEEP          ((uint32)((1u << press2_6_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << press2_6_USBIO_SUSPEND_DEL_SHIFT)))
    #define press2_6_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << press2_6_USBIO_SUSPEND_SHIFT)))
    #define press2_6_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << press2_6_USBIO_SUSPEND_DEL_SHIFT)))
    #define press2_6_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(press2_6__PC)
    /* Port Configuration */
    #define press2_6_PC                 (* (reg32 *) press2_6__PC)
#endif
/* Pin State */
#define press2_6_PS                     (* (reg32 *) press2_6__PS)
/* Data Register */
#define press2_6_DR                     (* (reg32 *) press2_6__DR)
/* Input Buffer Disable Override */
#define press2_6_INP_DIS                (* (reg32 *) press2_6__PC2)

/* Interrupt configuration Registers */
#define press2_6_INTCFG                 (* (reg32 *) press2_6__INTCFG)
#define press2_6_INTSTAT                (* (reg32 *) press2_6__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define press2_6_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(press2_6__SIO)
    #define press2_6_SIO_REG            (* (reg32 *) press2_6__SIO)
#endif /* (press2_6__SIO_CFG) */

/* USBIO registers */
#if !defined(press2_6__PC) && (CY_PSOC4_4200L)
    #define press2_6_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define press2_6_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define press2_6_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define press2_6_DRIVE_MODE_SHIFT       (0x00u)
#define press2_6_DRIVE_MODE_MASK        (0x07u << press2_6_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins press2_6_H */


/* [] END OF FILE */
