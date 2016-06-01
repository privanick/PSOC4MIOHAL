/*******************************************************************************
* File Name: flow.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the flow
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_flow_H)
#define CY_TCPWM_flow_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} flow_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  flow_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define flow_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define flow_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define flow_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define flow_QUAD_ENCODING_MODES            (0lu)
#define flow_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define flow_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define flow_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define flow_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define flow_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define flow_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define flow_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define flow_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define flow_TC_RUN_MODE                    (0lu)
#define flow_TC_COUNTER_MODE                (0lu)
#define flow_TC_COMP_CAP_MODE               (2lu)
#define flow_TC_PRESCALER                   (0lu)

/* Signal modes */
#define flow_TC_RELOAD_SIGNAL_MODE          (0lu)
#define flow_TC_COUNT_SIGNAL_MODE           (0lu)
#define flow_TC_START_SIGNAL_MODE           (0lu)
#define flow_TC_STOP_SIGNAL_MODE            (0lu)
#define flow_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define flow_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define flow_TC_COUNT_SIGNAL_PRESENT        (1lu)
#define flow_TC_START_SIGNAL_PRESENT        (0lu)
#define flow_TC_STOP_SIGNAL_PRESENT         (0lu)
#define flow_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define flow_TC_INTERRUPT_MASK              (0lu)

/* PWM Mode */
/* Parameters */
#define flow_PWM_KILL_EVENT                 (0lu)
#define flow_PWM_STOP_EVENT                 (0lu)
#define flow_PWM_MODE                       (4lu)
#define flow_PWM_OUT_N_INVERT               (0lu)
#define flow_PWM_OUT_INVERT                 (0lu)
#define flow_PWM_ALIGN                      (0lu)
#define flow_PWM_RUN_MODE                   (0lu)
#define flow_PWM_DEAD_TIME_CYCLE            (0lu)
#define flow_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define flow_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define flow_PWM_COUNT_SIGNAL_MODE          (3lu)
#define flow_PWM_START_SIGNAL_MODE          (0lu)
#define flow_PWM_STOP_SIGNAL_MODE           (0lu)
#define flow_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define flow_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define flow_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define flow_PWM_START_SIGNAL_PRESENT       (0lu)
#define flow_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define flow_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define flow_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define flow_TC_PERIOD_VALUE                (65535lu)
#define flow_TC_COMPARE_VALUE               (65535lu)
#define flow_TC_COMPARE_BUF_VALUE           (65535lu)
#define flow_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define flow_PWM_PERIOD_VALUE               (65535lu)
#define flow_PWM_PERIOD_BUF_VALUE           (65535lu)
#define flow_PWM_PERIOD_SWAP                (0lu)
#define flow_PWM_COMPARE_VALUE              (65535lu)
#define flow_PWM_COMPARE_BUF_VALUE          (65535lu)
#define flow_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define flow__LEFT 0
#define flow__RIGHT 1
#define flow__CENTER 2
#define flow__ASYMMETRIC 3

#define flow__X1 0
#define flow__X2 1
#define flow__X4 2

#define flow__PWM 4
#define flow__PWM_DT 5
#define flow__PWM_PR 6

#define flow__INVERSE 1
#define flow__DIRECT 0

#define flow__CAPTURE 2
#define flow__COMPARE 0

#define flow__TRIG_LEVEL 3
#define flow__TRIG_RISING 0
#define flow__TRIG_FALLING 1
#define flow__TRIG_BOTH 2

#define flow__INTR_MASK_TC 1
#define flow__INTR_MASK_CC_MATCH 2
#define flow__INTR_MASK_NONE 0
#define flow__INTR_MASK_TC_CC 3

#define flow__UNCONFIG 8
#define flow__TIMER 1
#define flow__QUAD 3
#define flow__PWM_SEL 7

#define flow__COUNT_UP 0
#define flow__COUNT_DOWN 1
#define flow__COUNT_UPDOWN0 2
#define flow__COUNT_UPDOWN1 3


/* Prescaler */
#define flow_PRESCALE_DIVBY1                ((uint32)(0u << flow_PRESCALER_SHIFT))
#define flow_PRESCALE_DIVBY2                ((uint32)(1u << flow_PRESCALER_SHIFT))
#define flow_PRESCALE_DIVBY4                ((uint32)(2u << flow_PRESCALER_SHIFT))
#define flow_PRESCALE_DIVBY8                ((uint32)(3u << flow_PRESCALER_SHIFT))
#define flow_PRESCALE_DIVBY16               ((uint32)(4u << flow_PRESCALER_SHIFT))
#define flow_PRESCALE_DIVBY32               ((uint32)(5u << flow_PRESCALER_SHIFT))
#define flow_PRESCALE_DIVBY64               ((uint32)(6u << flow_PRESCALER_SHIFT))
#define flow_PRESCALE_DIVBY128              ((uint32)(7u << flow_PRESCALER_SHIFT))

/* TCPWM set modes */
#define flow_MODE_TIMER_COMPARE             ((uint32)(flow__COMPARE         <<  \
                                                                  flow_MODE_SHIFT))
#define flow_MODE_TIMER_CAPTURE             ((uint32)(flow__CAPTURE         <<  \
                                                                  flow_MODE_SHIFT))
#define flow_MODE_QUAD                      ((uint32)(flow__QUAD            <<  \
                                                                  flow_MODE_SHIFT))
#define flow_MODE_PWM                       ((uint32)(flow__PWM             <<  \
                                                                  flow_MODE_SHIFT))
#define flow_MODE_PWM_DT                    ((uint32)(flow__PWM_DT          <<  \
                                                                  flow_MODE_SHIFT))
#define flow_MODE_PWM_PR                    ((uint32)(flow__PWM_PR          <<  \
                                                                  flow_MODE_SHIFT))

/* Quad Modes */
#define flow_MODE_X1                        ((uint32)(flow__X1              <<  \
                                                                  flow_QUAD_MODE_SHIFT))
#define flow_MODE_X2                        ((uint32)(flow__X2              <<  \
                                                                  flow_QUAD_MODE_SHIFT))
#define flow_MODE_X4                        ((uint32)(flow__X4              <<  \
                                                                  flow_QUAD_MODE_SHIFT))

/* Counter modes */
#define flow_COUNT_UP                       ((uint32)(flow__COUNT_UP        <<  \
                                                                  flow_UPDOWN_SHIFT))
#define flow_COUNT_DOWN                     ((uint32)(flow__COUNT_DOWN      <<  \
                                                                  flow_UPDOWN_SHIFT))
#define flow_COUNT_UPDOWN0                  ((uint32)(flow__COUNT_UPDOWN0   <<  \
                                                                  flow_UPDOWN_SHIFT))
#define flow_COUNT_UPDOWN1                  ((uint32)(flow__COUNT_UPDOWN1   <<  \
                                                                  flow_UPDOWN_SHIFT))

/* PWM output invert */
#define flow_INVERT_LINE                    ((uint32)(flow__INVERSE         <<  \
                                                                  flow_INV_OUT_SHIFT))
#define flow_INVERT_LINE_N                  ((uint32)(flow__INVERSE         <<  \
                                                                  flow_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define flow_TRIG_RISING                    ((uint32)flow__TRIG_RISING)
#define flow_TRIG_FALLING                   ((uint32)flow__TRIG_FALLING)
#define flow_TRIG_BOTH                      ((uint32)flow__TRIG_BOTH)
#define flow_TRIG_LEVEL                     ((uint32)flow__TRIG_LEVEL)

/* Interrupt mask */
#define flow_INTR_MASK_TC                   ((uint32)flow__INTR_MASK_TC)
#define flow_INTR_MASK_CC_MATCH             ((uint32)flow__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define flow_CC_MATCH_SET                   (0x00u)
#define flow_CC_MATCH_CLEAR                 (0x01u)
#define flow_CC_MATCH_INVERT                (0x02u)
#define flow_CC_MATCH_NO_CHANGE             (0x03u)
#define flow_OVERLOW_SET                    (0x00u)
#define flow_OVERLOW_CLEAR                  (0x04u)
#define flow_OVERLOW_INVERT                 (0x08u)
#define flow_OVERLOW_NO_CHANGE              (0x0Cu)
#define flow_UNDERFLOW_SET                  (0x00u)
#define flow_UNDERFLOW_CLEAR                (0x10u)
#define flow_UNDERFLOW_INVERT               (0x20u)
#define flow_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define flow_PWM_MODE_LEFT                  (flow_CC_MATCH_CLEAR        |   \
                                                         flow_OVERLOW_SET           |   \
                                                         flow_UNDERFLOW_NO_CHANGE)
#define flow_PWM_MODE_RIGHT                 (flow_CC_MATCH_SET          |   \
                                                         flow_OVERLOW_NO_CHANGE     |   \
                                                         flow_UNDERFLOW_CLEAR)
#define flow_PWM_MODE_ASYM                  (flow_CC_MATCH_INVERT       |   \
                                                         flow_OVERLOW_SET           |   \
                                                         flow_UNDERFLOW_CLEAR)

#if (flow_CY_TCPWM_V2)
    #if(flow_CY_TCPWM_4000)
        #define flow_PWM_MODE_CENTER                (flow_CC_MATCH_INVERT       |   \
                                                                 flow_OVERLOW_NO_CHANGE     |   \
                                                                 flow_UNDERFLOW_CLEAR)
    #else
        #define flow_PWM_MODE_CENTER                (flow_CC_MATCH_INVERT       |   \
                                                                 flow_OVERLOW_SET           |   \
                                                                 flow_UNDERFLOW_CLEAR)
    #endif /* (flow_CY_TCPWM_4000) */
#else
    #define flow_PWM_MODE_CENTER                (flow_CC_MATCH_INVERT       |   \
                                                             flow_OVERLOW_NO_CHANGE     |   \
                                                             flow_UNDERFLOW_CLEAR)
#endif /* (flow_CY_TCPWM_NEW) */

/* Command operations without condition */
#define flow_CMD_CAPTURE                    (0u)
#define flow_CMD_RELOAD                     (8u)
#define flow_CMD_STOP                       (16u)
#define flow_CMD_START                      (24u)

/* Status */
#define flow_STATUS_DOWN                    (1u)
#define flow_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   flow_Init(void);
void   flow_Enable(void);
void   flow_Start(void);
void   flow_Stop(void);

void   flow_SetMode(uint32 mode);
void   flow_SetCounterMode(uint32 counterMode);
void   flow_SetPWMMode(uint32 modeMask);
void   flow_SetQDMode(uint32 qdMode);

void   flow_SetPrescaler(uint32 prescaler);
void   flow_TriggerCommand(uint32 mask, uint32 command);
void   flow_SetOneShot(uint32 oneShotEnable);
uint32 flow_ReadStatus(void);

void   flow_SetPWMSyncKill(uint32 syncKillEnable);
void   flow_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   flow_SetPWMDeadTime(uint32 deadTime);
void   flow_SetPWMInvert(uint32 mask);

void   flow_SetInterruptMode(uint32 interruptMask);
uint32 flow_GetInterruptSourceMasked(void);
uint32 flow_GetInterruptSource(void);
void   flow_ClearInterrupt(uint32 interruptMask);
void   flow_SetInterrupt(uint32 interruptMask);

void   flow_WriteCounter(uint32 count);
uint32 flow_ReadCounter(void);

uint32 flow_ReadCapture(void);
uint32 flow_ReadCaptureBuf(void);

void   flow_WritePeriod(uint32 period);
uint32 flow_ReadPeriod(void);
void   flow_WritePeriodBuf(uint32 periodBuf);
uint32 flow_ReadPeriodBuf(void);

void   flow_WriteCompare(uint32 compare);
uint32 flow_ReadCompare(void);
void   flow_WriteCompareBuf(uint32 compareBuf);
uint32 flow_ReadCompareBuf(void);

void   flow_SetPeriodSwap(uint32 swapEnable);
void   flow_SetCompareSwap(uint32 swapEnable);

void   flow_SetCaptureMode(uint32 triggerMode);
void   flow_SetReloadMode(uint32 triggerMode);
void   flow_SetStartMode(uint32 triggerMode);
void   flow_SetStopMode(uint32 triggerMode);
void   flow_SetCountMode(uint32 triggerMode);

void   flow_SaveConfig(void);
void   flow_RestoreConfig(void);
void   flow_Sleep(void);
void   flow_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define flow_BLOCK_CONTROL_REG              (*(reg32 *) flow_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define flow_BLOCK_CONTROL_PTR              ( (reg32 *) flow_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define flow_COMMAND_REG                    (*(reg32 *) flow_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define flow_COMMAND_PTR                    ( (reg32 *) flow_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define flow_INTRRUPT_CAUSE_REG             (*(reg32 *) flow_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define flow_INTRRUPT_CAUSE_PTR             ( (reg32 *) flow_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define flow_CONTROL_REG                    (*(reg32 *) flow_cy_m0s8_tcpwm_1__CTRL )
#define flow_CONTROL_PTR                    ( (reg32 *) flow_cy_m0s8_tcpwm_1__CTRL )
#define flow_STATUS_REG                     (*(reg32 *) flow_cy_m0s8_tcpwm_1__STATUS )
#define flow_STATUS_PTR                     ( (reg32 *) flow_cy_m0s8_tcpwm_1__STATUS )
#define flow_COUNTER_REG                    (*(reg32 *) flow_cy_m0s8_tcpwm_1__COUNTER )
#define flow_COUNTER_PTR                    ( (reg32 *) flow_cy_m0s8_tcpwm_1__COUNTER )
#define flow_COMP_CAP_REG                   (*(reg32 *) flow_cy_m0s8_tcpwm_1__CC )
#define flow_COMP_CAP_PTR                   ( (reg32 *) flow_cy_m0s8_tcpwm_1__CC )
#define flow_COMP_CAP_BUF_REG               (*(reg32 *) flow_cy_m0s8_tcpwm_1__CC_BUFF )
#define flow_COMP_CAP_BUF_PTR               ( (reg32 *) flow_cy_m0s8_tcpwm_1__CC_BUFF )
#define flow_PERIOD_REG                     (*(reg32 *) flow_cy_m0s8_tcpwm_1__PERIOD )
#define flow_PERIOD_PTR                     ( (reg32 *) flow_cy_m0s8_tcpwm_1__PERIOD )
#define flow_PERIOD_BUF_REG                 (*(reg32 *) flow_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define flow_PERIOD_BUF_PTR                 ( (reg32 *) flow_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define flow_TRIG_CONTROL0_REG              (*(reg32 *) flow_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define flow_TRIG_CONTROL0_PTR              ( (reg32 *) flow_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define flow_TRIG_CONTROL1_REG              (*(reg32 *) flow_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define flow_TRIG_CONTROL1_PTR              ( (reg32 *) flow_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define flow_TRIG_CONTROL2_REG              (*(reg32 *) flow_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define flow_TRIG_CONTROL2_PTR              ( (reg32 *) flow_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define flow_INTERRUPT_REQ_REG              (*(reg32 *) flow_cy_m0s8_tcpwm_1__INTR )
#define flow_INTERRUPT_REQ_PTR              ( (reg32 *) flow_cy_m0s8_tcpwm_1__INTR )
#define flow_INTERRUPT_SET_REG              (*(reg32 *) flow_cy_m0s8_tcpwm_1__INTR_SET )
#define flow_INTERRUPT_SET_PTR              ( (reg32 *) flow_cy_m0s8_tcpwm_1__INTR_SET )
#define flow_INTERRUPT_MASK_REG             (*(reg32 *) flow_cy_m0s8_tcpwm_1__INTR_MASK )
#define flow_INTERRUPT_MASK_PTR             ( (reg32 *) flow_cy_m0s8_tcpwm_1__INTR_MASK )
#define flow_INTERRUPT_MASKED_REG           (*(reg32 *) flow_cy_m0s8_tcpwm_1__INTR_MASKED )
#define flow_INTERRUPT_MASKED_PTR           ( (reg32 *) flow_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define flow_MASK                           ((uint32)flow_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define flow_RELOAD_CC_SHIFT                (0u)
#define flow_RELOAD_PERIOD_SHIFT            (1u)
#define flow_PWM_SYNC_KILL_SHIFT            (2u)
#define flow_PWM_STOP_KILL_SHIFT            (3u)
#define flow_PRESCALER_SHIFT                (8u)
#define flow_UPDOWN_SHIFT                   (16u)
#define flow_ONESHOT_SHIFT                  (18u)
#define flow_QUAD_MODE_SHIFT                (20u)
#define flow_INV_OUT_SHIFT                  (20u)
#define flow_INV_COMPL_OUT_SHIFT            (21u)
#define flow_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define flow_RELOAD_CC_MASK                 ((uint32)(flow_1BIT_MASK        <<  \
                                                                            flow_RELOAD_CC_SHIFT))
#define flow_RELOAD_PERIOD_MASK             ((uint32)(flow_1BIT_MASK        <<  \
                                                                            flow_RELOAD_PERIOD_SHIFT))
#define flow_PWM_SYNC_KILL_MASK             ((uint32)(flow_1BIT_MASK        <<  \
                                                                            flow_PWM_SYNC_KILL_SHIFT))
#define flow_PWM_STOP_KILL_MASK             ((uint32)(flow_1BIT_MASK        <<  \
                                                                            flow_PWM_STOP_KILL_SHIFT))
#define flow_PRESCALER_MASK                 ((uint32)(flow_8BIT_MASK        <<  \
                                                                            flow_PRESCALER_SHIFT))
#define flow_UPDOWN_MASK                    ((uint32)(flow_2BIT_MASK        <<  \
                                                                            flow_UPDOWN_SHIFT))
#define flow_ONESHOT_MASK                   ((uint32)(flow_1BIT_MASK        <<  \
                                                                            flow_ONESHOT_SHIFT))
#define flow_QUAD_MODE_MASK                 ((uint32)(flow_3BIT_MASK        <<  \
                                                                            flow_QUAD_MODE_SHIFT))
#define flow_INV_OUT_MASK                   ((uint32)(flow_2BIT_MASK        <<  \
                                                                            flow_INV_OUT_SHIFT))
#define flow_MODE_MASK                      ((uint32)(flow_3BIT_MASK        <<  \
                                                                            flow_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define flow_CAPTURE_SHIFT                  (0u)
#define flow_COUNT_SHIFT                    (2u)
#define flow_RELOAD_SHIFT                   (4u)
#define flow_STOP_SHIFT                     (6u)
#define flow_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define flow_CAPTURE_MASK                   ((uint32)(flow_2BIT_MASK        <<  \
                                                                  flow_CAPTURE_SHIFT))
#define flow_COUNT_MASK                     ((uint32)(flow_2BIT_MASK        <<  \
                                                                  flow_COUNT_SHIFT))
#define flow_RELOAD_MASK                    ((uint32)(flow_2BIT_MASK        <<  \
                                                                  flow_RELOAD_SHIFT))
#define flow_STOP_MASK                      ((uint32)(flow_2BIT_MASK        <<  \
                                                                  flow_STOP_SHIFT))
#define flow_START_MASK                     ((uint32)(flow_2BIT_MASK        <<  \
                                                                  flow_START_SHIFT))

/* MASK */
#define flow_1BIT_MASK                      ((uint32)0x01u)
#define flow_2BIT_MASK                      ((uint32)0x03u)
#define flow_3BIT_MASK                      ((uint32)0x07u)
#define flow_6BIT_MASK                      ((uint32)0x3Fu)
#define flow_8BIT_MASK                      ((uint32)0xFFu)
#define flow_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define flow_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define flow_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(flow_QUAD_ENCODING_MODES     << flow_QUAD_MODE_SHIFT))       |\
         ((uint32)(flow_CONFIG                  << flow_MODE_SHIFT)))

#define flow_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(flow_PWM_STOP_EVENT          << flow_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(flow_PWM_OUT_INVERT          << flow_INV_OUT_SHIFT))         |\
         ((uint32)(flow_PWM_OUT_N_INVERT        << flow_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(flow_PWM_MODE                << flow_MODE_SHIFT)))

#define flow_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(flow_PWM_RUN_MODE         << flow_ONESHOT_SHIFT))
            
#define flow_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(flow_PWM_ALIGN            << flow_UPDOWN_SHIFT))

#define flow_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(flow_PWM_KILL_EVENT      << flow_PWM_SYNC_KILL_SHIFT))

#define flow_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(flow_PWM_DEAD_TIME_CYCLE  << flow_PRESCALER_SHIFT))

#define flow_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(flow_PWM_PRESCALER        << flow_PRESCALER_SHIFT))

#define flow_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(flow_TC_PRESCALER            << flow_PRESCALER_SHIFT))       |\
         ((uint32)(flow_TC_COUNTER_MODE         << flow_UPDOWN_SHIFT))          |\
         ((uint32)(flow_TC_RUN_MODE             << flow_ONESHOT_SHIFT))         |\
         ((uint32)(flow_TC_COMP_CAP_MODE        << flow_MODE_SHIFT)))
        
#define flow_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(flow_QUAD_PHIA_SIGNAL_MODE   << flow_COUNT_SHIFT))           |\
         ((uint32)(flow_QUAD_INDEX_SIGNAL_MODE  << flow_RELOAD_SHIFT))          |\
         ((uint32)(flow_QUAD_STOP_SIGNAL_MODE   << flow_STOP_SHIFT))            |\
         ((uint32)(flow_QUAD_PHIB_SIGNAL_MODE   << flow_START_SHIFT)))

#define flow_PWM_SIGNALS_MODES                                                              \
        (((uint32)(flow_PWM_SWITCH_SIGNAL_MODE  << flow_CAPTURE_SHIFT))         |\
         ((uint32)(flow_PWM_COUNT_SIGNAL_MODE   << flow_COUNT_SHIFT))           |\
         ((uint32)(flow_PWM_RELOAD_SIGNAL_MODE  << flow_RELOAD_SHIFT))          |\
         ((uint32)(flow_PWM_STOP_SIGNAL_MODE    << flow_STOP_SHIFT))            |\
         ((uint32)(flow_PWM_START_SIGNAL_MODE   << flow_START_SHIFT)))

#define flow_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(flow_TC_CAPTURE_SIGNAL_MODE  << flow_CAPTURE_SHIFT))         |\
         ((uint32)(flow_TC_COUNT_SIGNAL_MODE    << flow_COUNT_SHIFT))           |\
         ((uint32)(flow_TC_RELOAD_SIGNAL_MODE   << flow_RELOAD_SHIFT))          |\
         ((uint32)(flow_TC_STOP_SIGNAL_MODE     << flow_STOP_SHIFT))            |\
         ((uint32)(flow_TC_START_SIGNAL_MODE    << flow_START_SHIFT)))
        
#define flow_TIMER_UPDOWN_CNT_USED                                                          \
                ((flow__COUNT_UPDOWN0 == flow_TC_COUNTER_MODE)                  ||\
                 (flow__COUNT_UPDOWN1 == flow_TC_COUNTER_MODE))

#define flow_PWM_UPDOWN_CNT_USED                                                            \
                ((flow__CENTER == flow_PWM_ALIGN)                               ||\
                 (flow__ASYMMETRIC == flow_PWM_ALIGN))               
        
#define flow_PWM_PR_INIT_VALUE              (1u)
#define flow_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_flow_H */

/* [] END OF FILE */
