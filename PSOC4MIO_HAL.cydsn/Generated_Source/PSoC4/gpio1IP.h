/*******************************************************************************
* File Name: gpio1IP.h  
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

#if !defined(CY_PINS_gpio1IP_H) /* Pins gpio1IP_H */
#define CY_PINS_gpio1IP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "gpio1IP_aliases.h"


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
} gpio1IP_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   gpio1IP_Read(void);
void    gpio1IP_Write(uint8 value);
uint8   gpio1IP_ReadDataReg(void);
#if defined(gpio1IP__PC) || (CY_PSOC4_4200L) 
    void    gpio1IP_SetDriveMode(uint8 mode);
#endif
void    gpio1IP_SetInterruptMode(uint16 position, uint16 mode);
uint8   gpio1IP_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void gpio1IP_Sleep(void); 
void gpio1IP_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(gpio1IP__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define gpio1IP_DRIVE_MODE_BITS        (3)
    #define gpio1IP_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - gpio1IP_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the gpio1IP_SetDriveMode() function.
         *  @{
         */
        #define gpio1IP_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define gpio1IP_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define gpio1IP_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define gpio1IP_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define gpio1IP_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define gpio1IP_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define gpio1IP_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define gpio1IP_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define gpio1IP_MASK               gpio1IP__MASK
#define gpio1IP_SHIFT              gpio1IP__SHIFT
#define gpio1IP_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in gpio1IP_SetInterruptMode() function.
     *  @{
     */
        #define gpio1IP_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define gpio1IP_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define gpio1IP_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define gpio1IP_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(gpio1IP__SIO)
    #define gpio1IP_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(gpio1IP__PC) && (CY_PSOC4_4200L)
    #define gpio1IP_USBIO_ENABLE               ((uint32)0x80000000u)
    #define gpio1IP_USBIO_DISABLE              ((uint32)(~gpio1IP_USBIO_ENABLE))
    #define gpio1IP_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define gpio1IP_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define gpio1IP_USBIO_ENTER_SLEEP          ((uint32)((1u << gpio1IP_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << gpio1IP_USBIO_SUSPEND_DEL_SHIFT)))
    #define gpio1IP_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << gpio1IP_USBIO_SUSPEND_SHIFT)))
    #define gpio1IP_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << gpio1IP_USBIO_SUSPEND_DEL_SHIFT)))
    #define gpio1IP_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(gpio1IP__PC)
    /* Port Configuration */
    #define gpio1IP_PC                 (* (reg32 *) gpio1IP__PC)
#endif
/* Pin State */
#define gpio1IP_PS                     (* (reg32 *) gpio1IP__PS)
/* Data Register */
#define gpio1IP_DR                     (* (reg32 *) gpio1IP__DR)
/* Input Buffer Disable Override */
#define gpio1IP_INP_DIS                (* (reg32 *) gpio1IP__PC2)

/* Interrupt configuration Registers */
#define gpio1IP_INTCFG                 (* (reg32 *) gpio1IP__INTCFG)
#define gpio1IP_INTSTAT                (* (reg32 *) gpio1IP__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define gpio1IP_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(gpio1IP__SIO)
    #define gpio1IP_SIO_REG            (* (reg32 *) gpio1IP__SIO)
#endif /* (gpio1IP__SIO_CFG) */

/* USBIO registers */
#if !defined(gpio1IP__PC) && (CY_PSOC4_4200L)
    #define gpio1IP_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define gpio1IP_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define gpio1IP_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define gpio1IP_DRIVE_MODE_SHIFT       (0x00u)
#define gpio1IP_DRIVE_MODE_MASK        (0x07u << gpio1IP_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins gpio1IP_H */


/* [] END OF FILE */
