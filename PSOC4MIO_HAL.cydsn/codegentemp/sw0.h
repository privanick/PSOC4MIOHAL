/*******************************************************************************
* File Name: sw0.h  
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

#if !defined(CY_PINS_sw0_H) /* Pins sw0_H */
#define CY_PINS_sw0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "sw0_aliases.h"


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
} sw0_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   sw0_Read(void);
void    sw0_Write(uint8 value);
uint8   sw0_ReadDataReg(void);
#if defined(sw0__PC) || (CY_PSOC4_4200L) 
    void    sw0_SetDriveMode(uint8 mode);
#endif
void    sw0_SetInterruptMode(uint16 position, uint16 mode);
uint8   sw0_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void sw0_Sleep(void); 
void sw0_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(sw0__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define sw0_DRIVE_MODE_BITS        (3)
    #define sw0_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - sw0_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the sw0_SetDriveMode() function.
         *  @{
         */
        #define sw0_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define sw0_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define sw0_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define sw0_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define sw0_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define sw0_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define sw0_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define sw0_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define sw0_MASK               sw0__MASK
#define sw0_SHIFT              sw0__SHIFT
#define sw0_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sw0_SetInterruptMode() function.
     *  @{
     */
        #define sw0_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define sw0_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define sw0_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define sw0_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(sw0__SIO)
    #define sw0_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(sw0__PC) && (CY_PSOC4_4200L)
    #define sw0_USBIO_ENABLE               ((uint32)0x80000000u)
    #define sw0_USBIO_DISABLE              ((uint32)(~sw0_USBIO_ENABLE))
    #define sw0_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define sw0_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define sw0_USBIO_ENTER_SLEEP          ((uint32)((1u << sw0_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << sw0_USBIO_SUSPEND_DEL_SHIFT)))
    #define sw0_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << sw0_USBIO_SUSPEND_SHIFT)))
    #define sw0_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << sw0_USBIO_SUSPEND_DEL_SHIFT)))
    #define sw0_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(sw0__PC)
    /* Port Configuration */
    #define sw0_PC                 (* (reg32 *) sw0__PC)
#endif
/* Pin State */
#define sw0_PS                     (* (reg32 *) sw0__PS)
/* Data Register */
#define sw0_DR                     (* (reg32 *) sw0__DR)
/* Input Buffer Disable Override */
#define sw0_INP_DIS                (* (reg32 *) sw0__PC2)

/* Interrupt configuration Registers */
#define sw0_INTCFG                 (* (reg32 *) sw0__INTCFG)
#define sw0_INTSTAT                (* (reg32 *) sw0__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define sw0_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(sw0__SIO)
    #define sw0_SIO_REG            (* (reg32 *) sw0__SIO)
#endif /* (sw0__SIO_CFG) */

/* USBIO registers */
#if !defined(sw0__PC) && (CY_PSOC4_4200L)
    #define sw0_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define sw0_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define sw0_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define sw0_DRIVE_MODE_SHIFT       (0x00u)
#define sw0_DRIVE_MODE_MASK        (0x07u << sw0_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins sw0_H */


/* [] END OF FILE */
