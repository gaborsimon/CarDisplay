//====== Header includes =======================================================
#include "LCDManager.h"


//====== Private Constants =====================================================
#define L__WELCOME_TIMEOUT_MS       (3 * 1000u)
#define L__WELCOME_MESSAGE_ROW_1    ("   CarDisplay   ")  
#define L__WELCOME_MESSAGE_ROW_2    ("      v1.0      ")  

#define L__POS_ROW_WELCOME          (1u)
#define L__POS_COL_WELCOME          (1u)

#define L__POS_ROW_BATT_LEVEL       (1u)
#define L__POS_COL_BATT_LEVEL       (1u)

#define L__POS_ROW_BATT_STATUS      (2u)
#define L__POS_COL_BATT_STATUS      (1u)

#define L__POS_ROW_DHT22_TEMP       (1u)
#define L__POS_COL_DHT22_TEMP      (11u)
#define L__POS_ROW_DHT22_HUM        (2u)
#define L__POS_COL_DHT22_HUM       (13u)

#define L__CUSTOM_CHAR_POS_BATT_TOP             (1u)
#define L__CUSTOM_CHAR_POS_BATT_MIDDLE_0        (2u)
#define L__CUSTOM_CHAR_POS_BATT_MIDDLE_1        (3u)
#define L__CUSTOM_CHAR_POS_BATT_MIDDLE_CH       (4u)
#define L__CUSTOM_CHAR_POS_BATT_MIDDLE_CH_INV   (5u)
#define L__CUSTOM_CHAR_POS_BATT_BOTTOM_0        (6u)
#define L__CUSTOM_CHAR_POS_BATT_BOTTOM_CH_INV   (7u)

#define L__BATTERY_LEVEL_OVERCHARGE (14.7f)
#define L__BATTERY_LEVEL_CHARGE     (13.7f)
#define L__BATTERY_LEVEL_100        (12.6f)
#define L__BATTERY_LEVEL_75         (12.4f)
#define L__BATTERY_LEVEL_50         (12.2f)
#define L__BATTERY_LEVEL_25         (12.0f)


//====== Private Signals =======================================================


//====== Private Function Prototypes ===========================================
void L_RefreshWelcome(void);
void L_RefreshBattery(void);
void L_RefreshDHT22(void);


//====== Private Functions =====================================================
/*
 * Name: L_RefreshWelcome
 *
 * Description: This function display the welcome message and
 *              it waits for a defined time.
 *
 * Input: None
 *
 * Output: None
 */
void L_RefreshWelcome(void)
{
    LCD_SetCursor(L__POS_ROW_WELCOME, L__POS_COL_WELCOME);
    LCD_WriteString(L__WELCOME_MESSAGE_ROW_1); 
    LCD_SetCursor(L__POS_ROW_WELCOME + 1u, L__POS_COL_WELCOME);
    LCD_WriteString(L__WELCOME_MESSAGE_ROW_2); 

    _delay_ms(L__WELCOME_TIMEOUT_MS);

    LCD_Clear();
}


/*
 * Name: L_RefreshBattery
 *
 * Description: This function display the battery related information:
 *              - battery level in voltage
 *              - status icon
 *
 * Input: None
 *
 * Output: None
 */
void L_RefreshBattery(void)
{
    static G_Flag_e L_OverChargeToggle  = Flag_SET;
           float32  _BatteryVoltage     = U__INIT_VALUE_FLOAT;


    _BatteryVoltage = MCH_ReadBatteryVoltage();

    //**************************************************************************
    //****** BATTERY LEVEL
    //**************************************************************************
    LCD_SetCursor(L__POS_ROW_BATT_LEVEL, L__POS_COL_BATT_LEVEL);
    if (10.0f > _BatteryVoltage)
    {
        LCD_WriteChar(' ');
    }
    else
    {
        // Nothing to do
        ;
    }

    LCD_WriteInt((uint8)_BatteryVoltage);
    LCD_WriteChar('.');
    LCD_WriteInt((uint8)((_BatteryVoltage - ((uint8)_BatteryVoltage)) * 10.0f));
    LCD_WriteChar('V');


    //**************************************************************************
    //****** BATTERY STATUS
    //**************************************************************************
    LCD_SetCursor(L__POS_ROW_BATT_STATUS, L__POS_COL_BATT_STATUS);
    LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_TOP);

    if (L__BATTERY_LEVEL_OVERCHARGE <= _BatteryVoltage)
    {
        if (Flag_SET == L_OverChargeToggle)
        {
            L_OverChargeToggle = Flag_CLEAR;
            LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_CH);
            LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_CH);
            LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_CH);
            LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_CH);
        }
        else
        {
            L_OverChargeToggle = Flag_SET; 
            LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_CH_INV);
            LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_CH_INV);
            LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_CH_INV);
            LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_BOTTOM_CH_INV);
        }
    }
    else if ((L__BATTERY_LEVEL_CHARGE <= _BatteryVoltage) && (_BatteryVoltage < L__BATTERY_LEVEL_OVERCHARGE))
    {
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_CH);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_CH);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_CH);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_CH);
    }
    else if ((L__BATTERY_LEVEL_100 <= _BatteryVoltage) && (_BatteryVoltage < L__BATTERY_LEVEL_CHARGE))
    {
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_1);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_1);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_1);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_1);
    }
    else if ((L__BATTERY_LEVEL_75 <= _BatteryVoltage) && (_BatteryVoltage < L__BATTERY_LEVEL_100))
    {
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_0);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_1);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_1);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_1);
    }
    else if ((L__BATTERY_LEVEL_50 <= _BatteryVoltage) && (_BatteryVoltage < L__BATTERY_LEVEL_75))
    {
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_0);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_0);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_1);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_1);
    }
    else if ((L__BATTERY_LEVEL_25 <= _BatteryVoltage) && (_BatteryVoltage < L__BATTERY_LEVEL_50))
    {
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_0);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_0);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_0);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_1);
    }
    else if (_BatteryVoltage < L__BATTERY_LEVEL_25)
    {
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_0);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_0);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_0);
        LCD_WriteCustomChar(L__CUSTOM_CHAR_POS_BATT_BOTTOM_0);
    }
}


/*
 * Name: L_RefreshDHT22
 *
 * Description: This function display the DHT22 sensor related information:
 *              - temperature in degC
 *              - humidity
 *
 * Input: None
 *
 * Output: None
 */
void L_RefreshDHT22(void)
{
    //**************************************************************************
    //****** TEMPERATURE - DHT22
    //**************************************************************************
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


    //**************************************************************************
    //****** HUMIDITY - DHT22
    //**************************************************************************
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
        else
        {
            // Nothing to do
            ;
        }

        LCD_WriteInt((uint8)XDHT22__HUMIDITY_VALUE);
        LCD_WriteChar('%');
    }
    else
    {
        LCD_SetCursor(L__POS_ROW_DHT22_HUM, L__POS_COL_DHT22_HUM);
        LCD_WriteString("-- %");
    }
}


//====== Public Signals ========================================================


//====== Public Functions ======================================================
/*
 * Name: LCM_Init
 *
 * Description: This is the initialization function that sets the custom
 *              characters and inits and clears the LCD.
 *
 * Input: None
 *
 * Output: None
 */
void LCM_Init(void)
{
    LCD_Init();
    LCD_SwitchOn();
    LCD_Clear();

    LCD_StoreCustomChar(L__CUSTOM_CHAR_POS_BATT_TOP,            LCD_CharBatteryTop);
    LCD_StoreCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_0,       LCD_CharBatteryMiddle0);
    LCD_StoreCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_1,       LCD_CharBatteryMiddle1);
    LCD_StoreCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_CH,      LCD_CharBatteryMiddleCharge);
    LCD_StoreCustomChar(L__CUSTOM_CHAR_POS_BATT_MIDDLE_CH_INV,  LCD_CharBatteryMiddleChargeInv);
    LCD_StoreCustomChar(L__CUSTOM_CHAR_POS_BATT_BOTTOM_0,       LCD_CharBatteryBottom0);
    LCD_StoreCustomChar(L__CUSTOM_CHAR_POS_BATT_BOTTOM_CH_INV,  LCD_CharBatteryBottomChargeInv);
}


/*
 * Name: LCM_Refresh
 *
 * Description: This is the main function that is responsible for putting
 *              the information into the LCD display.
 *
 * Input: element name that has to be updated 
 *
 * Output: None
 */
void LCM_Refresh(uint8 _Element)
{
    switch (_Element)
    {
        case LCM__WELCOME:
        {
            L_RefreshWelcome();
        }
        break;
        
        case LCM__BATTERY:
        {
            L_RefreshBattery();
        }
        break;

        case LCM__DHT22:
        {
            L_RefreshDHT22();
        }
        break;
    } 
}
