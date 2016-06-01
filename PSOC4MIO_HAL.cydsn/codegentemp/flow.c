/*******************************************************************************
* File Name: flow.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the flow
*  component
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

#include "flow.h"

uint8 flow_initVar = 0u;


/*******************************************************************************
* Function Name: flow_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default flow configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void flow_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (flow__QUAD == flow_CONFIG)
        flow_CONTROL_REG = flow_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        flow_TRIG_CONTROL1_REG  = flow_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        flow_SetInterruptMode(flow_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        flow_SetCounterMode(flow_COUNT_DOWN);
        flow_WritePeriod(flow_QUAD_PERIOD_INIT_VALUE);
        flow_WriteCounter(flow_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (flow__QUAD == flow_CONFIG) */

    #if (flow__TIMER == flow_CONFIG)
        flow_CONTROL_REG = flow_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        flow_TRIG_CONTROL1_REG  = flow_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        flow_SetInterruptMode(flow_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        flow_WritePeriod(flow_TC_PERIOD_VALUE );

        #if (flow__COMPARE == flow_TC_COMP_CAP_MODE)
            flow_WriteCompare(flow_TC_COMPARE_VALUE);

            #if (1u == flow_TC_COMPARE_SWAP)
                flow_SetCompareSwap(1u);
                flow_WriteCompareBuf(flow_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == flow_TC_COMPARE_SWAP) */
        #endif  /* (flow__COMPARE == flow_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (flow_CY_TCPWM_V2 && flow_TIMER_UPDOWN_CNT_USED && !flow_CY_TCPWM_4000)
            flow_WriteCounter(1u);
        #elif(flow__COUNT_DOWN == flow_TC_COUNTER_MODE)
            flow_WriteCounter(flow_TC_PERIOD_VALUE);
        #else
            flow_WriteCounter(0u);
        #endif /* (flow_CY_TCPWM_V2 && flow_TIMER_UPDOWN_CNT_USED && !flow_CY_TCPWM_4000) */
    #endif  /* (flow__TIMER == flow_CONFIG) */

    #if (flow__PWM_SEL == flow_CONFIG)
        flow_CONTROL_REG = flow_CTRL_PWM_BASE_CONFIG;

        #if (flow__PWM_PR == flow_PWM_MODE)
            flow_CONTROL_REG |= flow_CTRL_PWM_RUN_MODE;
            flow_WriteCounter(flow_PWM_PR_INIT_VALUE);
        #else
            flow_CONTROL_REG |= flow_CTRL_PWM_ALIGN | flow_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (flow_CY_TCPWM_V2 && flow_PWM_UPDOWN_CNT_USED && !flow_CY_TCPWM_4000)
                flow_WriteCounter(1u);
            #elif (flow__RIGHT == flow_PWM_ALIGN)
                flow_WriteCounter(flow_PWM_PERIOD_VALUE);
            #else 
                flow_WriteCounter(0u);
            #endif  /* (flow_CY_TCPWM_V2 && flow_PWM_UPDOWN_CNT_USED && !flow_CY_TCPWM_4000) */
        #endif  /* (flow__PWM_PR == flow_PWM_MODE) */

        #if (flow__PWM_DT == flow_PWM_MODE)
            flow_CONTROL_REG |= flow_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (flow__PWM_DT == flow_PWM_MODE) */

        #if (flow__PWM == flow_PWM_MODE)
            flow_CONTROL_REG |= flow_CTRL_PWM_PRESCALER;
        #endif  /* (flow__PWM == flow_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        flow_TRIG_CONTROL1_REG  = flow_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        flow_SetInterruptMode(flow_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (flow__PWM_PR == flow_PWM_MODE)
            flow_TRIG_CONTROL2_REG =
                    (flow_CC_MATCH_NO_CHANGE    |
                    flow_OVERLOW_NO_CHANGE      |
                    flow_UNDERFLOW_NO_CHANGE);
        #else
            #if (flow__LEFT == flow_PWM_ALIGN)
                flow_TRIG_CONTROL2_REG = flow_PWM_MODE_LEFT;
            #endif  /* ( flow_PWM_LEFT == flow_PWM_ALIGN) */

            #if (flow__RIGHT == flow_PWM_ALIGN)
                flow_TRIG_CONTROL2_REG = flow_PWM_MODE_RIGHT;
            #endif  /* ( flow_PWM_RIGHT == flow_PWM_ALIGN) */

            #if (flow__CENTER == flow_PWM_ALIGN)
                flow_TRIG_CONTROL2_REG = flow_PWM_MODE_CENTER;
            #endif  /* ( flow_PWM_CENTER == flow_PWM_ALIGN) */

            #if (flow__ASYMMETRIC == flow_PWM_ALIGN)
                flow_TRIG_CONTROL2_REG = flow_PWM_MODE_ASYM;
            #endif  /* (flow__ASYMMETRIC == flow_PWM_ALIGN) */
        #endif  /* (flow__PWM_PR == flow_PWM_MODE) */

        /* Set other values from customizer */
        flow_WritePeriod(flow_PWM_PERIOD_VALUE );
        flow_WriteCompare(flow_PWM_COMPARE_VALUE);

        #if (1u == flow_PWM_COMPARE_SWAP)
            flow_SetCompareSwap(1u);
            flow_WriteCompareBuf(flow_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == flow_PWM_COMPARE_SWAP) */

        #if (1u == flow_PWM_PERIOD_SWAP)
            flow_SetPeriodSwap(1u);
            flow_WritePeriodBuf(flow_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == flow_PWM_PERIOD_SWAP) */
    #endif  /* (flow__PWM_SEL == flow_CONFIG) */
    
}


/*******************************************************************************
* Function Name: flow_Enable
********************************************************************************
*
* Summary:
*  Enables the flow.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void flow_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    flow_BLOCK_CONTROL_REG |= flow_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (flow__PWM_SEL == flow_CONFIG)
        #if (0u == flow_PWM_START_SIGNAL_PRESENT)
            flow_TriggerCommand(flow_MASK, flow_CMD_START);
        #endif /* (0u == flow_PWM_START_SIGNAL_PRESENT) */
    #endif /* (flow__PWM_SEL == flow_CONFIG) */

    #if (flow__TIMER == flow_CONFIG)
        #if (0u == flow_TC_START_SIGNAL_PRESENT)
            flow_TriggerCommand(flow_MASK, flow_CMD_START);
        #endif /* (0u == flow_TC_START_SIGNAL_PRESENT) */
    #endif /* (flow__TIMER == flow_CONFIG) */
    
    #if (flow__QUAD == flow_CONFIG)
        #if (0u != flow_QUAD_AUTO_START)
            flow_TriggerCommand(flow_MASK, flow_CMD_RELOAD);
        #endif /* (0u != flow_QUAD_AUTO_START) */
    #endif  /* (flow__QUAD == flow_CONFIG) */
}


/*******************************************************************************
* Function Name: flow_Start
********************************************************************************
*
* Summary:
*  Initializes the flow with default customizer
*  values when called the first time and enables the flow.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  flow_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time flow_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the flow_Start() routine.
*
*******************************************************************************/
void flow_Start(void)
{
    if (0u == flow_initVar)
    {
        flow_Init();
        flow_initVar = 1u;
    }

    flow_Enable();
}


/*******************************************************************************
* Function Name: flow_Stop
********************************************************************************
*
* Summary:
*  Disables the flow.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void flow_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_BLOCK_CONTROL_REG &= (uint32)~flow_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the flow. This function is used when
*  configured as a generic flow and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the flow to operate in
*   Values:
*   - flow_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - flow_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - flow_MODE_QUAD - Quadrature decoder
*         - flow_MODE_PWM - PWM
*         - flow_MODE_PWM_DT - PWM with dead time
*         - flow_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_CONTROL_REG &= (uint32)~flow_MODE_MASK;
    flow_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - flow_MODE_X1 - Counts on phi 1 rising
*         - flow_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - flow_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_CONTROL_REG &= (uint32)~flow_QUAD_MODE_MASK;
    flow_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - flow_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - flow_PRESCALE_DIVBY2    - Divide by 2
*         - flow_PRESCALE_DIVBY4    - Divide by 4
*         - flow_PRESCALE_DIVBY8    - Divide by 8
*         - flow_PRESCALE_DIVBY16   - Divide by 16
*         - flow_PRESCALE_DIVBY32   - Divide by 32
*         - flow_PRESCALE_DIVBY64   - Divide by 64
*         - flow_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_CONTROL_REG &= (uint32)~flow_PRESCALER_MASK;
    flow_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the flow runs
*  continuously or stops when terminal count is reached.  By default the
*  flow operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_CONTROL_REG &= (uint32)~flow_ONESHOT_MASK;
    flow_CONTROL_REG |= ((uint32)((oneShotEnable & flow_1BIT_MASK) <<
                                                               flow_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetPWMMode(uint32 modeMask)
{
    flow_TRIG_CONTROL2_REG = (modeMask & flow_6BIT_MASK);
}



/*******************************************************************************
* Function Name: flow_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_CONTROL_REG &= (uint32)~flow_PWM_SYNC_KILL_MASK;
    flow_CONTROL_REG |= ((uint32)((syncKillEnable & flow_1BIT_MASK)  <<
                                               flow_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_CONTROL_REG &= (uint32)~flow_PWM_STOP_KILL_MASK;
    flow_CONTROL_REG |= ((uint32)((stopOnKillEnable & flow_1BIT_MASK)  <<
                                                         flow_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_CONTROL_REG &= (uint32)~flow_PRESCALER_MASK;
    flow_CONTROL_REG |= ((uint32)((deadTime & flow_8BIT_MASK) <<
                                                          flow_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - flow_INVERT_LINE   - Inverts the line output
*         - flow_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_CONTROL_REG &= (uint32)~flow_INV_OUT_MASK;
    flow_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: flow_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void flow_WriteCounter(uint32 count)
{
    flow_COUNTER_REG = (count & flow_16BIT_MASK);
}


/*******************************************************************************
* Function Name: flow_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 flow_ReadCounter(void)
{
    return (flow_COUNTER_REG & flow_16BIT_MASK);
}


/*******************************************************************************
* Function Name: flow_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - flow_COUNT_UP       - Counts up
*     - flow_COUNT_DOWN     - Counts down
*     - flow_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - flow_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_CONTROL_REG &= (uint32)~flow_UPDOWN_MASK;
    flow_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void flow_WritePeriod(uint32 period)
{
    flow_PERIOD_REG = (period & flow_16BIT_MASK);
}


/*******************************************************************************
* Function Name: flow_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 flow_ReadPeriod(void)
{
    return (flow_PERIOD_REG & flow_16BIT_MASK);
}


/*******************************************************************************
* Function Name: flow_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_CONTROL_REG &= (uint32)~flow_RELOAD_CC_MASK;
    flow_CONTROL_REG |= (swapEnable & flow_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void flow_WritePeriodBuf(uint32 periodBuf)
{
    flow_PERIOD_BUF_REG = (periodBuf & flow_16BIT_MASK);
}


/*******************************************************************************
* Function Name: flow_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 flow_ReadPeriodBuf(void)
{
    return (flow_PERIOD_BUF_REG & flow_16BIT_MASK);
}


/*******************************************************************************
* Function Name: flow_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_CONTROL_REG &= (uint32)~flow_RELOAD_PERIOD_MASK;
    flow_CONTROL_REG |= ((uint32)((swapEnable & flow_1BIT_MASK) <<
                                                            flow_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void flow_WriteCompare(uint32 compare)
{
    #if (flow_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (flow_CY_TCPWM_4000) */

    #if (flow_CY_TCPWM_4000)
        currentMode = ((flow_CONTROL_REG & flow_UPDOWN_MASK) >> flow_UPDOWN_SHIFT);

        if (((uint32)flow__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)flow__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (flow_CY_TCPWM_4000) */
    
    flow_COMP_CAP_REG = (compare & flow_16BIT_MASK);
}


/*******************************************************************************
* Function Name: flow_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 flow_ReadCompare(void)
{
    #if (flow_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (flow_CY_TCPWM_4000) */

    #if (flow_CY_TCPWM_4000)
        currentMode = ((flow_CONTROL_REG & flow_UPDOWN_MASK) >> flow_UPDOWN_SHIFT);
        
        regVal = flow_COMP_CAP_REG;
        
        if (((uint32)flow__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)flow__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & flow_16BIT_MASK);
    #else
        return (flow_COMP_CAP_REG & flow_16BIT_MASK);
    #endif /* (flow_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: flow_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void flow_WriteCompareBuf(uint32 compareBuf)
{
    #if (flow_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (flow_CY_TCPWM_4000) */

    #if (flow_CY_TCPWM_4000)
        currentMode = ((flow_CONTROL_REG & flow_UPDOWN_MASK) >> flow_UPDOWN_SHIFT);

        if (((uint32)flow__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)flow__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (flow_CY_TCPWM_4000) */
    
    flow_COMP_CAP_BUF_REG = (compareBuf & flow_16BIT_MASK);
}


/*******************************************************************************
* Function Name: flow_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 flow_ReadCompareBuf(void)
{
    #if (flow_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (flow_CY_TCPWM_4000) */

    #if (flow_CY_TCPWM_4000)
        currentMode = ((flow_CONTROL_REG & flow_UPDOWN_MASK) >> flow_UPDOWN_SHIFT);

        regVal = flow_COMP_CAP_BUF_REG;
        
        if (((uint32)flow__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)flow__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & flow_16BIT_MASK);
    #else
        return (flow_COMP_CAP_BUF_REG & flow_16BIT_MASK);
    #endif /* (flow_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: flow_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 flow_ReadCapture(void)
{
    return (flow_COMP_CAP_REG & flow_16BIT_MASK);
}


/*******************************************************************************
* Function Name: flow_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 flow_ReadCaptureBuf(void)
{
    return (flow_COMP_CAP_BUF_REG & flow_16BIT_MASK);
}


/*******************************************************************************
* Function Name: flow_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - flow_TRIG_LEVEL     - Level
*     - flow_TRIG_RISING    - Rising edge
*     - flow_TRIG_FALLING   - Falling edge
*     - flow_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_TRIG_CONTROL1_REG &= (uint32)~flow_CAPTURE_MASK;
    flow_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - flow_TRIG_LEVEL     - Level
*     - flow_TRIG_RISING    - Rising edge
*     - flow_TRIG_FALLING   - Falling edge
*     - flow_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_TRIG_CONTROL1_REG &= (uint32)~flow_RELOAD_MASK;
    flow_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << flow_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - flow_TRIG_LEVEL     - Level
*     - flow_TRIG_RISING    - Rising edge
*     - flow_TRIG_FALLING   - Falling edge
*     - flow_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_TRIG_CONTROL1_REG &= (uint32)~flow_START_MASK;
    flow_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << flow_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - flow_TRIG_LEVEL     - Level
*     - flow_TRIG_RISING    - Rising edge
*     - flow_TRIG_FALLING   - Falling edge
*     - flow_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_TRIG_CONTROL1_REG &= (uint32)~flow_STOP_MASK;
    flow_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << flow_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - flow_TRIG_LEVEL     - Level
*     - flow_TRIG_RISING    - Rising edge
*     - flow_TRIG_FALLING   - Falling edge
*     - flow_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_TRIG_CONTROL1_REG &= (uint32)~flow_COUNT_MASK;
    flow_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << flow_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - flow_CMD_CAPTURE    - Trigger Capture/Switch command
*     - flow_CMD_RELOAD     - Trigger Reload/Index command
*     - flow_CMD_STOP       - Trigger Stop/Kill command
*     - flow_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void flow_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    flow_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: flow_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the flow.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - flow_STATUS_DOWN    - Set if counting down
*     - flow_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 flow_ReadStatus(void)
{
    return ((flow_STATUS_REG >> flow_RUNNING_STATUS_SHIFT) |
            (flow_STATUS_REG & flow_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: flow_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - flow_INTR_MASK_TC       - Terminal count mask
*     - flow_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetInterruptMode(uint32 interruptMask)
{
    flow_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: flow_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - flow_INTR_MASK_TC       - Terminal count mask
*     - flow_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 flow_GetInterruptSourceMasked(void)
{
    return (flow_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: flow_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - flow_INTR_MASK_TC       - Terminal count mask
*     - flow_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 flow_GetInterruptSource(void)
{
    return (flow_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: flow_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - flow_INTR_MASK_TC       - Terminal count mask
*     - flow_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void flow_ClearInterrupt(uint32 interruptMask)
{
    flow_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: flow_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - flow_INTR_MASK_TC       - Terminal count mask
*     - flow_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void flow_SetInterrupt(uint32 interruptMask)
{
    flow_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
