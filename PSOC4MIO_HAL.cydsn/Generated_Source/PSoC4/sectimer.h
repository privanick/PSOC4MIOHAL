/*******************************************************************************
* File Name: sectimer.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_sectimer_H)
#define CY_Timer_v2_60_sectimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 sectimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define sectimer_Resolution                 16u
#define sectimer_UsingFixedFunction         0u
#define sectimer_UsingHWCaptureCounter      0u
#define sectimer_SoftwareCaptureMode        0u
#define sectimer_SoftwareTriggerMode        0u
#define sectimer_UsingHWEnable              0u
#define sectimer_EnableTriggerMode          0u
#define sectimer_InterruptOnCaptureCount    0u
#define sectimer_RunModeUsed                0u
#define sectimer_ControlRegRemoved          0u

#if defined(sectimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define sectimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (sectimer_UsingFixedFunction)
    #define sectimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define sectimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End sectimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!sectimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (sectimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!sectimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}sectimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    sectimer_Start(void) ;
void    sectimer_Stop(void) ;

void    sectimer_SetInterruptMode(uint8 interruptMode) ;
uint8   sectimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define sectimer_GetInterruptSource() sectimer_ReadStatusRegister()

#if(!sectimer_UDB_CONTROL_REG_REMOVED)
    uint8   sectimer_ReadControlRegister(void) ;
    void    sectimer_WriteControlRegister(uint8 control) ;
#endif /* (!sectimer_UDB_CONTROL_REG_REMOVED) */

uint16  sectimer_ReadPeriod(void) ;
void    sectimer_WritePeriod(uint16 period) ;
uint16  sectimer_ReadCounter(void) ;
void    sectimer_WriteCounter(uint16 counter) ;
uint16  sectimer_ReadCapture(void) ;
void    sectimer_SoftwareCapture(void) ;

#if(!sectimer_UsingFixedFunction) /* UDB Prototypes */
    #if (sectimer_SoftwareCaptureMode)
        void    sectimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!sectimer_UsingFixedFunction) */

    #if (sectimer_SoftwareTriggerMode)
        void    sectimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (sectimer_SoftwareTriggerMode) */

    #if (sectimer_EnableTriggerMode)
        void    sectimer_EnableTrigger(void) ;
        void    sectimer_DisableTrigger(void) ;
    #endif /* (sectimer_EnableTriggerMode) */


    #if(sectimer_InterruptOnCaptureCount)
        void    sectimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (sectimer_InterruptOnCaptureCount) */

    #if (sectimer_UsingHWCaptureCounter)
        void    sectimer_SetCaptureCount(uint8 captureCount) ;
        uint8   sectimer_ReadCaptureCount(void) ;
    #endif /* (sectimer_UsingHWCaptureCounter) */

    void sectimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void sectimer_Init(void)          ;
void sectimer_Enable(void)        ;
void sectimer_SaveConfig(void)    ;
void sectimer_RestoreConfig(void) ;
void sectimer_Sleep(void)         ;
void sectimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define sectimer__B_TIMER__CM_NONE 0
#define sectimer__B_TIMER__CM_RISINGEDGE 1
#define sectimer__B_TIMER__CM_FALLINGEDGE 2
#define sectimer__B_TIMER__CM_EITHEREDGE 3
#define sectimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define sectimer__B_TIMER__TM_NONE 0x00u
#define sectimer__B_TIMER__TM_RISINGEDGE 0x04u
#define sectimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define sectimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define sectimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define sectimer_INIT_PERIOD             32769u
#define sectimer_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << sectimer_CTRL_CAP_MODE_SHIFT))
#define sectimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << sectimer_CTRL_TRIG_MODE_SHIFT))
#if (sectimer_UsingFixedFunction)
    #define sectimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << sectimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << sectimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define sectimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << sectimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << sectimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << sectimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (sectimer_UsingFixedFunction) */
#define sectimer_INIT_CAPTURE_COUNT      (2u)
#define sectimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << sectimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (sectimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define sectimer_STATUS         (*(reg8 *) sectimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define sectimer_STATUS_MASK    (*(reg8 *) sectimer_TimerHW__SR0 )
    #define sectimer_CONTROL        (*(reg8 *) sectimer_TimerHW__CFG0)
    #define sectimer_CONTROL2       (*(reg8 *) sectimer_TimerHW__CFG1)
    #define sectimer_CONTROL2_PTR   ( (reg8 *) sectimer_TimerHW__CFG1)
    #define sectimer_RT1            (*(reg8 *) sectimer_TimerHW__RT1)
    #define sectimer_RT1_PTR        ( (reg8 *) sectimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define sectimer_CONTROL3       (*(reg8 *) sectimer_TimerHW__CFG2)
        #define sectimer_CONTROL3_PTR   ( (reg8 *) sectimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define sectimer_GLOBAL_ENABLE  (*(reg8 *) sectimer_TimerHW__PM_ACT_CFG)
    #define sectimer_GLOBAL_STBY_ENABLE  (*(reg8 *) sectimer_TimerHW__PM_STBY_CFG)

    #define sectimer_CAPTURE_LSB         (* (reg16 *) sectimer_TimerHW__CAP0 )
    #define sectimer_CAPTURE_LSB_PTR       ((reg16 *) sectimer_TimerHW__CAP0 )
    #define sectimer_PERIOD_LSB          (* (reg16 *) sectimer_TimerHW__PER0 )
    #define sectimer_PERIOD_LSB_PTR        ((reg16 *) sectimer_TimerHW__PER0 )
    #define sectimer_COUNTER_LSB         (* (reg16 *) sectimer_TimerHW__CNT_CMP0 )
    #define sectimer_COUNTER_LSB_PTR       ((reg16 *) sectimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define sectimer_BLOCK_EN_MASK                     sectimer_TimerHW__PM_ACT_MSK
    #define sectimer_BLOCK_STBY_EN_MASK                sectimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define sectimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define sectimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define sectimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define sectimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define sectimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define sectimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << sectimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define sectimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define sectimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << sectimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define sectimer_CTRL_MODE_SHIFT                 0x01u
        #define sectimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << sectimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define sectimer_CTRL_RCOD_SHIFT        0x02u
        #define sectimer_CTRL_ENBL_SHIFT        0x00u
        #define sectimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define sectimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << sectimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define sectimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << sectimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define sectimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << sectimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define sectimer_CTRL_RCOD       ((uint8)((uint8)0x03u << sectimer_CTRL_RCOD_SHIFT))
        #define sectimer_CTRL_ENBL       ((uint8)((uint8)0x80u << sectimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define sectimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define sectimer_RT1_MASK                        ((uint8)((uint8)0x03u << sectimer_RT1_SHIFT))
    #define sectimer_SYNC                            ((uint8)((uint8)0x03u << sectimer_RT1_SHIFT))
    #define sectimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define sectimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << sectimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define sectimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << sectimer_SYNCDSI_SHIFT))

    #define sectimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << sectimer_CTRL_MODE_SHIFT))
    #define sectimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << sectimer_CTRL_MODE_SHIFT))
    #define sectimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << sectimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define sectimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define sectimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define sectimer_STATUS_TC_INT_MASK_SHIFT        (sectimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define sectimer_STATUS_CAPTURE_INT_MASK_SHIFT   (sectimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define sectimer_STATUS_TC                       ((uint8)((uint8)0x01u << sectimer_STATUS_TC_SHIFT))
    #define sectimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << sectimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define sectimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << sectimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define sectimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << sectimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define sectimer_STATUS              (* (reg8 *) sectimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define sectimer_STATUS_MASK         (* (reg8 *) sectimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define sectimer_STATUS_AUX_CTRL     (* (reg8 *) sectimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define sectimer_CONTROL             (* (reg8 *) sectimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(sectimer_Resolution <= 8u) /* 8-bit Timer */
        #define sectimer_CAPTURE_LSB         (* (reg8 *) sectimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define sectimer_CAPTURE_LSB_PTR       ((reg8 *) sectimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define sectimer_PERIOD_LSB          (* (reg8 *) sectimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define sectimer_PERIOD_LSB_PTR        ((reg8 *) sectimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define sectimer_COUNTER_LSB         (* (reg8 *) sectimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define sectimer_COUNTER_LSB_PTR       ((reg8 *) sectimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(sectimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define sectimer_CAPTURE_LSB         (* (reg16 *) sectimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define sectimer_CAPTURE_LSB_PTR       ((reg16 *) sectimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define sectimer_PERIOD_LSB          (* (reg16 *) sectimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define sectimer_PERIOD_LSB_PTR        ((reg16 *) sectimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define sectimer_COUNTER_LSB         (* (reg16 *) sectimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define sectimer_COUNTER_LSB_PTR       ((reg16 *) sectimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define sectimer_CAPTURE_LSB         (* (reg16 *) sectimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define sectimer_CAPTURE_LSB_PTR       ((reg16 *) sectimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define sectimer_PERIOD_LSB          (* (reg16 *) sectimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define sectimer_PERIOD_LSB_PTR        ((reg16 *) sectimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define sectimer_COUNTER_LSB         (* (reg16 *) sectimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define sectimer_COUNTER_LSB_PTR       ((reg16 *) sectimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(sectimer_Resolution <= 24u)/* 24-bit Timer */
        #define sectimer_CAPTURE_LSB         (* (reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define sectimer_CAPTURE_LSB_PTR       ((reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define sectimer_PERIOD_LSB          (* (reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define sectimer_PERIOD_LSB_PTR        ((reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define sectimer_COUNTER_LSB         (* (reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define sectimer_COUNTER_LSB_PTR       ((reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define sectimer_CAPTURE_LSB         (* (reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define sectimer_CAPTURE_LSB_PTR       ((reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define sectimer_PERIOD_LSB          (* (reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define sectimer_PERIOD_LSB_PTR        ((reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define sectimer_COUNTER_LSB         (* (reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define sectimer_COUNTER_LSB_PTR       ((reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define sectimer_CAPTURE_LSB         (* (reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define sectimer_CAPTURE_LSB_PTR       ((reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define sectimer_PERIOD_LSB          (* (reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define sectimer_PERIOD_LSB_PTR        ((reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define sectimer_COUNTER_LSB         (* (reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define sectimer_COUNTER_LSB_PTR       ((reg32 *) sectimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define sectimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) sectimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (sectimer_UsingHWCaptureCounter)
        #define sectimer_CAP_COUNT              (*(reg8 *) sectimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define sectimer_CAP_COUNT_PTR          ( (reg8 *) sectimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define sectimer_CAPTURE_COUNT_CTRL     (*(reg8 *) sectimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define sectimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) sectimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (sectimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define sectimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define sectimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define sectimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define sectimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define sectimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define sectimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << sectimer_CTRL_INTCNT_SHIFT))
    #define sectimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << sectimer_CTRL_TRIG_MODE_SHIFT))
    #define sectimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << sectimer_CTRL_TRIG_EN_SHIFT))
    #define sectimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << sectimer_CTRL_CAP_MODE_SHIFT))
    #define sectimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << sectimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define sectimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define sectimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define sectimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define sectimer_STATUS_TC_INT_MASK_SHIFT       sectimer_STATUS_TC_SHIFT
    #define sectimer_STATUS_CAPTURE_INT_MASK_SHIFT  sectimer_STATUS_CAPTURE_SHIFT
    #define sectimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define sectimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define sectimer_STATUS_FIFOFULL_INT_MASK_SHIFT sectimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define sectimer_STATUS_TC                      ((uint8)((uint8)0x01u << sectimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define sectimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << sectimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define sectimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << sectimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define sectimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << sectimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define sectimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << sectimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define sectimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << sectimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define sectimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << sectimer_STATUS_FIFOFULL_SHIFT))

    #define sectimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define sectimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define sectimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define sectimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define sectimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define sectimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_sectimer_H */


/* [] END OF FILE */
