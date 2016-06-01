/*******************************************************************************
* File Name: gpio1_led.h  
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

#if !defined(CY_PINS_gpio1_led_H) /* Pins gpio1_led_H */
#define CY_PINS_gpio1_led_H

#include "cytypes.h"
#include "cyfitter.h"
#include "gpio1_led_aliases.h"


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
} gpio1_led_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   gpio1_led_Read(void);
void    gpio1_led_Write(uint8 value);
uint8   gpio1_led_ReadDataReg(void);
#if defined(gpio1_led__PC) || (CY_PSOC4_4200L) 
    void    gpio1_led_SetDriveMode(uint8 mode);
#endif
void    gpio1_led_SetInterruptMode(uint16 position, uint16 mode);
uint8   gpio1_led_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void gpio1_led_Sleep(void); 
void gpio1_led_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(gpio1_led__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define gpio1_led_DRIVE_MODE_BITS        (3)
    #define gpio1_led_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - gpio1_led_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the gpio1_led_SetDriveMode() function.
         *  @{
         */
        #define gpio1_led_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define gpio1_led_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define gpio1_led_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define gpio1_led_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define gpio1_led_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define gpio1_led_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define gpio1_led_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define gpio1_led_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define gpio1_led_MASK               gpio1_led__MASK
#define gpio1_led_SHIFT              gpio1_led__SHIFT
#define gpio1_led_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in gpio1_led_SetInterruptMode() function.
     *  @{
     */
        #define gpio1_led_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define gpio1_led_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define gpio1_led_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define gpio1_led_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(gpio1_led__SIO)
    #define gpio1_led_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(gpio1_led__PC) && (CY_PSOC4_4200L)
    #define gpio1_led_USBIO_ENABLE               ((uint32)0x80000000u)
    #define gpio1_led_USBIO_DISABLE              ((uint32)(~gpio1_led_USBIO_ENABLE))
    #define gpio1_led_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define gpio1_led_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define gpio1_led_USBIO_ENTER_SLEEP          ((uint32)((1u << gpio1_led_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << gpio1_led_USBIO_SUSPEND_DEL_SHIFT)))
    #define gpio1_led_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << gpio1_led_USBIO_SUSPEND_SHIFT)))
    #define gpio1_led_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << gpio1_led_USBIO_SUSPEND_DEL_SHIFT)))
    #define gpio1_led_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(gpio1_led__PC)
    /* Port Configuration */
    #define gpio1_led_PC                 (* (reg32 *) gpio1_led__PC)
#endif
/* Pin State */
#define gpio1_led_PS                     (* (reg32 *) gpio1_led__PS)
/* Data Register */
#define gpio1_led_DR                     (* (reg32 *) gpio1_led__DR)
/* Input Buffer Disable Override */
#define gpio1_led_INP_DIS                (* (reg32 *) gpio1_led__PC2)

/* Interrupt configuration Registers */
#define gpio1_led_INTCFG                 (* (reg32 *) gpio1_led__INTCFG)
#define gpio1_led_INTSTAT                (* (reg32 *) gpio1_led__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define gpio1_led_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(gpio1_led__SIO)
    #define gpio1_led_SIO_REG            (* (reg32 *) gpio1_led__SIO)
#endif /* (gpio1_led__SIO_CFG) */

/* USBIO registers */
#if !defined(gpio1_led__PC) && (CY_PSOC4_4200L)
    #define gpio1_led_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define gpio1_led_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define gpio1_led_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define gpio1_led_DRIVE_MODE_SHIFT       (0x00u)
#define gpio1_led_DRIVE_MODE_MASK        (0x07u << gpio1_led_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins gpio1_led_H */


/* [] END OF FILE */
