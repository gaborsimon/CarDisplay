//====== Header includes =======================================================
#include "MicroControllerHAL.h"


//====== Private Constants =====================================================
#define L__ADC_REF_VOLT             (5.0f)
#define L__ADC_RESOLUTION_BIT    (1024.0f)
#define L__ADC_OFFSET_VOLT          (0.1f)
#define L__ADC_BATTERY_R1_OHM   (33000.0f)
#define L__ADC_BATTERY_R2_OHM   (10000.0f)

#define L__ADC_LSB_TO_VOLT      (L__ADC_REF_VOLT / L__ADC_RESOLUTION_BIT)
#define L__ADC_VOLT_TO_BATTERY  (L__ADC_BATTERY_R2_OHM / (L__ADC_BATTERY_R1_OHM + L__ADC_BATTERY_R2_OHM))


//====== Private Signals =======================================================


//====== Private Function Prototypes ===========================================


//====== Private Functions =====================================================


//====== Public Signals ========================================================


//====== Public Functions ======================================================
/*
 * Name: MCH_InitPins
 *
 * Description: This function initializes uC pins by setting them to digital or
 *              analogue / input or output.
 *
 * Input: None
 *
 * Output: None
 */
void MCH_InitPins(void)
{
    /* DHT22 */
    MCH__GPIO_DIRECTION  (MCH__DDR_DHT22,   MCH__P_DHT22_DATA,  U__OUTPUT);
    MCH__GPIO_WRITE      (MCH__PORT_DHT22,  MCH__P_DHT22_DATA,  U__HIGH);

    /* LCD DISPLAY */
    MCH__GPIO_DIRECTION  (MCH__DDR_LCD,     MCH__P_LCD_RS,      U__OUTPUT);
    MCH__GPIO_DIRECTION  (MCH__DDR_LCD,     MCH__P_LCD_RW,      U__OUTPUT);
    MCH__GPIO_DIRECTION  (MCH__DDR_LCD,     MCH__P_LCD_EN,      U__OUTPUT);
    MCH__GPIO_DIRECTION  (MCH__DDR_LCD,     MCH__P_LCD_D4,      U__OUTPUT);
    MCH__GPIO_DIRECTION  (MCH__DDR_LCD,     MCH__P_LCD_D5,      U__OUTPUT);
    MCH__GPIO_DIRECTION  (MCH__DDR_LCD,     MCH__P_LCD_D6,      U__OUTPUT);
    MCH__GPIO_DIRECTION  (MCH__DDR_LCD,     MCH__P_LCD_D7,      U__OUTPUT);

    /* Battery Voltage Measurement */
    MCH__GPIO_DIRECTION  (MCH__DDR_BVM,     MCH__P_BVM,         U__INPUT);
}


/*
 * Name: MCH_InitWatchdog
 *
 * Description: This function initializes the Watchdog timer.
 *
 * Input: None
 *
 * Output: None
 */
void MCH_InitWatchdog(void)
{
    MCH__WD_RESET();
    
    /* Start timed sequence */
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    
    // Watchdog Timeout by setting Number of WDT Oscillator (Cycles) to 512K (524288 cycles) = 4sec
    WDTCSR = (1<<WDE) | (1<<WDP3) | (0<<WDP2) | (0<<WDP1) | (0<<WDP0);
}


/*
 * Name: MCH_InitSleepMode
 *
 * Description: This function initializes and enables the desired Sleep Mode of the device.
 *              In our application the "Power-save" mode shall be used because the main
 *              scheduler is clocked from the external watch-clock driven asynchronous
 *              Timer2.
 *
 * Input: None
 *
 * Output: None
 */
/*
void MCH_InitSleepMode(void)
{
    // Setting the "Power-save" mode in sleep mode
    U__BIT_CLR(MCUCR,SM2);
    U__BIT_SET(MCUCR,SM1);
    U__BIT_SET(MCUCR,SM0);
    
    // Enable the sleep mode
    U__BIT_SET(MCUCR,SE);
}
*/


/*
 * Name: MCH_InitTimer1
 *
 * Description: This function initializes the Timer1 peripheral
 *              to generate the main tasking periode time of 1 second.
 *
 * Input: None
 *
 * Output: None
 */
void MCH_InitTimer1(void)
{
    // Reset control registers
    TCCR1A = 0x00u;
    TCCR1B = 0x00u;

    // Compare Output Mode for Channel A/B: Normal port operation, OC1A/OC1B disconnected
    U__BIT_CLR(TCCR1A, COM1A1);
    U__BIT_CLR(TCCR1A, COM1A0);
    U__BIT_CLR(TCCR1A, COM1B1);
    U__BIT_CLR(TCCR1A, COM1B0);

    // Waveform Generation Mode: CTC, update of OCR1x Immediate
    U__BIT_CLR(TCCR1B, WGM13);
    U__BIT_SET(TCCR1B, WGM12);
    U__BIT_CLR(TCCR1A, WGM11);
    U__BIT_CLR(TCCR1A, WGM10);
    
    // Input Capture Noise Canceler: Disabled
    U__BIT_CLR(TCCR1B, ICNC1);
    
    // Input Capture Edge Select: Falling (negative) edge
    U__BIT_CLR(TCCR1B, ICES1);
    
    // Clock Select: CLK / 256 = 46.875kHz = 21.33us
    U__BIT_SET(TCCR1B, CS12);
    U__BIT_CLR(TCCR1B, CS11);
    U__BIT_CLR(TCCR1B, CS10);
    
    // Reset Timer Register
    TCNT1 = 0u;
    // Set Output Compare Register for Channel A to 1sec
    OCR1A = 62500u;
    // Reset Output Compare Register for Channel B
    OCR1B = 0u;

    // Timer Input Capture Interrupt: Disabled
    U__BIT_CLR(TIMSK1, ICIE1);
    // Output Compare A Match Interrupt: Enabled
    U__BIT_SET(TIMSK1, OCIE1A);
    // Output Compare B Match Interrupt: Disabled
    U__BIT_CLR(TIMSK1, OCIE1B);
    // Timer Overflow Interrupt: Disabled
    U__BIT_CLR(TIMSK1, TOIE1);
}


/*
 * Name: MCH_InitADC
 *
 * Description: This function initializes the ADC peripheral of the MCU.
 *
 * Input:  None
 *
 * Output: None
 */
void MCH_InitADC(void)
{
    // Reset control registers
    ADMUX  = 0x00u;
    ADCSRA = 0x00u; 
    
    // Reference Selection: AVcc with external capacitor at VREF pin
    U__BIT_CLR(ADMUX, REFS1);
    U__BIT_SET(ADMUX, REFS0);
    
    // ADC Left Adjust Result: Enabled
    U__BIT_CLR(ADMUX, ADLAR);
    
    // Analog Channel and Gain Selection Bits: Single mode
    U__BIT_CLR(ADMUX, MUX3);
    U__BIT_CLR(ADMUX, MUX2);
    U__BIT_CLR(ADMUX, MUX1);
    U__BIT_CLR(ADMUX, MUX0);

    // ADC Auto Trigger: Disabled 
    U__BIT_CLR(ADCSRA, ADATE);
    
    // ADC Interrupt: Disabled
    U__BIT_CLR(ADCSRA, ADIE);
    
    // ADC Prescaler Select: CLK / 128 = 93.75kHz
    U__BIT_SET(ADCSRA, ADPS2);
    U__BIT_SET(ADCSRA, ADPS1);
    U__BIT_SET(ADCSRA, ADPS0);
   
    // ADC: Enabled
    U__BIT_SET(ADCSRA, ADEN); 
}


/*
 * Name: MCH_ReadADC
 *
 * Description: This function performs an AD conversion with the given channel.
 *              The result is stored in 10-bit precision.
 *
 * Input:  Desired AD input channel
 *
 * Output: Result of the AD conversion with 10-bit precision
 */
uint16 MCH_ReadADC(uint8 _Channel)
{
    uint16 _Ret = U__INIT_VALUE_UINT;


    // Only the 7 single channels can be selected
    _Channel &= 0x07u;

    // Set the desired channel
    ADMUX = (ADMUX & 0xF8u) | _Channel;

    // Start AD conversion
    U__BIT_SET(ADCSRA, ADSC);
    
    // Wait for the conversion to complete
    loop_until_bit_is_clear(ADCSRA, ADSC);

    _Ret = (uint16)((ADCH << 8u) | ADCL);


    return _Ret;
}


/*
 * Name: MCH_ReadBatteryVoltage
 *
 * Description: This function measures the battery voltage via ADC.
 *              The result is in Voltage dimension compensated with ADC offset.
 *
 * Input:  ADC battery voltage channel
 *
 * Output: Measured battery voltage
 */
float32 MCH_ReadBatteryVoltage(void)
{
    float32 _Ret = U__INIT_VALUE_FLOAT;


    _Ret = (float32)MCH_ReadADC(MCH__ADC_CHANNEL_0);

    _Ret *= L__ADC_LSB_TO_VOLT;
    _Ret /= L__ADC_VOLT_TO_BATTERY;
    _Ret += L__ADC_OFFSET_VOLT;


    return _Ret;
}
