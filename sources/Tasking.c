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
    DHT22_Init();

    LCD_Init();
    LCD_SwitchOn();
    LCD_Clear();
    
    LCD_StoreCustomChar(1u, LCD_CharBatteryTop);
    LCD_StoreCustomChar(2u, LCD_CharBatteryMiddle0);
    LCD_StoreCustomChar(3u, LCD_CharBatteryMiddle1);
    LCD_StoreCustomChar(4u, LCD_CharBatteryMiddleCharge);
    LCD_StoreCustomChar(5u, LCD_CharBatteryBottom0);

//    RTC_SetDate(2000u,1u,1u,1u,Flag_CLEAR,0u,0u,0u);

    MCH__INTERRUPT_ENABLED();
}

#define L__POS_ROW_DHT22_TEMP   ( 1u)
#define L__POS_COL_DHT22_TEMP   (11u)
#define L__POS_ROW_DHT22_HUM    ( 2u)
#define L__POS_COL_DHT22_HUM    (13u)
#define L__POS_ROW_BATT_VOLT    ( 1u)
#define L__POS_COL_BATT_VOLT    ( 1u)
#define L__POS_ROW_BATT_PERC    ( 2u)
#define L__POS_COL_BATT_PERC    ( 1u)

//******************************************************************************
//****** MAIN
//******************************************************************************
void Task_Main(void)
{
    uint16   bv_raw  = 42u;
    float32 bv      = 0.0f;
    static uint8 ize = 0u;

    for (;;)
    {
        if (Flag_SET == L_Task1SEC)
        {
            L_Task1SEC = Flag_CLEAR;

            LCD_Clear();
           

            LCD_SetCursor(2u, 7u);
            LCD_WriteInt(ize++);

            /*******************************/
            /* TEMPERATURE */
            /*******************************/
            DHT22_Refresh();
            
//            if (Flag_SET == XDHT22__DATA_UPDATED)
//            {
                if (Signal_RELIABLE == XDHT22__DATA_QUALIFIER)
                {
                    LCD_SetCursor(L__POS_ROW_DHT22_TEMP, L__POS_COL_DHT22_TEMP);
                    if (10.0f <= XDHT22__TEMPERATURE_VALUE)
                    {
                        LCD_WriteChar(' ');
                    }
                    else if ((0.0f <= XDHT22__TEMPERATURE_VALUE) && (XDHT22__TEMPERATURE_VALUE < 10.0f))
                    {
                        LCD_WriteChar(' ');
                        LCD_WriteChar(' ');
                    }
                    else if ((-10.0f < XDHT22__TEMPERATURE_VALUE) && (XDHT22__TEMPERATURE_VALUE < 0.0f))
                    {
                        LCD_WriteChar(' ');
                    }
                    else
                    {
                        // Nothing to do
                        ;
                    }

                    LCD_WriteInt((sint8)XDHT22__TEMPERATURE_VALUE);
                    LCD_WriteChar('.');
                    LCD_WriteInt((uint8)((XDHT22__TEMPERATURE_VALUE - ((sint8)XDHT22__TEMPERATURE_VALUE)) * 10.0f));
                    LCD_WriteChar('C');
                }
                else
                {
                    LCD_SetCursor(L__POS_ROW_DHT22_TEMP, L__POS_COL_DHT22_TEMP);
                    LCD_WriteString("  -- C");
                }
//            }

            /*******************************/
            /* HUMIDITY */
            /*******************************/
                if (Signal_RELIABLE == XDHT22__DATA_QUALIFIER)
                {
                    LCD_SetCursor(L__POS_ROW_DHT22_HUM, L__POS_COL_DHT22_HUM);
                    if (10.0f <= XDHT22__HUMIDITY_VALUE)
                    {
                        LCD_WriteChar(' ');
                    }
                    else if ((0.0f <= XDHT22__HUMIDITY_VALUE) && (XDHT22__HUMIDITY_VALUE < 10.0f))
                    {
                        LCD_WriteChar(' ');
                        LCD_WriteChar(' ');
                    }
                    else if ((-10.0f < XDHT22__HUMIDITY_VALUE) && (XDHT22__HUMIDITY_VALUE < 0.0f))
                    {
                        LCD_WriteChar(' ');
                    }
                    else
                    {
                        // Nothing to do
                        ;
                    }

                    LCD_WriteInt((sint8)XDHT22__HUMIDITY_VALUE);
                    //LCD_WriteChar('.');
                    //LCD_WriteInt((uint8)((XDHT22__HUMIDITY_VALUE - ((sint8)XDHT22__HUMIDITY_VALUE)) * 10.0f));
                    LCD_WriteChar('%');
                }
                else
                {
                    LCD_SetCursor(L__POS_ROW_DHT22_HUM, L__POS_COL_DHT22_HUM);
                    LCD_WriteString("-- %");
                }
            
            
            
            /*******************************/
            /* BATTERY VOLTAGE */
            /*******************************/
            bv_raw = MCH_ReadADC(MCH__ADC_CHANNEL_0);

            bv = bv_raw * (5.0f / 1024.0f);
            bv = bv / (100.0f / (100.0f + 330.0f));


            LCD_SetCursor(L__POS_ROW_BATT_VOLT, L__POS_COL_BATT_VOLT);
            if (10.0f > bv)
            {
                LCD_WriteChar(' ');
            }
            else
            {
                // Nothing to do
                ;
            }

            LCD_WriteInt((uint8)bv);
            LCD_WriteChar('.');
            LCD_WriteInt((uint8)((bv - ((uint8)bv)) * 10.0f));
            LCD_WriteChar('V');

            LCD_SetCursor(1u,7u);
            LCD_WriteInt(bv_raw);
        
            /*******************************/
            /* BATTERY PERCENT */
            /*******************************/
            LCD_SetCursor(L__POS_ROW_BATT_PERC, L__POS_COL_BATT_PERC);

            LCD_WriteCustomChar(1u);
            if (14.7f < bv)
            {
                LCD_WriteString("OVER CHARGE");
            }
            else if ((13.7f <= bv) && (bv <= 14.7f))
            {
                LCD_WriteCustomChar(4u);
                LCD_WriteCustomChar(4u);
                LCD_WriteCustomChar(4u);
                LCD_WriteCustomChar(4u);
            }
            else if ((12.6f <= bv) && (bv <= 13.2f))
            {
                LCD_WriteCustomChar(3u);
                LCD_WriteCustomChar(3u);
                LCD_WriteCustomChar(3u);
                LCD_WriteCustomChar(3u);
            }
            else if ((12.4f <= bv) && (bv < 12.6f))
            {
                LCD_WriteCustomChar(2u);
                LCD_WriteCustomChar(3u);
                LCD_WriteCustomChar(3u);
                LCD_WriteCustomChar(3u);
            }
            else if ((12.2f <= bv) && (bv < 12.4f))
            {
                LCD_WriteCustomChar(2u);
                LCD_WriteCustomChar(2u);
                LCD_WriteCustomChar(3u);
                LCD_WriteCustomChar(3u);
            }
            else if ((12.0f <= bv) && (bv < 12.2f))
            {
                LCD_WriteCustomChar(2u);
                LCD_WriteCustomChar(2u);
                LCD_WriteCustomChar(2u);
                LCD_WriteCustomChar(3u);
            }
            else if (12.0f > bv)
            {
                LCD_WriteCustomChar(2u);
                LCD_WriteCustomChar(2u);
                LCD_WriteCustomChar(2u);
                LCD_WriteCustomChar(5u);
            }
        }

    } // main end-less loop

} // Task_Main
