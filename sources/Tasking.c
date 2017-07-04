//====== Header includes =======================================================
#include "Tasking.h"


//====== Private Constants =====================================================

// Center coordinates are set to Hungary
#define L__USART_BAUD_RATE   ((uint16) 9600u)


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

/*
ISR(USART_RXC_vect)
{
    GPS_Callback_USART_RXC();
}
*/
    
//******************************************************************************
//****** INIT
//******************************************************************************
void Task_Init(void)
{
    MCH__INTERRUPT_DISABLED();

    MCH_InitPins();
    MCH_InitTimer1();
//    MCH_InitTimer2();
    MCH_InitADC(); 
//    MCH_InitUSART(L__USART_BAUD_RATE);
//    MCH_InitWatchdog();
//    MCH_InitSleepMode();

    LCD_Init();
    LCD_SwitchOn();
    LCD_Clear();
//    DHT22_Init();

//    RTC_SetDate(2000u,1u,1u,1u,Flag_CLEAR,0u,0u,0u);

    MCH__INTERRUPT_ENABLED();
}


//******************************************************************************
//****** MAIN
//******************************************************************************
void Task_Main(void)
{
    uint16   bv_raw  = 42u;
    float32 bv      = 0.0f;

    for (;;)
    {
        if (Flag_SET == L_Task1SEC)
        {
            L_Task1SEC = Flag_CLEAR;

            LCD_Clear();
            bv_raw = MCH_ReadADC(MCH__ADC_CHANNEL_0);

            bv = bv_raw * (5.0f / 1024.0f);
            bv = bv / (100.0f / (100.0f + 330.0f));
            
            LCD_SetCursor(1,3);
            LCD_WriteInt((uint16) (bv));
            LCD_WriteChar('.');
            LCD_WriteInt((uint16) ((bv - (uint16)bv) * 10.0f));
            LCD_WriteChar('V');
            LCD_SetCursor(2,1);
            LCD_WriteInt(bv_raw);
        }

    } // main end-less loop

} // Task_Main
