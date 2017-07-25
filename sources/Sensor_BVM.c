//====== Header includes =======================================================
#include "Sensor_BVM.h"


//====== Private Constants =====================================================
#define L__ADC_REF_VOLT             (5.0f)
#define L__ADC_RESOLUTION_BIT    (1024.0f)
#define L__ADC_OFFSET_VOLT          (0.1f)
#define L__ADC_BATTERY_R1_KOHM       (33u)
#define L__ADC_BATTERY_R2_KOHM       (10u)

#define L__ADC_LSB_TO_VOLT      (L__ADC_REF_VOLT / L__ADC_RESOLUTION_BIT)
#define L__ADC_VOLT_TO_BATTERY  ((L__ADC_BATTERY_R2_KOHM * 1000.0f) / ((L__ADC_BATTERY_R1_KOHM * 1000.0f) + (L__ADC_BATTERY_R2_KOHM * 1000.0f)))


//====== Private Signals =======================================================


//====== Private Function Prototypes ===========================================


//====== Private Functions =====================================================


//====== Public Signals ========================================================
BVM_Data_s BVM_Data;


//====== Public Functions ======================================================
/*
 * Name: BVM_Init
 *
 * Description: The function initializes the global variables.
 *
 * Input: None
 *
 * Output: None
 */
void BVM_Init(void)
{
    BVM_Data.Qualifier      = Signal_NOT_RELIABLE;
    BVM_Data.BatteryVoltage = U__INIT_VALUE_FLOAT;
}


/*
 * Name: BVM_Refresh
 *
 * Description:  The function performs periodically the sensor read action.
 *               It measures the battery voltage via ADC.
 *               The result is in Voltage dimension compensated with ADC offset.
 *
 * Input: ADC battery voltage channel
 *
 * Output: None
 */
void BVM_Refresh(void)
{
    float32 _Ret = U__INIT_VALUE_FLOAT;


    _Ret = (float32)MCH_ReadADC(MCH__ADC_CHANNEL_0);

    _Ret *= L__ADC_LSB_TO_VOLT;
    _Ret /= L__ADC_VOLT_TO_BATTERY;
    _Ret += L__ADC_OFFSET_VOLT;

    BVM_Data.BatteryVoltage = _Ret;
    BVM_Data.Qualifier      = Signal_RELIABLE;
}
