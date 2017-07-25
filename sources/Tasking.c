//====== Header includes =======================================================
#include "Tasking.h"


//====== Private Constants =====================================================


//====== Private Signals =======================================================
static volatile G_Flag_e L_Task1SEC = Flag_CLEAR;


//====== Private Function Prototypes ===========================================


//====== Private Functions =====================================================


//====== Public Signals ========================================================


//====== Public Functions ======================================================

//******************************************************************************
//****** INTERRUPT HANDLER
//******************************************************************************
ISR(TIMER1_COMPA_vect)
{
    L_Task1SEC = Flag_SET;
}

    
//******************************************************************************
//****** INIT
//******************************************************************************
void Task_Init(void)
{
    MCH__INTERRUPT_DISABLED();

    MCH_InitPins();
    MCH_InitTimer1();
    MCH_InitADC(); 
    MCH_InitWatchdog();
    MCH_InitSleepMode();

    BVM_Init();
    DHT22_Init();
    LCM_Init();

    MCH__INTERRUPT_ENABLED();
}


//******************************************************************************
//****** MAIN
//******************************************************************************
void Task_Main(void)
{
    LCM_Refresh(LCM__WELCOME);

    for (;;)
    {
        MCH__WD_RESET();
        
        if (Flag_SET == L_Task1SEC)
        {

            L_Task1SEC = Flag_CLEAR;

            /***************************************/
            /* Battery */
            /***************************************/
            BVM_Refresh();
            LCM_Refresh(LCM__BATTERY);
            
            /***************************************/
            /* DHT22 */
            /***************************************/
            DHT22_Refresh();
            if (Flag_SET == XDHT22__DATA_UPDATED)
            {
                LCM_Refresh(LCM__DHT22);
            }

        } // Task_1SEC

        MCH__SLEEP();

    } // main end-less loop
} // Task_Main
